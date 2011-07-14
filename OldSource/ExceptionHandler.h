#ifndef __EXC_HNDLR_H__
#define __EXC_HNDLR_H__
// nfries88's exception handler code

#define REPORT_FILE "CLIENT.RPT"
#define CRSH_POPUP_TITLE "Crash!"
#define CRSH_POPUP_TXT "The client crashed! Please supply \"" REPORT_FILE "\" to the developers. Sorry for any inconvenience."

#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>

class ExceptionHandler
{
public:
    ExceptionHandler();
    ~ExceptionHandler();

protected:
    // for uninstalling the exception handler
    LPTOP_LEVEL_EXCEPTION_FILTER previous_exception_filter;
    // last error mode in the system
    UINT last_error_mode;
    // called when an uncaught exception occurs
    static LONG WINAPI exception_filter(PEXCEPTION_POINTERS info);
};
#else
// TODO: Linux/OS X
#endif // system-specific

#endif //__EXC_HNDLR_H__
