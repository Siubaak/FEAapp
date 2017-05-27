#ifndef CINPUT_H
#define CINPUT_H
#include "cinstance.h"

class CInput
{
public:
    CInput() {}
    CInput(QString order);
    QVector<CNode> inode() { return node; }
    QVector<CMaterial> imaterial() { return material; }
    QVector<Q8> ielement() { return element; }
    QVector<CLoad> iload() { return load; }
    QVector<CConstraint> iconstraint() { return constraint; }
private:
    QVector<CNode> node;
    QVector<CMaterial> material;
    QVector<Q8> element;
    QVector<CLoad> load;
    QVector<CConstraint> constraint;
};

#endif // CINPUT_H
