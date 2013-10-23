#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QPointF>

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

private:
    Ui::MainWindow *ui;
    double **xnPlus, **xnMinus, **ynPlus, **ynMinus;
    double x0, y0;
    int countTraj;
    QwtPlotCurve *plusCurve, *minusCurve;
    QwtPlotPicker *picker;

private:
    void initArrays();
    void initTauComboBox();
    void initQwtPlot();
    void initQwtPlotPicker();
    void initCurves();
    void displayTrajectory(int idTraj);
    double func1(double xn, double yn);
    double func2(double xn);
    void buildTrajectory(int idTraj);
};

#endif // MAINWINDOW_H
