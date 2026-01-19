#ifndef VRSPECULARTORUS_H
#define VRSPECULARTORUS_H

#include "vrtorus.h"

class VRSpecularTorus : public VRTorus
{
public:
    VRSpecularTorus();
    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;
};

#endif // VRSPECULARTORUS_H

