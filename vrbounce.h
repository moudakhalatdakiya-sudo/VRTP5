#ifndef VRBOUNCE_H
#define VRBOUNCE_H

#include "vrcurve.h"
#include <math.h>

class VRBounce : public VRCurve
{
public:
    VRBounce(float hMax = 5,float tMax = 1);
    float getHmax();
    void setHmax(float newHmax);

    float getTmax();
    void setTmax(float newTmax);

    float x(double t) override;
    float y(double t) override;
    float z(double t) override;

private:
    float hmax;
    float tmax;
};

#endif // VRBOUNCE_H
