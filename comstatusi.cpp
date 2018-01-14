#include "comstatusi.h"

ComstatusI::ComstatusI()
{

}
void ComstatusI::sportsCMDStatus(::Ice::Int cmd, ::Ice::Int status, const ::Ice::Current&)
{
    emit cmdStatus(cmd,status);
}
