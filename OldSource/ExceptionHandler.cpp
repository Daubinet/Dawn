// Nate's exception handler code

#include "ExceptionHandler.h"

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

#ifndef _MSVC_VER
    #ifndef strcpy_s
        #define strcpy_s(a, b, c) strncpy(a, c, b)
    #endif //strcpy_s
	#ifndef asctime_s
		#define asctime_s(a, b, c) strcpy_s(a, b, asctime(c));
	#endif //asctime_s
	#ifndef localtime_s
		#define localtime_s(a, b) (a) = localtime(b)
	#endif //localtime_s
#endif //_MSVC_VER

#if defined(WIN32) || defined(_WIN32)
#include <imagehlp.h>
#include <limits.h>
#include <malloc.h>
#include <map>

#ifndef PATH_MAX
	#ifdef MAX_PATH
		#define PATH_MAX MAX_PATH
	#else
		#define PATH_MAX 256 /* just to be safe*/
	#endif //MAX_PATH
#endif //PATH_MAX

#ifdef _M_IX86
    #define PNTR_LEN 8
#else
    #define PNTR_LEN 16
#endif

#define as_ptr(var) "0x" << std::right << std::setfill('0') << std::setw(PNTR_LEN) << var

// needed for backtrace
HMODULE imghlp;
BOOL (WINAPI *_SymInitialize)(HANDLE, LPSTR, BOOL);
BOOL (WINAPI *_SymCleanup)(HANDLE);
DWORD (WINAPI *_SymSetOptions)(DWORD);
BOOL (WINAPI *_SymUnDName)(PIMAGEHLP_SYMBOL, PSTR, DWORD);
PFUNCTION_TABLE_ACCESS_ROUTINE _SymFunctionTableAccess;
PGET_MODULE_BASE_ROUTINE _SymGetModuleBase;
BOOL (WINAPI *_StackWalk)(DWORD, HANDLE, HANDLE, LPSTACKFRAME, LPVOID,
                          PREAD_PROCESS_MEMORY_ROUTINE, PFUNCTION_TABLE_ACCESS_ROUTINE, PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE);
BOOL (WINAPI *_SymGetSymFromAddr)(HANDLE, DWORD, LPDWORD, PIMAGEHLP_SYMBOL);
BOOL (WINAPI *_SymGetLineFromAddr)(HANDLE, DWORD, LPDWORD, PIMAGEHLP_LINE);

ExceptionHandler::ExceptionHandler()
{
    previous_exception_filter = SetUnhandledExceptionFilter(exception_filter);
    // disable system error pop-ups. We'll handle it instead.
    last_error_mode = SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);

    imghlp = LoadLibraryA("imagehlp.dll");
    if(imghlp)
    {
        _SymInitialize = (BOOL (WINAPI *)(HANDLE, LPSTR, BOOL))GetProcAddress(imghlp, "SymInitialize");
        _SymCleanup = (BOOL (WINAPI *)(HANDLE))GetProcAddress(imghlp, "SymCleanup");
        _SymSetOptions = (DWORD (WINAPI *)(DWORD))GetProcAddress(imghlp, "SymSetOptions");
        _SymUnDName = (BOOL (WINAPI *)(PIMAGEHLP_SYMBOL, PSTR, DWORD))GetProcAddress(imghlp, "SymUnDName");
        _SymFunctionTableAccess = (PFUNCTION_TABLE_ACCESS_ROUTINE)GetProcAddress(imghlp, "SymFunctionTableAccess");
        _SymGetModuleBase = (PGET_MODULE_BASE_ROUTINE)GetProcAddress(imghlp, "SymGetModuleBase");
        _StackWalk = (BOOL (WINAPI *)(DWORD, HANDLE, HANDLE, LPSTACKFRAME, LPVOID, PREAD_PROCESS_MEMORY_ROUTINE,
                                      PFUNCTION_TABLE_ACCESS_ROUTINE, PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE))
                    GetProcAddress(imghlp, "StackWalk");
        _SymGetSymFromAddr = (BOOL (WINAPI *)(HANDLE, DWORD, LPDWORD, PIMAGEHLP_SYMBOL))GetProcAddress(imghlp, "SymGetSymFromAddr");
        _SymGetLineFromAddr = (BOOL (WINAPI *)(HANDLE, DWORD, LPDWORD, PIMAGEHLP_LINE))GetProcAddress(imghlp, "SymGetLineFromAddr");
    }
}

