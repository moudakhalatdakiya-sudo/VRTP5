#ifndef VRSURFACE_H
#define VRSURFACE_H

/*!
  \file vrsurface.h
  \brief Déclaration de la classe VRSurface.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QtMath>
#include <QtDebug>
#include "vrbody.h"

/*!
 * \class VRSurface
 * \brief classe abstraite, représente une surface paramètrée P(s, t) et texturée
 *
 * Trois fonctions virtuelles pures sont à surcharger dans toute classe fille.
 * x(s,t)
 * y(s,t)
 * z(s,t)
 * Mais il faut aussi définir le bon intervalle des paramètres t et s
 * ainsi que le nombre de segments de la discrétisation de ces deux intervalles.
 */
class VRSurface : public VRBody
{
public:
    VRSurface();
    void draw() override;
    void initializeBuffer() override;

    virtual QVector3D pos(double s, double t) {
        return QVector3D(x(s,t), y(s,t), z(s,t));
    }

protected:
    virtual float x(double s, double t) = 0;
    virtual float y(double s, double t) = 0;
    virtual float z(double s, double t) = 0;

    QVector3D gradS(double s, double t) { return pos(s+ds,t)-pos(s,t); }
    QVector3D gradT(double s, double t) { return pos(s,t+dt)-pos(s,t); }

    QVector3D normal(double s, double t);

    double minT, maxT;
    int numSegT;
    double minS, maxS;
    int numSegS;
    float time = 0;
    double ds = 0.1;
    double dt = 0.1;
};

#endif // VRSURFACE_H
