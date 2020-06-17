#include "curves.h"

const int NMAX = 10000;
const int M = 500;

Curves::Curves(QObject *parent) : QObject(parent)
{
    countTraj = 0;
    initArrays();
}

void Curves::initArrays() {
    xnPlus = new double* [M];
    xnMinus = new double* [M];
    ynPlus = new double* [M];
    ynMinus = new double* [M];
    for (int i = 0; i < M; i++) {
        xnPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        xnMinus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        ynPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        ynMinus[i] = new double [NMAX];
    }
}

void Curves::buildTrajectory(double n, double tau, double alpha, double beta,
                             double epsilon, double lyambda, double fi)
{
    for (int i = 1; i <= n; i++) {
        xnPlus[countTraj][i] = xnPlus[countTraj][i -1]
                + tau * func1(xnPlus[countTraj][i -1], ynPlus[countTraj][i - 1], alpha, beta, epsilon);
        xnMinus[countTraj][i] = xnMinus[countTraj][i -1]
                - tau * func1(xnMinus[countTraj][i -1], ynMinus[countTraj][i - 1], alpha, beta, epsilon);
        ynPlus[countTraj][i] = ynPlus[countTraj][i -1] + tau * func2(xnPlus[countTraj][i -1], lyambda, fi);
        ynMinus[countTraj][i] = ynMinus[countTraj][i -1] - tau * func2(xnMinus[countTraj][i -1], lyambda, fi);
    }
}

double Curves::func1(double xn, double yn, double alpha, double beta, double epsilon)
{
    return alpha * xn + beta * yn + epsilon;
}

double Curves::func2(double xn, double lyambda, double fi)
{
    return lyambda * xn + fi;
}
