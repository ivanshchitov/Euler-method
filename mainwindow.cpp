#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initQwtPlot();
    initQwtPlotPicker();
    initTauComboBox();
    initImageODESystem();
    setWindowTitle("Решение системы ОДУ методом Эйлера.");
    connect(picker, SIGNAL(selected(const QPointF&)),
            this, SLOT(fixClickedPoint(const QPointF&)));
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

void MainWindow::initTauComboBox() {
    QStringList tauList;
    tauList << "1" << "0.1" << "0.01" << "0.001" << "0.0001";
    ui->tauComboBox->addItems(tauList);
}

void MainWindow::initQwtPlot() {
    ui->qwtPlot->setTitle("Графики траекторий");
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,
                              ui->aDoubleSpinBox->value(),
                              ui->bDoubleSpinBox->value());
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,
                              ui->cDoubleSpinBox->value(),
                              ui->dDoubleSpinBox->value());
}

void MainWindow::initQwtPlotPicker() {
    picker = new QwtPlotPicker(ui->qwtPlot->canvas());
    picker->setTrackerMode(QwtPicker::AlwaysOn);
    picker->setRubberBandPen(QColor(Qt::red));
    picker->setRubberBand(QwtPicker::NoRubberBand);
    picker->setStateMachine(new QwtPickerClickPointMachine());
    picker->setMousePattern(QwtPicker::MouseSelect1, Qt::LeftButton);
}

void MainWindow::initQwtPlotCurves() {
    plusCurve = createQwtPlotCurve(Qt::red);
    minusCurve = createQwtPlotCurve(Qt::blue);
}

QwtPlotCurve *MainWindow::createQwtPlotCurve(Qt::GlobalColor color)
{
    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setPen(QPen(QColor(color)));
    curve->attach(ui->qwtPlot);
    return curve;
}

void MainWindow::initImageODESystem() {
    QImage *image = new QImage;
    image->load("://formula.png");
    ui->imgLabel->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::fixClickedPoint(const QPointF& point) {
    initQwtPlotCurves();
    curves.setupStartPoints(point.x(), point.y());
    curves.build(ui->nDoubleSpinBox->value(), ui->tauComboBox->currentText().toDouble(),
                           ui->alphaDoubleSpinBox->value(), ui->betaDoubleSpinBox->value(),
                           ui->epsilonDoubleSpinBox->value(), ui->lyambdaDoubleSpinBox->value(),
                           ui->fiDoubleSpinBox->value());
    displayCurve(curves.count());
    curves.increaseCount();
    if (curves.count() > 0) {
        setEnabledSpinBoxes(false);
    }
}

void MainWindow::displayCurve(int curveId) {
    plusCurve->setSamples(curves.xnPlus()[curveId], curves.ynPlus()[curveId],
                          ui->nDoubleSpinBox->value() + 1);
    minusCurve->setSamples(curves.xnMinus()[curveId], curves.ynMinus()[curveId],
                           ui->nDoubleSpinBox->value() + 1);
    ui->qwtPlot->replot();
}

void MainWindow::on_clearButton_clicked() {
    ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotCurve);
    ui->qwtPlot->replot();
    curves.clearCount();
    setEnabledSpinBoxes(true);
}

void MainWindow::on_helpButton_clicked() {
    QMessageBox::about(this, "Справка", "Это приложение позволяет решать систему ОДУ методом Эйлера.\n"
                             "Оно рисует траектории численных решений в зависимости от того, какую Вы выбирете "
                             "начальную точку, параметры функций и размеры рабочей области.\n"
                             "© ЯрГУ им. П. Г. Демидова, факультет ИВТ, группа ИВТ-41СО, Щитов Иван");
}

void MainWindow::setEnabledSpinBoxes(bool isEnabled) {
    ui->alphaDoubleSpinBox->setEnabled(isEnabled);
    ui->betaDoubleSpinBox->setEnabled(isEnabled);
    ui->epsilonDoubleSpinBox->setEnabled(isEnabled);
    ui->lyambdaDoubleSpinBox->setEnabled(isEnabled);
    ui->fiDoubleSpinBox->setEnabled(isEnabled);
    ui->nDoubleSpinBox->setEnabled(isEnabled);
    ui->tauComboBox->setEnabled(isEnabled);
}
