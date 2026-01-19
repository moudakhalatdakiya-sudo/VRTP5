#include "vrwidget.h"

VRWidget::VRWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    timer = new QTimer();
    angleY = 5;

    grabKeyboard();
}

VRWidget::~VRWidget()
{
}

VRLight *VRWidget::getLight() const
{
    return light;
}

VRScene *VRWidget::getScene() const
{
    return scene;
}

void VRWidget::update()
{
    QTime currentTime = QTime::currentTime();
    float t = lastTime.msecsTo(currentTime);
    lastTime = currentTime;
    float t2 = startTime.msecsTo(currentTime);

    if (animationOn) {
        scene->update(t, true);
        QOpenGLWidget::update();

        if (bounceAnimation){
            world->setPosition(trajectory->pos(t2*0.001));
        }
        if (animationOnLight){
            this->rotateLight(0.01);
        }
        if (animationCamera){
            QVector3D newPosCam(
                2*light->getPositionLight().x(),
                2*light->getPositionLight().y(),
                2*light->getPositionLight().z()
                );
            camera->setPosition(newPosCam);
        }
        else{
            camera->setRho(20);
            camera->setPhi(M_PI_4);
            camera->setTheta(0);
        }
        if (targetCamera){
            camera->setTarget(world->getPosition());
        }
        else{
            camera->setTarget(QVector3D(0,0,0));
        }
    }
    QOpenGLWidget::update();
}

void VRWidget::changeFov(int fov)
{
    camera->setFov(fov);
    QOpenGLWidget::update();
}

void VRWidget::startAnimation()
{
    startTime = QTime::currentTime();
    lastTime = QTime::currentTime();
    animationOn = !animationOn;
    this->update();
}

void VRWidget::startAnimationLight()
{
    animationOnLight = !animationOnLight;
    this->update();
}

void VRWidget::startAnimationCamera()
{
    animationCamera = !animationCamera;
    this->update();
}

void VRWidget::changeBounce()
{
    bounceAnimation = !bounceAnimation;
}

void VRWidget::targetOnPlanet()
{
    targetCamera = !targetCamera;
}

void VRWidget::changeOpacity(int val)
{
    plane->setOpacity(val * 0.01f);
    QOpenGLWidget::update();
}

void VRWidget::changeSize(int value)
{
    body->setScale(value*0.1f);
    QOpenGLWidget::update();
}

void VRWidget::changeSaturation(int value)
{
    int gris = (int)(2.55f * value);
    body->setGlobalColor(QColor(gris, gris, gris));
    QOpenGLWidget::update();
}

void VRWidget::changeCulling()
{
    bool culling = !body->getCulling();
    body->setCulling(culling);
    QOpenGLWidget::update();
}

void VRWidget::changeWireframe()
{
    bool wireframe = !world->getWireframe();
    world->setWireframe(wireframe);
    QOpenGLWidget::update();
}

