#include "cinstance.h"

CInstance::CInstance(int n, QVector<Q8> element, QVector<CLoad> load, QVector<CConstraint> constraint)
{
    m_velement = element;
    m_vload = load;
    m_vconstraint = constraint;
    m_matK = MatrixXd::Zero(n, n);
    m_matKp = MatrixXd::Zero(n, n);
    m_matF = MatrixXd::Zero(n, 1);
    m_matFp = MatrixXd::Zero(n, 1);
    m_matU = MatrixXd::Zero(n, 1);
    m_matR = MatrixXd::Zero(n, 1);
    for (int k = 0; k != element.size(); ++k)
        for (int i = 0; i != 8; ++i)
            for (int j = 0; j != 8; ++j)
            {
                m_matK(element[k].node()[i].n()*2 - 2, element[k].node()[j].n()*2 - 2) = m_matK(element[k].node()[i].n()*2 - 2, element[k].node()[j].n()*2 - 2) + element[k].Ke()(i*2, j*2);
                m_matK(element[k].node()[i].n()*2 - 2, element[k].node()[j].n()*2 - 1) = m_matK(element[k].node()[i].n()*2 - 2, element[k].node()[j].n()*2 - 1) + element[k].Ke()(i*2, j*2 + 1);
                m_matK(element[k].node()[i].n()*2 - 1, element[k].node()[j].n()*2 - 2) = m_matK(element[k].node()[i].n()*2 - 1, element[k].node()[j].n()*2 - 2) + element[k].Ke()(i*2 + 1, j*2);
                m_matK(element[k].node()[i].n()*2 - 1, element[k].node()[j].n()*2 - 1) = m_matK(element[k].node()[i].n()*2 - 1, element[k].node()[j].n()*2 - 1) + element[k].Ke()(i*2 + 1, j*2 + 1);
            }
    for (int i = 0; i != load.size(); ++i)
    {
        m_matF(load[i].f()[0][0], 0) = m_matF(load[i].f()[0][0], 0) + load[i].f()[0][1];
        m_matF(load[i].f()[1][0], 0) = m_matF(load[i].f()[1][0], 0) + load[i].f()[1][1];
    }
    m_matKp = m_matK;
    m_matFp = m_matF;
    for (int i = 0; i != constraint.size(); ++i)
    {
        if (constraint[i].c()[0][1] == 1)
            for (int j = 0; j != n; ++j)
            {
                m_matKp(constraint[i].c()[0][0], j) = 0;
                m_matKp(j, constraint[i].c()[0][0]) = 0;
                m_matKp(constraint[i].c()[0][0], constraint[i].c()[0][0]) = 1;
                m_matFp(constraint[i].c()[0][0], 0) = 0;
            }
        if (constraint[i].c()[1][1] == 1)
            for (int j = 0; j != n; ++j)
            {
                m_matKp(constraint[i].c()[1][0], j) = 0;
                m_matKp(j, constraint[i].c()[1][0]) = 0;
                m_matKp(constraint[i].c()[1][0], constraint[i].c()[1][0]) = 1;
                m_matFp(constraint[i].c()[1][0], 0) = 0;
            }
    }
    m_matU = m_matKp.lu().solve(m_matFp);
    Matrix<double, Dynamic, 1> NetF(m_matK*m_matU);
    m_matR = NetF - m_matF;
}

