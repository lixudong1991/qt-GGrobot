#include "comstatusi.h"

ComstatusI::ComstatusI()
{

}
void ComstatusI::sportsCMDStatus(::Ice::Int cmd, ::Ice::Int status, const ::Ice::Current&)
{
     LOGI("sportsCMDStatus  Command: "<<cmd<<" Status: "<<status);
     emit cmdStatus(cmd,status);
}
