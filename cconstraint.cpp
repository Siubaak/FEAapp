#include "cconstraint.h"

CConstraint::CConstraint(int n, CNode node, double cx, double cy)
{
    m_iN = n;
    QVector<double> q1;
    q1<<node.n()*2 - 2;
    q1<<cx;
    m_vdCe<<q1;
    QVector<double> q2;
    q2<<node.n()*2 - 1;
    q2<<cy;
    m_vdCe<<q2;
}

