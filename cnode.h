#ifndef CNODE_H
#define CNODE_H


class CNode
{
public:
    //Constructed Function
    CNode(int n = 0, double x = 0, double y = 0) :m_iN(n), m_dX(x), m_dY(y) {}
    //Member Function
    double x() { return m_dX; }
    double y() { return m_dY; }
    int n() { return m_iN; }
    void Set(const int &x, const int &y) { m_dX = x, m_dY = y; }
private:
    int m_iN;       //Node number
    double m_dX;    //Coordinate x
    double m_dY;    //Coordinate y
};

#endif // CNODE_H
