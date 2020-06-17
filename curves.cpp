#include "curves.h"

const int NMAX = 10000;
const int M = 500;

Curves::Curves(QObject *parent) : QObject(parent)
{
    clearCount();
    initArrays();
}

void Curves::initArrays() {
    m_xnPlus = new double* [M];
    m_xnMinus = new double* [M];
    m_ynPlus = new double* [M];
    m_ynMinus = new double* [M];
    for (int i = 0; i < M; i++) {
        m_xnPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        m_xnMinus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        m_ynPlus[i] = new double [NMAX];
    }
    for (int i = 0; i < M; i++) {
        m_ynMinus[i] = new double [NMAX];
    }
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

double Curves::func1(double xn, double yn, double alpha, double beta, double epsilon)
{
    return alpha * xn + beta * yn + epsilon;
}

double Curves::func2(double xn, double lyambda, double fi)
{
    return lyambda * xn + fi;
}
