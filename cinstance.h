#ifndef CINSTANCE_H
#define CINSTANCE_H
#include <QVector>
#include "cnode.h"
#include "celement.h"
#include "cmaterial.h"
#include "cload.h"
#include "cconstraint.h"
#include <Eigen/Dense>
#include <Eigen/LU>
using namespace Eigen;


class CInstance
{
public:
    //Constructed Function
    CInstance() {}
    CInstance(int n, QVector<Q8> element, QVector<CLoad> load, QVector<CConstraint> constraint);
    //Member Funtion
    Matrix<double, Dynamic, 1> u() { return m_matU; }
    Matrix<double, Dynamic, 1> R() { return m_matR; }
private:
    QVector<Q8> m_velement;     //Store element information
    QVector<CLoad> m_vload;     //Store load information
    QVector<CConstraint> m_vconstraint;     //Store load information
    MatrixXd m_matK;    //Global Matrix
    MatrixXd m_matKp;   //Global Matrix after processing
    Matrix<double, Dynamic, 1> m_matF;  //Force
    Matrix<double, Dynamic, 1> m_matFp;  //Force after processing
    Matrix<double, Dynamic, 1> m_matU;  //Displacement
    Matrix<double, Dynamic, 1> m_matR;  //Reaction
};

#endif // CINSTANCE_H
