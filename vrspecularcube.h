#ifndef VRSPECULARCUBE_H
#define VRSPECULARCUBE_H

#include "vrtexcube.h"

class VRSpecularCube : public VRTexCube
{
public:
    VRSpecularCube();

    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;
};

#endif // VRSPECULARCUBE_H
