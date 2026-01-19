#include "vrdice.h"

VRDice::VRDice()
    :VRBody()
{
    VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    FSFileName = ":/shaders/FS_lit_texture_cube.fsh";
}

void VRDice::draw()
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

    for (int i =0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
    }
}

QMatrix4x4 VRDice::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return VRBody::modelMatrix() * model;
}

void VRDice::initializeBuffer()
{
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D jaune(1, 1, 0);

    QVector3D avant(0, 0, 1);
    QVector3D arriere(0, 0,-1);
    QVector3D gauche(-1, 0, 0);
    QVector3D droite(1, 0, 0);
    QVector3D dessus(0, 1, 0);
    QVector3D dessous(0, -1, 0);

    QVector3D f1SW(0.5, 0, 0);
    QVector3D f1SE(0.5,0.25, 0);
    QVector3D f1NE(0.75,0.25, 0);
    QVector3D f1NW(0.75, 0, 0);

    QVector3D f2SW(0.5,0.75,0);
    QVector3D f2SE(0.5,1,0);
    QVector3D f2NE(0.75,1,0);
    QVector3D f2NW(0.75,0.75,0);

    QVector3D f3SW(0.75, 1, 0);
    QVector3D f3SE(0.75,0.75,0);
    QVector3D f3NE(1,0.75,0);
    QVector3D f3NW(1,1,0);

    QVector3D f4SW(0.25,1,0);
    QVector3D f4SE(0.25,0.75,0);
    QVector3D f4NE(0.5,0.75,0);
    QVector3D f4NW(0.5,1,0);

    QVector3D f5SW(0.5,0.25,0);
    QVector3D f5SE(0.5,0.5,0);
    QVector3D f5NE(0.75,0.5,0);
    QVector3D f5NW(0.75,0.25,0);

    QVector3D f6SW(0.5,0.5,0);
    QVector3D f6SE(0.5,0.75,0);
    QVector3D f6NE(0.75,0.75,0);
    QVector3D f6NW(0.75,0.5,0);

    QVector3D vertexData[] = {
        A, B, C, D,
        H, G, F, E,
        A, D, H, E,
        B, F, G, C,
        D, C, G, H,
        A, E, F, B,
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune,
        f3SW,f3SE,f3NE,f3NW,
        f4SW,f4SE,f4NE,f4NW,
        f1SW,f1SE,f1NE,f1NW,
        f6SW,f6SE,f6NE,f6NW,
        f5SW,f5SE,f5NE,f5NW,
        f2SW,f2SE,f2NE,f2NW,
        avant,avant,avant,avant,
        arriere,arriere,arriere,arriere,
        gauche,gauche,gauche,gauche,
        droite,droite,droite,droite,
        dessus,dessus,dessus,dessus,
        dessous,dessous,dessous,dessous
    };

    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();

    numVertices = 24;
    numTriangles = 12;
    numIndices = 0;
}

void VRDice::initializeVAO()
{
    program.bind();
    vao.bind();
    vbo.bind();
    ibo.bind();

    program.setAttributeBuffer("vr_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("vr_Position");

    program.setAttributeBuffer("vr_Color", GL_FLOAT, sizeof(QVector3D)*numVertices, 3);
    program.enableAttributeArray("vr_Color");

    program.setAttributeBuffer("vr_TexCoord", GL_FLOAT, sizeof(QVector3D)*48, 3);
    program.enableAttributeArray("vr_TexCoord");

    program.setAttributeBuffer("vr_Normal", GL_FLOAT, sizeof(QVector3D)*72, 3);
    program.enableAttributeArray("vr_Normal");

    vao.release();
    program.release();
}

void VRDice::update(float time, bool relative)
{
    if (relative) {
        int vitAngulaire = 360;
        this->rotate(time*vitAngulaire*0.001, QVector3D(0, 1, 0));
    }
    else {
        int vitAngulaire = 80;
        this->rotate(vitAngulaire*0.1, QVector3D(0, 1, 0));
    }
}