ExceptionHandler::~ExceptionHandler()
{
    SetUnhandledExceptionFilter(previous_exception_filter);
    SetErrorMode(last_error_mode);
}

std::string _getExceptionString(int exccode)
{
    switch(exccode)
    {
		case EXCEPTION_ACCESS_VIOLATION:
            return "an Access Violation";
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			return "an Array Bound Exceeded";
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			return "a Datatype Misalignment";
		case EXCEPTION_FLT_DENORMAL_OPERAND:
            return "a Float Denormal Operand";
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			return "a Float Divided By Zero";
		case EXCEPTION_FLT_INEXACT_RESULT:
			return "a Float Inexact Result";
		case EXCEPTION_FLT_INVALID_OPERATION:
			return "a Float Invalid Operation";
		case EXCEPTION_FLT_OVERFLOW:
			return "a Float Overflow";
		case EXCEPTION_FLT_STACK_CHECK:
			return "a Float Stack Check";
		case EXCEPTION_FLT_UNDERFLOW:
			return "a Float Underflow";
		case EXCEPTION_GUARD_PAGE:
			return "a Guard Page";
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			return "an Illegal Instruction";
		case EXCEPTION_IN_PAGE_ERROR:
			return "an In Page-Error";
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			return "an Integer Divided By Zero";
		case EXCEPTION_INT_OVERFLOW:
			return "an Integer Overflow";
		case EXCEPTION_INVALID_DISPOSITION:
			return "an Invalid Disposition";
		case EXCEPTION_INVALID_HANDLE:
			return "an Invalid Handle";
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			return "a Noncontinuable Exception";
		case EXCEPTION_PRIV_INSTRUCTION:
			return "a Privileged Instruction";
		case EXCEPTION_SINGLE_STEP:
			return "a Single Step";
		case EXCEPTION_STACK_OVERFLOW:
			return "a Stack Overflow";
        default:
            // TODO: query NTDLL.DLL?
            break;
    }
    return "an unknown exception.";
}

