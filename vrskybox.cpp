#include "vrskybox.h"

VRSkyBox::VRSkyBox(): VRBody()
{
    VSFileName = ":/shaders/VS_skybox_texture.vsh";
    FSFileName = ":/shaders/FS_skybox_texture.fsh";
}

void VRSkyBox::initializeBuffer()
{
    QVector3D A(-1, -1, 1);
    QVector3D B(1, -1, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(-1, 1, 1);
    QVector3D E(-1,-1,-1);
    QVector3D F(1, -1, -1);
    QVector3D G(1, 1, -1);
    QVector3D H(-1, 1, -1);

    QVector3D vertexData[] = {
        A, B, C, D,
        H, G, F, E,
        A, D, H, E,
        B, F, G, C,
        D, C, G, H,
        A, E, F, B,
    };

    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();
}

void VRSkyBox::initializeVAO()
{
    program.bind();
    vao.bind();
    vbo.bind();
    ibo.bind();

    program.setAttributeBuffer("vr_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("vr_Position");

    vao.release();
    program.release();
}

void VRSkyBox::draw()
{
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (texture) {
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE0);
        texture->bind();
    }

    program.bind();
    vao.bind();

    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("texture0", 0);

    for (int i =0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    vao.release();
    program.release();

    if (texture) {
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE0);
        texture->bind();
    }
}

void VRSkyBox::setCubeTexture(QString leftImage, QString rightImage, QString frontImage, QString backImage, QString topImage, QString bottomImage)
{
    texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    texture->create();

    QImage posX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posY = QImage(topImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negY = QImage(bottomImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posZ = QImage(frontImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negZ = QImage(backImage).convertToFormat(QImage::Format_RGBA8888);

    texture->setSize(posX.width(),posX.height(),posX.depth());
    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    texture->allocateStorage();

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     posX.constBits(),
                     Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     negX.constBits(),
                     Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     posY.constBits(),
                     Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     negY.constBits(),
                     Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     posZ.constBits(),
                     Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                     QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8,
                     negZ.constBits(),
                     Q_NULLPTR);

    texture->generateMipMaps();
    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}
