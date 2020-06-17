#ifndef CURVES_H
#define CURVES_H

#include <QObject>

class Curves : public QObject
{
    Q_OBJECT

public:
    explicit Curves(QObject *parent = nullptr);

    void initArrays();
    void build(double n, double tau, double alpha, double beta,
                         double epsilon, double lyambda, double fi);

    double **m_xnPlus;
    double **m_xnMinus;
    double **m_ynPlus;
    double **m_ynMinus;
    int m_count;

private:

    double func1(double xn, double yn, double alpha, double beta, double epsilon);
    double func2(double xn, double lyambda, double fi);
};

#endif // CURVES_H
