#include "curves.h"

const int NMAX = 10000;
const int M = 500;

Curves::Curves(QObject *parent) : QObject(parent)
{
    clearCount();
    initArrays();
}

void Curves::initArrays() {
    m_xnPlus = createPointsArray();
    m_xnMinus = createPointsArray();
    m_ynPlus = createPointsArray();
    m_ynMinus = createPointsArray();
}

void Curves::build(double n, double tau, double alpha, double beta,
                             double epsilon, double lyambda, double fi)
{
    for (int i = 1; i <= n; i++) {
        m_xnPlus[m_count][i] = m_xnPlus[m_count][i -1]
                + tau * func1(m_xnPlus[m_count][i -1], m_ynPlus[m_count][i - 1], alpha, beta, epsilon);
        m_xnMinus[m_count][i] = m_xnMinus[m_count][i -1]
                - tau * func1(m_xnMinus[m_count][i -1], m_ynMinus[m_count][i - 1], alpha, beta, epsilon);
        m_ynPlus[m_count][i] = m_ynPlus[m_count][i -1] + tau * func2(m_xnPlus[m_count][i -1], lyambda, fi);
        m_ynMinus[m_count][i] = m_ynMinus[m_count][i -1] - tau * func2(m_xnMinus[m_count][i -1], lyambda, fi);
    }
}

void Curves::setupStartPoints(double x, double y)
{
    m_xnPlus[m_count][0] = x;
    m_xnMinus[m_count][0] = x;
    m_ynPlus[m_count][0] = y;
    m_ynMinus[m_count][0] = y;
}

double **Curves::xnPlus()
{
    return m_xnPlus;
}

double **Curves::xnMinus()
{
    return m_xnMinus;
}

double **Curves::ynPlus()
{
    return m_ynPlus;
}

double **Curves::ynMinus()
{
    return m_ynMinus;
}

int Curves::count() const
{
    return m_count;
}

void Curves::increaseCount()
{
    m_count++;
}

void Curves::clearCount()
{
    m_count = 0;
}

double **Curves::createPointsArray()
{
    double **points = new double* [M];
    for (int i = 0; i < M; i++) {
        points[i] = new double [NMAX];
    }
    return points;
}

double Curves::func1(double xn, double yn, double alpha, double beta, double epsilon)
{
    return alpha * xn + beta * yn + epsilon;
}

double Curves::func2(double xn, double lyambda, double fi)
{
    return lyambda * xn + fi;
}
