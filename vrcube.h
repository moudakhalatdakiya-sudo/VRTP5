#ifndef VRCUBE_H
#define VRCUBE_H

#include "vrbody.h"

class VRCube : public VRBody
{
public:
    VRCube();

public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // VRCUBE_H
