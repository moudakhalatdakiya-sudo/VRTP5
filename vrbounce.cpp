#include "vrbounce.h"

VRBounce::VRBounce(float hMax, float tMax):VRCurve()
{
    hmax = hMax;
    tmax = tMax;

    FSFileName = ":/shaders/FS_simple.fsh";
    VSFileName = ":/shaders/VS_simpler.vsh";
}

float VRBounce::getHmax()
{
    return hmax;
}

float VRBounce::getTmax()
{
    return tmax;
}

void VRBounce::setHmax(float newHmax){

    hmax=newHmax;

}
void VRBounce::setTmax(float newTmax){

    tmax=newTmax;
}

float VRBounce::x(double t)
{
    return 0;
}

float VRBounce::y(double t)
{
    float a=-hmax/pow(tmax,2);
    float b=2*hmax/tmax;
    float c = fmod(t, 2*tmax);
    return a*pow(c,2)+b*c;
}

float VRBounce::z(double t)
{
    return 0;
}
