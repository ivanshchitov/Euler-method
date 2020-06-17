#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QPointF>

#include "curves.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_enableSizeButton_clicked();
    void fixClickedPoint(const QPointF& point);
    void on_clearButton_clicked();
    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;
    QwtPlotCurve *plusCurve, *minusCurve;
    QwtPlotPicker *picker;

    Curves curves;

private:
    void initTauComboBox();
    void initQwtPlot();
    void initQwtPlotPicker();
    void initQwtPlotCurves();
    void initImageODESystem();
    void setEnabledSpinBoxes(bool isEnabled);
    void displayCurve(int curveId);
};

#endif // MAINWINDOW_H
