#include "celement.h"

Q8::Q8(int n, QVector<CNode> node, CMaterial m)
{
    m_iN = n;
    m_vcnNode = node;
    m_cmMaterial = m;
    m_matKe.setZero(16, 16);
    //3x3 Gaussian Integral Coefficient
    QVector<double> Hi;
    Hi<<0.555555555555555;
    Hi<<0.888888888888888;
    Hi<<0.555555555555555;
    QVector<double> x;
    x<<-0.774596669241483;
    x<<0;
    x<<0.774596669241483;
    //Elastic Matrix D
    double D0(m_cmMaterial.E()/(1 - m_cmMaterial.v()*m_cmMaterial.v()));
    Matrix3d D;
    D << D0, D0*m_cmMaterial.v(), 0,
         D0*m_cmMaterial.v(), D0, 0,
         0, 0, D0*(1 - m_cmMaterial.v())/2;
    //Strain Matrix B
    Matrix<double, 3, 16> B;
    //Determinant of Jacobi Matrix J
    double J;
    //Calculate K = SUM(H*B'*D*B*|J|)
    for (int r = 0; r != 3; ++r)
        for (int s = 0; s != 3; ++s)
        {
            //Partial Derivatives of Interpolation Function
            double Nr1((1 - x[s])*(2*x[r] + x[s])/4);   double Ns1((1 - x[r])*(2*x[s] + x[r])/4);
            double Nr2((1 - x[s])*(2*x[r] - x[s])/4);   double Ns2((1 + x[r])*(2*x[s] - x[r])/4);
            double Nr3((1 + x[s])*(2*x[r] + x[s])/4);   double Ns3((1 + x[r])*(2*x[s] + x[r])/4);
            double Nr4((1 + x[s])*(2*x[r] - x[s])/4);   double Ns4((1 - x[r])*(2*x[s] - x[r])/4);
            double Nr5(x[r]*(x[s] - 1));                double Ns5((x[r]*x[r] - 1)/2);
            double Nr6((1 - x[s]*x[s])/2);              double Ns6(-x[s]*(x[r] + 1));
            double Nr7(-x[r]*(x[s] + 1));               double Ns7((1 - x[r]*x[r])/2);
            double Nr8((x[s]*x[s] - 1)/2);              double Ns8(x[s]*(x[r] - 1));
            //Determinant of Jacobi Matrix J
            double LT(Nr1*node[0].x() + Nr2*node[1].x() + Nr3*node[2].x() + Nr4*node[3].x() + Nr5*node[4].x() + Nr6*node[5].x() + Nr7*node[6].x() + Nr8*node[7].x());
            double RT(Nr1*node[0].y() + Nr2*node[1].y() + Nr3*node[2].y() + Nr4*node[3].y() + Nr5*node[4].y() + Nr6*node[5].y() + Nr7*node[6].y() + Nr8*node[7].y());
            double LB(Ns1*node[0].x() + Ns2*node[1].x() + Ns3*node[2].x() + Ns4*node[3].x() + Ns5*node[4].x() + Ns6*node[5].x() + Ns7*node[6].x() + Ns8*node[7].x());
            double RB(Ns1*node[0].y() + Ns2*node[1].y() + Ns3*node[2].y() + Ns4*node[3].y() + Ns5*node[4].y() + Ns6*node[5].y() + Ns7*node[6].y() + Ns8*node[7].y());
            J = LT*RB - LB*RT;
            //Strain Matrix B
            double Nx1((RB*Nr1-RT*Ns1)/J);   double Ny1((-LB*Nr1+LT*Ns1)/J);
            double Nx2((RB*Nr2-RT*Ns2)/J);   double Ny2((-LB*Nr2+LT*Ns2)/J);
            double Nx3((RB*Nr3-RT*Ns3)/J);   double Ny3((-LB*Nr3+LT*Ns3)/J);
            double Nx4((RB*Nr4-RT*Ns4)/J);   double Ny4((-LB*Nr4+LT*Ns4)/J);
            double Nx5((RB*Nr5-RT*Ns5)/J);   double Ny5((-LB*Nr5+LT*Ns5)/J);
            double Nx6((RB*Nr6-RT*Ns6)/J);   double Ny6((-LB*Nr6+LT*Ns6)/J);
            double Nx7((RB*Nr7-RT*Ns7)/J);   double Ny7((-LB*Nr7+LT*Ns7)/J);
            double Nx8((RB*Nr8-RT*Ns8)/J);   double Ny8((-LB*Nr8+LT*Ns8)/J);
            B << Nx1, 0, Nx2, 0, Nx3, 0, Nx4, 0, Nx5, 0, Nx6, 0, Nx7, 0, Nx8, 0,
                 0, Ny1, 0, Ny2, 0, Ny3, 0, Ny4, 0, Ny5, 0, Ny6, 0, Ny7, 0, Ny8,
                 Ny1, Nx1, Ny2, Nx2, Ny3, Nx3, Ny4, Nx4, Ny5, Nx5, Ny6, Nx6, Ny7, Nx7, Ny8, Nx8;
            //Calculate K = SUM(H*B'*D*B*|J|)
            m_matKe = m_matKe + Hi[r]*Hi[s]*J*B.transpose()*D*B;
        }
}