void VRWidget::addBody(QVector3D pos, QQuaternion orientation, QString corps)
{
    this->makeCurrent();

    VRBody* newBody = new VRCube();

    if (corps == "Dé"){
        newBody = new VRDice();
        newBody->setTexture(":/textures/dice_texture.jpg");
    }
    else if (corps == "Cube texturé"){
        newBody = new VRTexCube();
        newBody->setTexture(":/textures/polytech_logo.jpg");
    }
    else if (corps == "Cube Speculaire"){
        newBody = new VRSpecularCube();
        dynamic_cast<VRSpecularCube*>(newBody)->setCubeTexture(
            ":/textures/Ciel/left.jpg",
            ":/textures/Ciel/right.jpg",
            ":/textures/Ciel/front.jpg",
            ":/textures/Ciel/back.jpg",
            ":/textures/Ciel/top.jpg",
            ":/textures/Ciel/bottom.jpg"
            );
    }
    else if (corps == "Tore"){
        newBody = new VRTorus();
        newBody->setFSFileName(":/shaders/FS_lit_checker.fsh");
    }
    else if (corps == "Tore Speculaire"){
        newBody = new VRSpecularTorus();
        dynamic_cast<VRSpecularTorus*>(newBody)->setCubeTexture(
            ":/textures/Ciel/left.jpg",
            ":/textures/Ciel/right.jpg",
            ":/textures/Ciel/front.jpg",
            ":/textures/Ciel/back.jpg",
            ":/textures/Ciel/top.jpg",
            ":/textures/Ciel/bottom.jpg"
            );
    }
    else if (corps == "Planete"){
        newBody = new VRPlanet();
        newBody->setTexture(":/textures/2k_earth_daymap.jpg");
    }
    else if (corps == "Sphere"){
        newBody = new VRSphere();
    }
    else if (corps == "Sphere Speculaire"){
        newBody = new VRSpecularSphere();
        dynamic_cast<VRSpecularSphere*>(newBody)->setCubeTexture(
            ":/textures/Ciel/left.jpg",
            ":/textures/Ciel/right.jpg",
            ":/textures/Ciel/front.jpg",
            ":/textures/Ciel/back.jpg",
            ":/textures/Ciel/top.jpg",
            ":/textures/Ciel/bottom.jpg"
            );
    }
    else if (corps == "Plan"){
        newBody = new VRPlane();
        newBody->setLight(light);
        newBody->setTexture(":/textures/wood.png");
    }

    newBody->setLight(light);
    newBody->setPosition(pos);
    newBody->setOrientation(orientation);
    newBody->initialize();
    newBody->setCamera(camera);
    scene->append(newBody);
}

void VRWidget::setSkyboxImage(QString img)
{
    this->makeCurrent();
    skybox->setCubeTexture(":/textures/"+img+"/left.jpg",
                           ":/textures/"+img+"/right.jpg",
                           ":/textures/"+img+"/front.jpg",
                           ":/textures/"+img+"/back.jpg",
                           ":/textures/"+img+"/top.jpg",
                           ":/textures/"+img+"/bottom.jpg");
    QOpenGLWidget::update();
}

void VRWidget::changeXLight(double newX)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(newX, pos.y(), pos.z()));
    sun->setPosition(QVector3D(newX, pos.y(), pos.z()));
    QOpenGLWidget::update();
}

void VRWidget::changeYLight(double newY)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), newY, pos.z()));
    sun->setPosition(QVector3D(pos.x(), newY, pos.z()));
    QOpenGLWidget::update();
}

void VRWidget::changeZLight(double newZ)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), pos.y(), newZ));
    sun->setPosition(QVector3D(pos.x(), pos.y(), newZ));
    QOpenGLWidget::update();
}

void VRWidget::changeSpecCoeff(int newCoeff)
{
    scene->setSpecStrength(newCoeff);
    QOpenGLWidget::update();
}

void VRWidget::rotateLight(float angle)
{
    QVector3D center = scene->getPosition();
    QVector3D pos = light->getPositionLight();
    float x_new = (pos.x()-center.x())*cos(angle)+(pos.z()-center.z())*sin(angle);
    float z_new = -(pos.x()-center.x())*sin(angle)+(pos.z()-center.z())*cos(angle);
    light->setPositionLight(QVector3D(x_new,pos.y(),z_new));
    sun->setPosition(QVector3D(x_new,pos.y(),z_new));
}

void VRWidget::changeStereo()
{
    stereo = !stereo;
}

void VRWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    camera = new VRSphericalCamera();
    camera->setFov(90.0f);
    camera->setZMin(1);
    camera->setZMax(800);

    light = new VRLight();
    sun = new VRSphere();
    sun->setPosition(light->getPositionLight());
    sun->setTexture(":/textures/sun_texture.jpg",true,true);
    sun->initialize();

    body = new VRTexCube();
    body->setPosition(QVector3D(4, 4, 8));
    body->setScale(3);
    body->setTexture(":/textures/polytech_logo.jpg");
    body->initialize();

    cube = new VRCube();
    cube->setPosition(QVector3D(8, 4, 8));
    cube->setScale(3);
    cube->initialize();

    dice = new VRDice();
    dice->setPosition(QVector3D(0, 4, 8));
    dice->setScale(3);
    dice->setTexture(":/textures/dice_texture.jpg");
    dice->initialize();

    plane = new VRPlane(40, 40);
    plane->setPosition(QVector3D(0, -2, -4));
    plane->setTexture(":/textures/wood.png");
    plane->initialize();

    trajectory = new VRBounce();

    world = new VRPlanet(2);
    world->setPosition(QVector3D(0, 2, 0));
    world->setTexture(":/textures/2k_earth_daymap.jpg", true, true);
    world->initialize();

    torus = new VRTorus();
    torus->setPosition(QVector3D(0, 5, -10));
    torus->initialize();

    skybox = new VRSkyBox();
    skybox->setPosition(QVector3D(0,0,0));
    skybox->setScale(300);
    skybox->setCubeTexture(":/textures/Ciel/left.jpg",
                           ":/textures/Ciel/right.jpg",
                           ":/textures/Ciel/front.jpg",
                           ":/textures/Ciel/back.jpg",
                           ":/textures/Ciel/top.jpg",
                           ":/textures/Ciel/bottom.jpg");
    skybox->setCamera(camera);
    skybox->initialize();

    specCube = new VRSpecularCube();
    specCube->setPosition(QVector3D(0,0,4));
    specCube->setScale(5);
    specCube->initialize();

    scene = new VRScene();
    scene->setPosition(QVector3D(0,0,0));
    scene->append(dice);
    scene->append(plane);
    scene->append(world);
    scene->append(torus);
    scene->append(sun);
    scene->setCamera(camera);
    scene->setLight(light);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void VRWidget::resizeGL(int w, int h)
{
    float aspect = ((float)w)/h;
    camera->setAspect(aspect);
    glViewport(0, 0, w, h);
}

void VRWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skybox->draw();

    if (stereo){
        glColorMask(true, false, false, false);
        camera->setCameraType(VR_CAMERA_LEFT);
        scene->draw();

        glClear(GL_DEPTH_BUFFER_BIT);

        glColorMask(false, true, true, false);
        camera->setCameraType(VR_CAMERA_RIGHT);
        scene->draw();

        glColorMask(true,true,true,false);
    }
    else {
        scene->draw();
    }
}

void VRWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

void VRWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) / width();
    float dy = (event->position().y() - oldPos.y()) / height();

    camera->setPhi(camera->getPhi() + qDegreesToRadians(180 * dy));
    camera->setTheta(camera->getTheta() + qDegreesToRadians(180 * dx));

    QOpenGLWidget::update();
    oldPos = event->pos();
}

void VRWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = camera->getPosition();
    float delta = 0.2f;

    if (event->key() == Qt::Key_Left)  camPos.setX(camPos.x() - delta);
    if (event->key() == Qt::Key_Right) camPos.setX(camPos.x() + delta);
    if (event->key() == Qt::Key_Up)    camPos.setY(camPos.y() + delta);
    if (event->key() == Qt::Key_Down)  camPos.setY(camPos.y() - delta);

    camera->setPosition(camPos);
    QOpenGLWidget::update();
}

void VRWidget::wheelEvent(QWheelEvent *event)
{
    int newRho = event->angleDelta().y();
    if (camera->getRho()+newRho>0 && camera->getRho()+newRho<200)
        camera->setRho(camera->getRho()+newRho);
    QOpenGLWidget::update();
}

QPixmap VRWidget::getImage()
{
    makeCurrent();

    QOpenGLFramebufferObject* fbo =
        new QOpenGLFramebufferObject(width(), height());
    fbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo->bind();
    paintGL();
    QImage img(fbo->toImage(true));
    fbo->release();
    return QPixmap::fromImage(img);
}
