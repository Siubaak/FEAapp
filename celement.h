#ifndef CELEMENT_H
#define CELEMENT_H
#include <QVector>
#include "cnode.h"
#include "cmaterial.h"
#include <Eigen/Dense>
using namespace Eigen;


//If the program needs to be developed, base class may need to be considered.
class Q8
{
public:
    //Constructed Function
    Q8() {}
    Q8(int n, QVector<CNode> node, CMaterial m);
    //Member Function
    Matrix<double, 16, 16> Ke() { return m_matKe; }
    QVector<CNode> node() { return m_vcnNode; }
    int n() { return m_iN; }
private:
    int m_iN;                       //Element number
    QVector<CNode> m_vcnNode;       //Element nodes
    CMaterial m_cmMaterial;         //Element material
    Matrix<double, 16, 16> m_matKe; //Element stiffness matrix
};

#endif // CELEMENT_H
