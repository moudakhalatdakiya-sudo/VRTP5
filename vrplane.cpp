#include "vrplane.h"

VRPlane::VRPlane(float newLength, float newWidth)
    :VRBody()
{
    width = newWidth;
    length = newLength;
    globalColor = QColor(0, 255, 0);

    VSFileName = ":/shaders/VS_lit_texture.vsh";
    FSFileName = ":/shaders/FS_lit_texture.fsh";
}

void VRPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->bind();
    }

    program.bind();
    vao.bind();

    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();

    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("texture0", 0);

    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_specular_strength", specStrength);
    program.setUniformValue("light_position",light->getPositionLight());
    program.setUniformValue("eye_position", camera->getPosition());

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void VRPlane::initializeBuffer()
{
    float w = width/2;
    float l = length/2;

    QVector3D A(-l, 0, w);
    QVector3D B(l, 0, w);
    QVector3D C(l, 0, -w);
    QVector3D D(-l, 0, -w);

    QVector2D SW(0, 0);
    QVector2D SE(1, 0);
    QVector2D NE(1, 1);
    QVector2D NW(0, 1);

    QVector3D up(0, 1, 0);

    VRVertex vertexData[] = {
        VRVertex(A, SW, up),
        VRVertex(B, SE, up),
        VRVertex(C, NE, up),
        VRVertex(D, NW, up)
    };

    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();

    numVertices = 4;
    numTriangles = 2;
    numIndices = 0;
}

float VRPlane::getLength() const
{
    return length;
}

void VRPlane::setLength(float newLength)
{
    length = newLength;
}

float VRPlane::getWidth() const
{
    return width;
}

void VRPlane::setWidth(float newWidth)
{
    width = newWidth;
}
