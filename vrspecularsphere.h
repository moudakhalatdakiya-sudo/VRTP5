#ifndef VRSPECULARSPHERE_H
#define VRSPECULARSPHERE_H

#include "vrsphere.h"

class VRSpecularSphere : public VRSphere
{
public:
    VRSpecularSphere();
    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;
};

#endif // VRSPECULARSPHERE_H
