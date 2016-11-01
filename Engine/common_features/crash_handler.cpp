/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014-2016 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL_messagebox.h>
#include <cstdlib>
#include <signal.h>
#ifdef _WIN32
    #include <windows.h>
    #include <dbghelp.h>
#elif ((__linux__) && !(__ANDROID__) || __APPLE__)
    #include <execinfo.h>
    #include <unistd.h>
#endif

#include "crash_handler.h"
#include "logger.h"

#include <version.h>
#include <graphics/window.h>

#define STACK_FORMAT    "====Stack trace====\n" \
                        "%s\n" \
                        "===================\n" \
                        "%s"

static const char* g_messageToUser =
        "================================================\n"
        "            Additional information:\n"
        "================================================\n"
        _FILE_DESC " version: " _FILE_VERSION _FILE_RELEASE "\n"
        "GIT Revision code: " GIT_VERSION "\n"
        "================================================\n"
        " Please send this log file to the developers by one of ways:\n"
        " - Via contact form:          http://wohlsoft.ru/forum/memberlist.php?mode=contactadmin\n"
        " - Official forums:           http://wohlsoft.ru/forum/\n"
        " - Make issue at GitHub repo: https://github.com/WohlSoft/PGE-Project\n\n"
        "================================================\n";

#ifdef _WIN32
//
// http://blog.aaronballman.com/2011/04/generating-a-stack-crawl/
//
static bool GetStackWalk( std::string &outWalk )
{
    // Set up the symbol options so that we can gather information from the current
    // executable's PDB files, as well as the Microsoft symbol servers.  We also want
    // to undecorate the symbol names we're returned.  If you want, you can add other
    // symbol servers or paths via a semi-colon separated list in SymInitialized.
    ::SymSetOptions( SYMOPT_DEFERRED_LOADS | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_UNDNAME );
    if (!::SymInitialize( ::GetCurrentProcess(), "http://msdl.microsoft.com/download/symbols", TRUE )) return false;

    // Capture up to 25 stack frames from the current call stack.  We're going to
    // skip the first stack frame returned because that's the GetStackWalk function
    // itself, which we don't care about.
    PVOID addrs[ 400 ] = { 0 };
    USHORT frames = CaptureStackBackTrace( 1, 400, addrs, nullptr );

    for (USHORT i = 0; i < frames; i++) {
        // Allocate a buffer large enough to hold the symbol information on the stack and get
        // a pointer to the buffer.  We also have to set the size of the symbol structure itself
        // and the number of bytes reserved for the name.
        ULONG64 buffer[ (sizeof( SYMBOL_INFO ) + 1024 + sizeof( ULONG64 ) - 1) / sizeof( ULONG64 ) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof( SYMBOL_INFO );
        info->MaxNameLen = 1024;

        // Attempt to get information about the symbol and add it to our output parameter.
        DWORD64 displacement = 0;
        if (::SymFromAddr( ::GetCurrentProcess(), (DWORD64)addrs[ i ], &displacement, info )) {
            outWalk.append( info->Name, info->NameLen );
            outWalk.append( "\n" );
        }
    }

        ::SymCleanup( ::GetCurrentProcess() );

    return true;
}
#endif

static std::string getStacktrace()
{
    #ifdef _WIN32
        //StackTracer tracer;
        //tracer.runStackTracerForAllThreads();
        //return tracer.theOutput();
        //dbg::stack s;
        //std::stringstream out;
        //std::copy(s.begin(), s.end(), std::ostream_iterator<dbg::stack_frame>(out, "\n"));
        std::string stack;
        GetStackWalk(stack);
        return stack;
    #elif ((__linux__) && !(__ANDROID__) || __APPLE__)
        void*  array[400];
        size_t size;
        char** strings;

        #ifdef DEBUGTRACER
        pLogDebug("Requesting backtrace...");
        #endif
        size = backtrace(array, 400);

        #ifdef DEBUGTRACER
        pLogDebug("Converting...");
        #endif
        strings = backtrace_symbols(array, size);

        #ifdef DEBUGTRACER
        pLogDebug("Initializing std::string...");
        #endif
        std::string bkTrace("");

        #ifdef DEBUGTRACER
        pLogDebug("Filling std::string...");
        #endif
        for(size_t j = 0; j < size; j++)
        {
             bkTrace.append(strings[j]);
             bkTrace.push_back('\n');
        }

        #ifdef DEBUGTRACER
        pLogDebug("DONE!");
        #endif
        return bkTrace;
    #else
        return std::string("<Stack trace not supported for this platform!>");
    #endif
}

CrashHandler::CrashHandler()
{}

static void msgBox(QString title, QString text)
{
    std::string ttl = title.toStdString();
    std::string msg = text.toStdString();
    SDL_MessageBoxData mbox;
    SDL_MessageBoxButtonData mboxButton;
    const SDL_MessageBoxColorScheme colorScheme =
    {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 200, 200, 200 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 150, 150, 150 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255, 255, 255 }
        }
    };

    mboxButton.buttonid = 0;
    mboxButton.flags    = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT|SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    mboxButton.text     = "Ok";

    mbox.flags          = SDL_MESSAGEBOX_ERROR;
    mbox.window         = PGE_Window::window;
    mbox.title          = ttl.c_str();
    mbox.message        = msg.c_str();
    mbox.numbuttons     = 1;
    mbox.buttons        = &mboxButton;
    mbox.colorScheme    = &colorScheme;

    SDL_ShowMessageBox(&mbox, NULL);
}

