#ifndef VRSPHERICALCAMERA_H
#define VRSPHERICALCAMERA_H

#include "vrstereocamera.h"

class VRSphericalCamera : public VRStereoCamera
{
public:
    VRSphericalCamera();

    float getPhi() const;
    void setPhi(float newPhi);

    float getTheta() const;
    void setTheta(float newTheta);

    float getRho() const;
    void setRho(float newRho);

protected:
    float phi;
    float theta;
    float rho;

private:
    void updateposition();
};

#endif // VRSPHERICALCAMERA_H