std::string getOSString()
{
    std::stringstream f;
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    OSVERSIONINFOEXA os_info;
    os_info.dwOSVersionInfoSize = sizeof(os_info);
    GetVersionExA((OSVERSIONINFO*)(&os_info));
    // derived from MSDN page on OSVERSIONINFOEX
    f << "Windows ";
    switch(os_info.dwMajorVersion)
    {
        case 5: // 2000 -> XP
        {
            if(os_info.dwMinorVersion == 0)
                f << "2000 ";
            else if(os_info.dwMinorVersion == 1)
                f << "XP ";
            else if(os_info.dwMinorVersion == 2)
            {
                if(os_info.wProductType == VER_NT_WORKSTATION && sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
                    f << "XP Professional ";
                //else if(os_info.wSuiteMask & VER_SUITE_WH_SERVER)
                //    f << "Home Server ";
                else
                {
                    f << "Server 2003 ";
                    if(GetSystemMetrics(SM_SERVERR2))
                        f << "R2 ";
                }
            }
            else
                f << "(version unknown)";
            break;
        }
        case 6: // Vista and later
        {
            if(os_info.wProductType == VER_NT_WORKSTATION)
            {
                if(os_info.dwMinorVersion == 0)
                    f << "Vista ";
                else if(os_info.dwMinorVersion == 1)
                    f << "7 ";
                else
                    f << "(version unknown)";
            }
            else if(os_info.wProductType != VER_NT_WORKSTATION)
            {
                if(os_info.dwMinorVersion == 0)
                    f << "Server 2008 ";
                else if(os_info.dwMinorVersion == 1)
                    f << "Server 2008 R2 ";
                else
                    f << "(version unknown)";
            }
            else
                f << "(version unknown)";
            break;
        }
        default:
            f << "(version unknown) ";
            break;
    }
    if(sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        f << "64-bit";
    else
        f << "32-bit";

    return f.str();
}

std::string getRegisterString(PCONTEXT context)
{
    #define preg(regname, sregname)\
        f << regname << std::right << std::setfill(' ') << std::setw(25 - strlen(regname))\
          << " = " << as_ptr(context->sregname) << std::endl
    std::stringstream f;
    f << std::hex;
    // x86-only
    #ifdef _M_IX86
    if(context->ContextFlags & CONTEXT_INTEGER)
    {
        preg("eax", Eax);
        preg("ebx", Ebx);
        preg("ecx", Ecx);
        preg("edx", Edx);
        preg("source index", Esi);
        preg("destination index", Edi);
    }
    if(context->ContextFlags & CONTEXT_CONTROL)
    {
        preg("stack base", Ebp);
        preg("stack top", Esp);
        preg("instruction", Eip);
    }
    if(context->ContextFlags & CONTEXT_SEGMENTS)
    {
        preg("code segment", SegCs);
        preg("data segment", SegDs);
        preg("stack segment", SegSs);
        preg("es", SegEs);
        preg("fs", SegFs);
        preg("gs", SegGs);
    }
    f << std::endl;
    if(context->ContextFlags & CONTEXT_CONTROL)
    {
        preg("cpu flags", EFlags);
        f << "Flags Set:" << std::endl;
        #define prfl(name, value) if(context->EFlags & value) f << name << std::endl
        prfl("carry", 0x00000001);
        prfl("parity", 0x00000004);
        prfl("auxiliary carry", 0x00000010);
        prfl("zero", 0x00000040);
        prfl("sign", 0x00000080);
        prfl("trap", 0x00000100);
        prfl("interrupt enabled", 0x00000200);
        prfl("overflow", 0x00000400);
        prfl("nested task", 0x00004000);
        prfl("resume", 0x00010000);
        prfl("virtual 8086 (16-bit) mode", 0x00020000);
        prfl("alignment check", 0x00040000);
        prfl("virtual interrupt", 0x00080000);
        prfl("virtual interrupt pending", 0x00100000);
        #undef prfl
    }
    #elif _M_AMD64
    // TODO
    #endif //
    return f.str();
    #undef preg
}

// The GetModuleBase function retrieves the base address of the module that contains the specified address.
static
HMODULE GetModuleBase(DWORD dwAddress)
{
	MEMORY_BASIC_INFORMATION Buffer;

	return (HMODULE)(VirtualQuery((LPCVOID) dwAddress, &Buffer, sizeof(Buffer)) ? (DWORD) Buffer.AllocationBase : 0);
}

void win32_backtrace(std::ofstream& f, PCONTEXT context, DWORD exception_address)
{
    // make sure we have the required functions
    if(!imghlp || !_SymInitialize || !_SymCleanup || !_SymSetOptions || !_SymUnDName || !_SymFunctionTableAccess || !_SymGetModuleBase || !_StackWalk)
    {
        f << "Could not backtrace -- missing or invalid imghlp.dll." << std::endl;
        return;
    }

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    // this might allow us to get lines from instruction pointers!
    _SymSetOptions(SYMOPT_LOAD_LINES);

    // initialize symbols
    if(!_SymInitialize(process, NULL, true))
    {
        f << "Could not backtrace -- failure at SymInitialize." << std::endl;
        return;
    }

    // set up frame pointer
    STACKFRAME frame;
    memset(&frame, 0, sizeof(frame));
    #if _M_IX86
    frame.AddrPC.Offset = context->Eip;
    frame.AddrStack.Offset = context->Esp;
    frame.AddrFrame.Offset = context->Ebp;
    #elif _M_AMD64
    frame.AddrPC.Offset = context->Rip;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrFrame.Offset = context->Rbp;
    #endif
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Mode = AddrModeFlat;

    f << "backtrace:" << std::endl;

    HMODULE thismodule = NULL;
    while(true)
    {
        bool success = false;
        char modulename[PATH_MAX] = "";
        char filename[PATH_MAX] = "";
        char funcname[512] = "";

        #if _M_IX86
        if(!_StackWalk(IMAGE_FILE_MACHINE_I386, process, thread,
                       &frame, context, NULL,
                       _SymFunctionTableAccess,
                       _SymGetModuleBase, NULL
                       )
           )
           break;
        #elif _M_AMD64
        if(!_StackWalk(IMAGE_FILE_MACHINE_AMD64, process, thread,
                       &frame, context, NULL,
                       _SymFunctionTableAccess,
                       _SymGetModuleBase, NULL
                       )
           )
           break;
        #endif //
        // this means a holy wtf happened
        if(frame.AddrPC.Offset == 0)
            break;

        // get the module this function-call is in
        thismodule = GetModuleBase(frame.AddrPC.Offset);
        if(thismodule && GetModuleFileName(thismodule, modulename, PATH_MAX))
        {
            char* mname = strrchr(modulename, '\\')+1;
            int len = strlen(mname);
            f.fill(' ');
            f << "[" << mname << std::left << std::setw(25-len) << "]";

            if(!success)
            {
                // the IMAGEHLP_SYMBOL structure is one of the odder ones out there.
                //      it, itself, only acts as a prefix for an array of bytes.
                //      that explains the next few lines, I hope...
                char symbuf[sizeof(IMAGEHLP_SYMBOL) + 512];
                PIMAGEHLP_SYMBOL sym = (PIMAGEHLP_SYMBOL)symbuf;
                sym->SizeOfStruct = sizeof(symbuf);
                sym->MaxNameLength = 512;

                // now to grab the symbol name
                /// Try from .DLL
                DWORD offset;
                if(_SymGetSymFromAddr(process, frame.AddrPC.Offset, &offset, sym))
                {
                    // success!
                    success = true;
                    // now to demangle the symbol name
                    _SymUnDName(sym, funcname, 512);

                    // now to get the line number
                    IMAGEHLP_LINE line;
                    memset(&line, 0, sizeof(IMAGEHLP_LINE));
                    line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
                    offset = 0;
                    DWORD tempoffset = 0;
                    while(tempoffset < 100 && !_SymGetLineFromAddr(process, frame.AddrPC.Offset - tempoffset, &offset, &line))
                        tempoffset++;
                    if(tempoffset < 100)
                    {
                        f << line.FileName << ":" << std::left << std::setw(30 - strlen(line.FileName)) << line.LineNumber << " ";
                    }

                    f << std::setfill(' ') << std::setw(30) << std::left << funcname << "(" << as_ptr(frame.AddrPC.Offset) << ")";
                }// _SymGetSymFromAddr
                if(!success) /// Try from .exe
                {
                    PIMAGE_NT_HEADERS p_nt_header;
                    IMAGE_NT_HEADERS nt_header;
                    PIMAGE_DOS_HEADER dos_header;
                    PIMAGE_SECTION_HEADER _section;
                    DWORD nearest_addr = 0, nearest_name;
                    long nt_header_offset;

                    // read the offset of the NT header from the DOS header
                    dos_header = (PIMAGE_DOS_HEADER)thismodule;
                    if(ReadProcessMemory(process, &dos_header->e_lfanew, &nt_header_offset, sizeof(nt_header_offset), NULL))
                    {
                        // read the NT header
                        p_nt_header = (PIMAGE_NT_HEADERS)((DWORD)thismodule + (DWORD)nt_header_offset);
                        if(ReadProcessMemory(process, p_nt_header, &nt_header, sizeof(IMAGE_NT_HEADERS), NULL))
                        {
                            // find the section
                            _section = (PIMAGE_SECTION_HEADER)((DWORD)p_nt_header + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER)
                                                              + nt_header.FileHeader.SizeOfOptionalHeader);

                            for(int i = 0; i < nt_header.FileHeader.NumberOfSections; ++i)
                            {
                                // read section from pointer
                                IMAGE_SECTION_HEADER section;

                                PIMAGE_EXPORT_DIRECTORY _export_dir = NULL;
                                BYTE ExportSectionName[IMAGE_SIZEOF_SHORT_NAME] = {'.', 'e', 'd', 'a', 't', 'a', '\0', '\0'};

                                if(ReadProcessMemory(process, _section, &section, sizeof(IMAGE_SECTION_HEADER), NULL))
                                {
                                    // figure out where to find export directory
                                    if(memcmp(section.Name, ExportSectionName, IMAGE_SIZEOF_SHORT_NAME))
                                        _export_dir = (PIMAGE_EXPORT_DIRECTORY)section.VirtualAddress;
                                    else if((nt_header.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress >= section.VirtualAddress)
                                            && (nt_header.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress <
                                                (section.VirtualAddress + section.SizeOfRawData)))
                                        _export_dir = (PIMAGE_EXPORT_DIRECTORY)nt_header.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
                                    if(_export_dir)
                                    {

                                        // read the export directory from memory
                                        IMAGE_EXPORT_DIRECTORY export_dir;
                                        if(ReadProcessMemory(process, (PVOID)((DWORD)thismodule + (DWORD)_export_dir),
                                            &export_dir, sizeof(IMAGE_EXPORT_DIRECTORY), NULL))
                                        {
                                            // read the addresses in this export dir
                                            //PDWORD addrs[export_dir.NumberOfFunctions];
                                            PDWORD* addrs = (PDWORD*)malloc(export_dir.NumberOfFunctions*sizeof(PDWORD));

                                            if(ReadProcessMemory(process, (PVOID)((DWORD)thismodule + (DWORD)export_dir.AddressOfFunctions),
                                                    addrs, export_dir.NumberOfFunctions*sizeof(PDWORD), NULL))
                                            {
                                                // find the function
                                                for(DWORD j = 0; j < export_dir.NumberOfNames; ++j)
                                                {
                                                    DWORD func = (DWORD)thismodule + (DWORD)addrs[j];
                                                    if(func <= frame.AddrPC.Offset && func > nearest_addr)
                                                    {
                                                        nearest_addr = func;

                                                        // read the function name pointer
                                                        if(ReadProcessMemory(process,
                                                            (PVOID)((DWORD)thismodule + export_dir.AddressOfNames + j*sizeof(DWORD)),
                                                                &nearest_name, sizeof(DWORD), NULL))
                                                            nearest_name = (DWORD) thismodule + nearest_name;
                                                    }// function in range
                                                }// for each function
                                            }// read addresses
                                            free(addrs);
                                        }// read export directory

                                    }
                                }// read section from memory
                            }// foreach section
                            // function name
                            if(nearest_addr)
                            {
                                if(ReadProcessMemory(process, (PVOID)nearest_name, funcname, 512, NULL))
                                {
                                    success = true;
                                    f << std::setfill(' ') << std::setw(30) << std::left << funcname << "(" << as_ptr(frame.AddrPC.Offset) << ")";
                                }
                            }// get function name

                        }// read NT header from memory
                    }// read NT header offset

                    if(!success)
                        f << std::setfill(' ') << std::setw(30) << std::left << "Unknown function" << "(" << as_ptr(frame.AddrPC.Offset) << ")";
                }
                f << std::endl;
            }// !success
        } // thismodule && GetModuleFileName(thismodule)

    }// while(true)

    _SymCleanup(process);
    f << "End of backtrace." << std::endl;
}

LONG WINAPI ExceptionHandler::exception_filter(PEXCEPTION_POINTERS info)
{
    // prevent multiple executions
    static bool executed = false;
    // some info on the exception
    PEXCEPTION_RECORD record = info->ExceptionRecord;
    // will hold the name of the module resulting in the crash
    char _mname[MAX_PATH];
    // whether it was in the application or dll
    bool in_app = true;

    if(!executed)
    {
        executed = true;

        std::ofstream f(REPORT_FILE, std::fstream::out|std::fstream::trunc);
        if(f.is_open())
        {
            // print crash time
            time_t t = std::time(NULL);
			char tbuff[26];
			struct tm now;
			localtime_s(&now, &t);
			asctime_s(tbuff, 26, &now);
            f << tbuff << std::endl;

            // print operating system info
            f << "Operating System: " << getOSString() << std::endl << std::endl;

            // determine if this was caused by a dll, and name of the dll if it applies
            in_app = !GetModuleFileName(NULL, _mname, MAX_PATH);

            // print who caused the exception and what the exception is
            f << (!in_app ? "Game App" : _mname) << " caused " << _getExceptionString(record->ExceptionCode) << std::endl;

            // print where the exception was raised
            f << "Exception raised at Address " << as_ptr(record->ExceptionAddress) << std::endl;

            // give additional info about an access violation
            if(record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2)
            {
                f << "Copying memory " << (record->ExceptionInformation[0] ? "to " : "from ")
                    << as_ptr(record->ExceptionInformation[1]) << std::endl;
            }

            // print register information
            f << std::endl
              << "Registers: " << std::endl
              << getRegisterString(info->ContextRecord) << std::endl << std::endl;

            // print stacktrace
            win32_backtrace(f, info->ContextRecord, (DWORD)record->ExceptionAddress);

            // close the file to ensure report file is updated
            f.close();
        }
        // give the user instructions on what to do
        MessageBoxA(NULL, CRSH_POPUP_TXT, CRSH_POPUP_TITLE, MB_OK);
    }
	exit(0);

    return EXCEPTION_EXECUTE_HANDLER;
}
#else
// todo: Linux/OS X
#endif // system-specific

ExceptionHandler exchndl;
