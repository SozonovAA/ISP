#include "Log.h"


#include <stdlib.h>
#include <stdio.h>

#include "P7_Trace.h"
#include "P7_Telemetry.h"



namespace utils {

void __cdecl Telemetry_Enable(void *i_pContext, tUINT16 i_wId, tBOOL i_bEnable)
{
    UNUSED_ARG(i_pContext);
    printf("Id=%d, Enable=%d\n", (tUINT32)i_wId, (tUINT32)i_bEnable);
}

void __cdecl Connect(void *i_pContext, tBOOL i_bConnect)
{
    UNUSED_ARG(i_pContext);
    printf("Connect=%d\n", (tUINT32)i_bConnect);
}

static IP7_Client        *l_pClient    = NULL;

static IP7_Trace         *l_pTrace     = NULL;
static IP7_Trace::hModule l_hModule    = NULL;

static IP7_Telemetry     *l_pTelemetry = NULL;
static tUINT16            l_bTID1      = 0;
static tUINT16            l_bTID2      = 0;
static tUINT32            l_dwIdx      = 0;
static stTelemetry_Conf   l_stConf     = {};
static std::size_t trace_ch_count { 0 };

LogStream::LogStream(std::string _thr_name,
                     std::size_t _thr_numb,
                     std::string _module_name ) :
    thread_name( _thr_name )
  , thread_numb( _thr_numb )
  , module_name( _module_name )
{
    P7_Set_Crash_Handler();

    //create P7 client object
    l_pClient = P7_Create_Client(TM("/P7.Sink=FileTxt "
                                    "/P7.Format=\"{%cn, %tn %ti} [%tf] "
                                    "( function: %fn ) %lv %ms\" "
                                    "/P7.Trc.Verb=0 /P7.Files=5") );


    l_stConf.pContext              = NULL;
    l_stConf.pEnable_Callback      = &Telemetry_Enable;
    l_stConf.pTimestamp_Callback   = NULL;
    l_stConf.qwTimestamp_Frequency = 0ull;
    l_stConf.pConnect_Callback     = &Connect;

    //create P7 trace object 1
    l_pTrace = P7_Create_Trace(l_pClient,
        TM( (std::string{ "Trace channel " }
             + std::to_string( trace_ch_count++ ) ).c_str() ) );

    l_pTrace->Register_Thread(TM( thread_name.c_str() ), thread_numb );
    l_pTrace->Register_Module(TM( module_name.c_str() ), &l_hModule);

}

LogStream::~LogStream()
{
    if (l_pTrace)
    {
        l_pTrace->Release();
        l_pTrace = NULL;
    }

    if (l_pClient)
    {
        l_pClient->Release();
        l_pClient = NULL;
    }
}

void LogStream::write_to_log( std::string&& _message )
{
    l_pTrace->P7_TRACE(l_hModule, TM( _message.c_str() ) );
    l_pTrace->P7_INFO(l_hModule, TM( _message.c_str() ) );
    l_pTrace->P7_DEBUG(l_hModule, TM( _message.c_str() ) );
}

} // namespace utils
