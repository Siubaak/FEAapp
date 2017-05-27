#include "cinput.h"

CInput::CInput(QString order)
{
    //turn the code into line form and mark beginings and ends
    QVector<QString> line;
    QVector<int> begin;
    QVector<int> end;
    int k(0);
    for (int i = 0; i != order.size(); ++i)
    {
        if (order.data()[i] == '\n')
        {
            line<<order.mid(k, i-k);
            k = i + 1;
        }
    }
    for (int i = 0; i != line.size(); ++i)
    {
        if (line[i].endsWith('=', Qt::CaseInsensitive))
            begin<<i;
        if (line[i] == "-")
            end<<i;
    }
    //Form node information
    for (int i = begin[0] + 1; i != end[0]; ++i)
    {
        int n = line[i].section(',', 0, 0).toInt();
        double x = line[i].section(',', 1, 1).toDouble();
        double y = line[i].section(',', 2, 2).toDouble();
        CNode enode(n, x, y);
        node<<enode;
    }
    //Form material information
    for (int i = begin[1] + 1; i != end[1]; ++i)
    {
        int n = line[i].section(',', 0, 0).toInt();
        double rho = line[i].section(',', 1, 1).toDouble();
        double E = line[i].section(',', 2, 2).toDouble();
        double v = line[i].section(',', 3, 3).toDouble();
        CMaterial emateral(n, rho, E, v);
        material<<emateral;
    }
    //Form element information
    for (int i = begin[2] + 1; i != end[2]; ++i)
    {
        int n = line[i].section(',', 0, 0).toInt();
        QVector<CNode> enodes;
        for (int j = 0; j != 8; ++j)
            enodes<<node[line[i].section(',', 1, 1).section(';', j, j).toInt() - 1];
        int m = line[i].section(',', 2, 2).toInt() - 1;
        Q8 eelement(n, enodes, material[m]);
        element<<eelement;
    }
    //Form load information
    for (int i = begin[3] + 1; i != end[3]; ++i)
    {
        int n = line[i].section(',', 0, 0).toInt();
        int no = line[i].section(',', 1, 1).toInt();
        double fx = line[i].section(',', 2, 2).toDouble();
        double fy = line[i].section(',', 3, 3).toDouble();
        CLoad eload(n, no, fx, fy);
        load<<eload;
    }
    //Form constraint information
    for (int i = begin[4] + 1; i != end[4]; ++i)
    {
        int n = line[i].section(',', 0, 0).toInt();
        int no = line[i].section(',', 1, 1).toInt();
        int cx = line[i].section(',', 2, 2).toInt();
        int cy = line[i].section(',', 3, 3).toInt();
        CConstraint econstraint(n, no, cx, cy);
        constraint<<econstraint;
    }
}

