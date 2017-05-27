#ifndef CLOAD_H
#define CLOAD_H
#include <QVector>
#include "cnode.h"

class CLoad
{
public:
    //Constructed Function
    CLoad(){}
    CLoad(int n, CNode node, double fx, double fy);
    //Member Function
    QVector<QVector<double> > f() { return m_vdFe; }
private:
    int m_iN;           //Load number
    QVector<QVector<double> > m_vdFe;   //DOF-Force
};

#endif // CLOAD_H
