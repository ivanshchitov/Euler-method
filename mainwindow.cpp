#include "mainwindow.h"
#include "ui_mainwindow.h"


const int NMAX = 10000;
const int M = 500;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countTraj = 0;
    initQwtPlot();
    initQwtPlotPicker();
    initTauComboBox();
    initArrays();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_enableSizeButton_clicked() {
    ui->qwtPlot->setAxisScale(
                QwtPlot::xBottom,
                std::min(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()),
                std::max(ui->aDoubleSpinBox->value(), ui->bDoubleSpinBox->value()));
    ui->qwtPlot->setAxisScale(
                QwtPlot::yLeft,
                std::min(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()),
                std::max(ui->cDoubleSpinBox->value(), ui->dDoubleSpinBox->value()));
    ui->qwtPlot->replot();
}

void MainWindow::initArrays() {
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

void MainWindow::initTauComboBox() {
    QStringList tauList;
    tauList << "1" << "0.1" << "0.01" << "0.001" << "0.0001";
    ui->tauComboBox->addItems(tauList);
}

void MainWindow::initQwtPlot() {
    ui->qwtPlot->setTitle("Графики траекторий");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, -5, 5);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, -5, 5);
}

void MainWindow::initQwtPlotPicker() {
    picker = new QwtPlotPicker(ui->qwtPlot->canvas());
    picker->setTrackerMode(QwtPicker::AlwaysOn);
    picker->setRubberBandPen(QColor(Qt::red));
    picker->setRubberBand(QwtPicker::NoRubberBand);
    picker->setMousePattern(QwtPicker::MouseSelect1, Qt::LeftButton);
}

double MainWindow::func1(double xn, double yn) {
    return ui->alphaDoubleSpinBox->value() * xn
            + ui->betaDoubleSpinBox->value() * yn
            + ui->epsilonDoubleSpinBox->value();
}

double MainWindow::func2(double xn) {
    return ui->lyambdaDoubleSpinBox->value() * xn
            + ui->fiDoubleSpinBox->value();
}

void MainWindow::buildTrajectory(int idTraj) {
    for (int i = 0; i < ui->nDoubleSpinBox->value(); i++) {
        xnPlus[idTraj][i] = xnPlus[idTraj][i -1]
                + ui->tauComboBox->currentText().toDouble()
                * func1(xnPlus[idTraj][i -1], ynPlus[idTraj][i - 1]);
        xnMinus[idTraj][i] = xnMinus[idTraj][i -1]
                - ui->tauComboBox->currentText().toDouble()
                * func1(xnMinus[idTraj][i -1], ynMinus[idTraj][i - 1]);
        ynPlus[idTraj][i] = ynPlus[idTraj][i -1]
                + ui->tauComboBox->currentText().toDouble()
                * func2(xnPlus[idTraj][i -1]);
        ynMinus[idTraj][i] = ynMinus[idTraj][i -1]
                - ui->tauComboBox->currentText().toDouble()
                * func2(xnMinus[idTraj][i -1]);
    }
}
