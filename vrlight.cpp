#include "vrlight.h"

VRLight::VRLight()
{
    position = QVector3D(10, 0, 10);
    ambient = QColor(100, 100, 100);
    diffuse = QColor(255, 255, 255);
    specular = QColor(255, 255, 255);
}

QColor VRLight::getAmbient() const
{
    return ambient;
}

void VRLight::setAmbient(const QColor &newAmbient)
{
    ambient = newAmbient;
}

QColor VRLight::getDiffuse() const
{
    return diffuse;
}

void VRLight::setDiffuse(const QColor &newDiffuse)
{
    diffuse = newDiffuse;
}

QColor VRLight::getSpecular() const
{
    return specular;
}

void VRLight::setSpecular(const QColor &newSpecular)
{
    specular = newSpecular;
}

QVector3D VRLight::getPositionLight() const
{
    return position;
}

void VRLight::setPositionLight(const QVector3D &newPosition)
{
    position = newPosition;
}
