#ifndef CMATERIAL_H
#define CMATERIAL_H


class CMaterial
{
public:
    //Constructed Function
    CMaterial(int n = 1, double rho = 7900, double E = 210000, double v = 0.3) :m_iN(n), m_dRho(rho), m_dE(E), m_dv(v) {}
                                            //Default propertities is of steel
    //Member Function
    double Rho() { return m_dRho; }
    double E() { return m_dE; }
    double v() { return m_dv; }
    int n() { return m_iN; }
private:
    int m_iN;       //Material number
    double m_dRho;  //Density
    double m_dE;    //Elastic modulus
    double m_dv;    //Possion ratio
};

#endif // CMATERIAL_H
