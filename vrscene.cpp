#include "vrscene.h"

VRScene::VRScene()
{

}

void VRScene::setCamera(VRCamera *pCamera)
{
    camera = pCamera;
    foreach (VRBody* body, *this) {
        body->setCamera(pCamera);
    }
}

void VRScene::translate(QVector3D vec)
{
    foreach (VRBody* body, *this) {
        body->translate(vec);
    }
}

void VRScene::rotate(float angle, QVector3D axis)
{
    foreach (VRBody* body, *this) {
        body->rotate(angle, axis);
    }
}

void VRScene::draw()
{
    foreach (VRBody* body, *this) {
        body->draw();
    }
}

VRLight *VRScene::getLight() const
{
    return light;
}

void VRScene::setLight(VRLight *newLight)
{
    light = newLight;
    foreach (VRBody* body, *this) {
        body->setLight(newLight);
    }
}

float VRScene::getSpecStrength() const
{
    return specStrength;
}

void VRScene::setSpecStrength(float newSpecStrength)
{
    specStrength = newSpecStrength;
    foreach (VRBody* body, *this) {
        body->setSpecStrength(newSpecStrength);
    }
}

QVector3D VRScene::getPosition() const
{
    return position;
}

void VRScene::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

void VRScene::update(float time, bool relative)
{
    foreach (VRBody* body, *this) {
        body->update(time, relative);
    }
}
