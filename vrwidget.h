#ifndef VRWIDGET_H
#define VRWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QOpenGLFramebufferObject>
#include <QTime>
#include "vrbody.h"
#include "vrcamera.h"
#include "vrcube.h"
#include "vrplane.h"
#include "vrsphere.h"
#include "vrplanet.h"
#include "vrtorus.h"
#include "vrtexcube.h"
#include "vrdice.h"
#include "vrscene.h"
#include "vrsphericalcamera.h"
#include "vrskybox.h"
#include "vrlight.h"
#include "vrspecularcube.h"
#include "vrspeculartorus.h"
#include "vrspecularsphere.h"
#include "vrcurve.h"
#include "vrhelix.h"
#include "vrbounce.h"

class VRWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    VRWidget(QWidget *parent = nullptr);
    ~VRWidget();

    VRScene *getScene() const;
    VRLight *getLight() const;

    void setTargetCamera(bool newTargetCamera);

private:
    VRBody* body;
    VRBody* plane;
    VRBody* world;
    VRBody* torus;
    VRBody* dice;
    VRBody* specCube;
    VRSphericalCamera* camera;
    VRScene* scene;
    VRSkyBox* skybox;
    VRLight* light;
    VRBody* cube;
    VRBody* sun;
    QTimer* timer;
    VRCurve* trajectory;
    float angleY;
    bool animationOn = false;
    bool animationOnLight = false;
    bool animationCamera = false;
    bool targetCamera = false;
    bool bounceAnimation = false;
    bool stereo = false;
    float angleX;
    QPointF oldPos;
    bool showSun = false;
    QTime startTime;
    QTime lastTime;

protected slots:
    void update();

public slots:
    void startAnimation();
    void startAnimationLight();
    void startAnimationCamera();
    void changeBounce();
    void targetOnPlanet();
    void changeFov(int);
    void changeOpacity(int);
    void changeSize(int value);
    void changeSaturation(int value);
    void changeCulling();
    void changeWireframe();
    void addBody(QVector3D pos, QQuaternion orientation, QString corps);
    void setSkyboxImage(QString img);
    void changeXLight(double newX);
    void changeYLight(double newY);
    void changeZLight(double newZ);
    void changeSpecCoeff(int newCoeff);
    void rotateLight(float angle);
    void changeStereo();
    QPixmap getImage();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent * event) override;
};

#endif // VRWIDGET_H
