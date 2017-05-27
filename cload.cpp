#include "cload.h"

CLoad::CLoad(int n, CNode node, double fx, double fy)
{
    m_iN = n;
    QVector<double> q1;
    q1<<node.n()*2 - 2;
    q1<<fx;
    m_vdFe<<q1;
    QVector<double> q2;
    q2<<node.n()*2 - 1;
    q2<<fy;
    m_vdFe<<q2;
}

