#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vrlight.h"
#include <random>
#include <QColorDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Réalité Virtuelle : TP5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBody()
{
    float x = ui->valeurX->value();
    float y = ui->valeurY->value();
    float z = ui->valeurZ->value();

    if (aleatoire){
        int minX = -40;
        int maxX = 40;
        int minY = -40;
        int maxY = 40;
        int minZ = -40;
        int maxZ = 40;
        x = (float) (rand() % (maxX*10 - minX*10) - (maxX*10))/10;
        y = (float) (rand() % (maxY*10 - minY*10) - (maxY*10))/10;
        z = (float) (rand() % (maxZ*10 - minZ*10) - (maxZ*10))/10;
    }

    float tangage = ui->valeurTangage->value();
    float lacet = ui->valeurLacet->value();
    float roulis = ui->valeurRoulis->value();
    QVector3D position = QVector3D(x,y,z);
    QQuaternion orientation = QQuaternion::fromEulerAngles(tangage, lacet, roulis);

    QString newBody = ui->comboCorps->currentText();
    ui->widgetVR->addBody(position, orientation, newBody);
}

void MainWindow::setAleatoire()
{
    aleatoire = !aleatoire;
}

void MainWindow::setSaving()
{
    saving = !saving;
}

void MainWindow::changeSkyboxImage(QString img)
{
    ui->widgetVR->setSkyboxImage(img);
}

void MainWindow::changeAmbientLight()
{
    VRLight* lumiere = ui->widgetVR->getLight();
    QColor col = QColorDialog::getColor(lumiere->getAmbient(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        lumiere->setAmbient(col);
    }
}

void MainWindow::changeDiffuseLight()
{
    VRLight* lumiere = ui->widgetVR->getLight();
    QColor col = QColorDialog::getColor(lumiere->getDiffuse(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        lumiere->setDiffuse(col);
    }
}

void MainWindow::changeSpecularLight()
{
    VRLight* lumiere = ui->widgetVR->getLight();
    QColor col = QColorDialog::getColor(lumiere->getSpecular(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        lumiere->setSpecular(col);
    }
}

void MainWindow::takePicture()
{
    QPixmap img = ui->widgetVR->getImage();
    ui->image->clear();
    ui->image->setPixmap(img);
    if (saving){
        img.save("qpixmap.png", "PNG");
    }
}