static void abortEngine(int signal)
{
    SDL_Quit();
    CloseLog();
    exit(signal);
}

void CrashHandler::crashByUnhandledException()
{
    LogWarning("<Unhandled exception!>");
    msgBox(
          //% "Unhandled exception!"
          qtTrId("CRASH_UNHEXC_TITLE"),
          //% "Engine has crashed because accepted unhandled exception!"
          qtTrId("CRASH_UNHEXC_MSG"));
    abortEngine(-1);
}

void CrashHandler::crashByFlood()
{
    LogWarning("<Out of memory!>");
    msgBox(
          //% "Out of memory!"
          qtTrId("CRASH_OUT_OF_MEM_TITLE"),
          //% "Engine has crashed because out of memory! Try to close other applications and restart game."
          qtTrId("CRASH_OUT_OF_MEM_MSG"));
    abortEngine(-2);
}



static void handle_signal(int signal, siginfo_t * siginfo, void * /*context*/)
{
    // Find out which signal we're handling
    switch (signal)
    {
#ifndef _WIN32  //Unsupported signals by Windows
    case SIGHUP:
        pLogWarning("Terminal was closed");
        abortEngine(signal);
        break;

    case SIGQUIT:
        pLogWarning("<Quit command>");
        abortEngine(signal);
        break;

    case SIGKILL:
        pLogFatal("<killed>");
        abortEngine(signal);
        break;

    case SIGALRM:
    {
        pLogFatal("<alarm() time out!>");
        msgBox(
              //% "Time out!"
              qtTrId("CRASH_TIMEOUT_TITLE"),
              //% "Engine has abourted because alarm() time out!"
              qtTrId("CRASH_TIMEOUT_MSG"));
        abortEngine(signal);
        break;
    }
    case SIGBUS:
    {
        std::string stack = getStacktrace();
        if(siginfo)
        {
            switch(siginfo->si_code)
            {
            case BUS_ADRALN:
                pLogFatal("<Physical memory address error: wrong address alignment>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            case BUS_ADRERR:
                pLogFatal("<Physical memory address error: physical address is not exists>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            case BUS_OBJERR:
                pLogFatal("<Physical memory address error: object specific hardware error>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            default:
                pLogFatal("<Physical memory address error>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
            }

        }
        else
        {
            pLogFatal("<Physical memory address error>\n"
                      STACK_FORMAT,
                      stack.c_str(), g_messageToUser);
        }

        msgBox(
              //% "Physical memory address error!"
              qtTrId("CRASH_BUS_TITLE"),
              //% "Engine has crashed because a physical memory address error"
              qtTrId("CRASH_BUS_MSG"));
        abortEngine(signal);
        break;
    }
    case SIGURG:
    case SIGUSR1:
    case SIGUSR2:
        break;

    case SIGILL:
    {
        std::string stack = getStacktrace();
        pLogFatal("<Wrong CPU Instruction>\n"
                  STACK_FORMAT,
                  stack.c_str(), g_messageToUser);
        msgBox(
              //% "Wrong CPU Instruction!"
              qtTrId("CRASH_ILL_TITLE"),
              //% "Engine has crashed because a wrong CPU instruction"
              qtTrId("CRASH_ILL_MSG"));
        abortEngine(signal);
        break;
    }
#endif

    case SIGFPE:
    {
        std::string stack = getStacktrace();
        if(siginfo)
        {
            switch(siginfo->si_code)
            {
            case FPE_INTDIV:
                pLogFatal("<wrong arithmetical operation: division of integer number by zero>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            case FPE_FLTDIV:
                pLogFatal("<wrong arithmetical operation: division of floating point number by zero>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            case FPE_INTOVF:
                pLogFatal("<wrong arithmetical operation: integer number max bits size overflot>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            case FPE_FLTOVF:
                pLogFatal("<wrong arithmetical operation: floating point number max bits size overflot>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            default:
                pLogFatal("<wrong arithmetical operation>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
            }
        }
        else
        {
            pLogFatal("<wrong arithmetical operation>\n"
                      STACK_FORMAT,
                      stack.c_str(), g_messageToUser);
        }
        msgBox(
              //% "Wrong arithmetical operation"
              qtTrId("CRASH_FPE_TITLE"),
              //% "Engine has crashed because of a wrong arithmetical operation!"
              qtTrId("CRASH_FPE_MSG"));
        abortEngine(signal);
        break;
    }
    case SIGABRT:
    {
        std::string stack = getStacktrace();
        pLogFatal("<Aborted!>\n"
                 STACK_FORMAT,
                 stack.c_str(), g_messageToUser);
        msgBox(
              //% "Aborted"
              qtTrId("CRASH_ABORT_TITLE"),
              //% "Engine has been aborted because critical error was occouped."
              qtTrId("CRASH_ABORT_TITLE."));
        abortEngine(signal);
        break;

    }
    case SIGSEGV:
    {
        #ifdef DEBUGTRACER
        pLogDebug("\n===========================================================\n"
                  "Attempt to take a backtrace..."
                  "(if log ends before \"DONE\" will be shown, seems also trouble in the backtracing function too...)");
        #endif
        std::string stack = getStacktrace();
        if(siginfo)
        {
            switch(siginfo->si_code)
            {
            case SEGV_MAPERR:
                pLogFatal("<Segmentation fault crash!: Address is not pointing to object!!!>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;

            case SEGV_ACCERR:
                pLogFatal("<Segmentation fault crash!: Wrong access rights for address!!!>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;

            default:
                pLogFatal("<Segmentation fault crash!>\n"
                          STACK_FORMAT,
                          stack.c_str(), g_messageToUser);
                break;
            }
        } else {
            pLogFatal("<Segmentation fault crash!>\n"
                      STACK_FORMAT,
                      stack.c_str(), g_messageToUser);
        }

        msgBox(
              //% "Segmentation fault"
              qtTrId("CRASH_SIGSEGV_TITLE"),

              /*% "Engine has crashed because of a Segmentation fault.\n"
                  "Run debugging with a built in debug mode application\n"
                  "and retry your recent actions to get more detailed information." */
              qtTrId("CRASH_SIGSEGV_MSG."));
        abortEngine(signal);
        break;
    }
    case SIGINT:
    {
        pLogFatal("<Interrupted!>");
        msgBox(
              //% "Interrupt"
              qtTrId("CRASH_INT_TITLE"),
              //% "Engine has been interrupted"
              qtTrId("CRASH_INT_MSG"));

        abortEngine(signal);
        break;
    }

    default:
        return;
    }
}

struct sigaction act;

void CrashHandler::initSigs()
{
    std::set_new_handler(&crashByFlood);
    std::set_terminate(&crashByUnhandledException);

    memset(&act, 0, sizeof(struct sigaction));
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;

    #ifndef _WIN32 //Unsupported signals by Windows
    sigaction(SIGHUP,  &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    sigaction(SIGKILL, &act, NULL);
    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGURG,  &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigaction(SIGBUS,  &act, NULL);
    #endif
    sigaction(SIGILL,  &act, NULL);
    sigaction(SIGFPE,  &act, NULL);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGINT,  &act, NULL);
    sigaction(SIGABRT, &act, NULL);
}
/* Signals End */
