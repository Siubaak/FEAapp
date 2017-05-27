#ifndef CCONSTRAINT_H
#define CCONSTRAINT_H
#include "cnode.h"
#include <QVector>

class CConstraint
{
public:
    //Constructed Function
    CConstraint(){}
    CConstraint(int n, CNode node, double cx, double cy);
    //Member Function
    QVector<QVector<double> > c() { return m_vdCe; }
private:
    int m_iN;           //Load number
    QVector<QVector<double> > m_vdCe;   //DOF-Force
};

#endif // CCONSTRAINT_H
