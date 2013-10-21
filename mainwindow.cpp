#include "mainwindow.h"
#include "ui_mainwindow.h"


const int NMAX = 10000;
const int M = 500;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initQwtPlot();
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
