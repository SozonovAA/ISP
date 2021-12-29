#include "Log.h"

#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "P7_Trace.h"
#include "P7_Telemetry.h"



namespace utils {

static std::size_t trace_ch_count { 0 };
struct LogVar{
    IP7_Client        *l_pClient    = NULL;

    IP7_Trace         *l_pTrace     = NULL;
    IP7_Trace::hModule l_hModule    = NULL;

    ~LogVar();

};

static std::vector<LogVar> logs;



LogStream::LogStream(std::string _thr_name,
                     std::size_t _thr_numb,
                     std::string _module_name ) :
    thread_name( _thr_name )
  , thread_numb( _thr_numb )
  , module_name( _module_name )
{
    P7_Set_Crash_Handler();
    log_pos = trace_ch_count;
    logs.push_back( LogVar() );
    //create P7 client object
    logs.rbegin()->l_pClient = P7_Create_Client(TM("/P7.Sink=FileTxt "
                                    "/P7.Format=\"{%cn, %tn %ti CPU: %cc} [%tf] "
                                    "( function: %fn ) %lv %ms\" "
                                    "/P7.Trc.Verb=0 /P7.Files=5") );

    //create P7 trace object 1
    logs.rbegin()->l_pTrace = P7_Create_Trace(logs.rbegin()->l_pClient,
        TM( (std::string{ "Trace channel " }
             + std::to_string( trace_ch_count++ ) ).c_str() ) );

    logs.rbegin()->l_pTrace->Register_Thread(TM( thread_name.c_str() ), thread_numb );
    logs.rbegin()->l_pTrace->Register_Module(TM( module_name.c_str() ), &logs.rbegin()->l_hModule);

}

LogStream::~LogStream()
{
    if (logs[log_pos].l_pTrace)
    {
        logs[log_pos].l_pTrace->Release();
        logs[log_pos].l_pTrace = NULL;
    }

    if (logs[log_pos].l_pClient)
    {
        logs[log_pos].l_pClient->Release();
        logs[log_pos].l_pClient = NULL;
    }
}

LogVar::~LogVar()
{

}

void LogStream::write_to_log( std::string&& _message )
{
    logs[log_pos].l_pTrace->P7_TRACE(logs[log_pos].l_hModule, TM( _message.c_str() ) );
    logs[log_pos].l_pTrace->P7_INFO(logs[log_pos].l_hModule, TM( _message.c_str() ) );
    logs[log_pos].l_pTrace->P7_DEBUG(logs[log_pos].l_hModule, TM( _message.c_str() ) );
}

} // namespace utils
