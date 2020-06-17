#ifndef CURVES_H
#define CURVES_H

#include <QObject>

class Curves : public QObject
{
    Q_OBJECT

public:
    explicit Curves(QObject *parent = nullptr);

    void initArrays();
    void buildTrajectory(double n, double tau, double alpha, double beta,
                         double epsilon, double lyambda, double fi);

    double **xnPlus, **xnMinus, **ynPlus, **ynMinus;
    int countTraj;

private:

    double func1(double xn, double yn, double alpha, double beta, double epsilon);
    double func2(double xn, double lyambda, double fi);
};

#endif // CURVES_H
