#ifndef VRSCENE_H
#define VRSCENE_H

#include <QList>
#include "vrbody.h"
#include "vrlight.h"

class VRScene : public QList<VRBody*>
{
public:
    VRScene();
    void setCamera(VRCamera* pCamera);
    void translate(QVector3D vec);
    void rotate(float angle, QVector3D axis);
    void draw();

    VRLight *getLight() const;
    void setLight(VRLight *newLight);

    float getSpecStrength() const;
    void setSpecStrength(float newSpecStrength);

    QVector3D getPosition() const;
    void setPosition(const QVector3D &newPosition);

    void update(float time, bool relative = true);

protected:
    VRCamera* camera;
    VRLight* light;
    float specStrength;
    QVector3D position;
};

#endif // VRSCENE_H
