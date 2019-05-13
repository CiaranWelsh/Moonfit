#ifndef GRAPHECUSTOM_H
#define GRAPHECUSTOM_H

#include "common.h"


#ifdef QT4
#include <QtGui/QMainWindow>
#include <QtGui/QInputDialog>
#endif
#ifdef QT5
#include <QMainWindow>
#include <QInputDialog>
#endif


#include "Interface/QCustomPlot/qcustomplot.h"

#include <iostream>
#include <vector>
using namespace std;

enum {MULTICOL, GREEN_BLUE_RED};

namespace Ui {
class MainWindow;
}

class grapheCustom : public QWidget
{
  Q_OBJECT
  
public:
  explicit grapheCustom(QWidget *parent = 0);
  ~grapheCustom();

    QCustomPlot* bigPlot;
    vector< QVector<double>* > Data;
    vector< QVector<double>* > xpoints;
    vector< QCPErrorBars*> Errbars;
    //vector<QwtPlotCurve*> curveData; not needed anymore, can access by  customPlot->graph(3)->
    int nbCurves;
    QCPTextElement* currentTitle; // QCPPlotTitle replaced by  QCPTextElement in QCutomPlot2
    int currentColorScale;

    void setTitle(QString _titre);
    void setNbCurves(int _nbCurves);
    void Plot(int IDCurve, vector<double> y_to_plot, vector<double> x_to_plot, QString _titre, QColor _color = QColor(Qt::white), Qt::PenStyle ps = Qt::SolidLine, QCPScatterStyle scsty = QCPScatterStyle::ssNone );
    void Plot(int IDCurve, vector<double> y_to_plot, vector<double> yerr_to_plot, vector<double> x_to_plot, QString _titre, QColor _color = QColor(Qt::white), Qt::PenStyle ps = Qt::SolidLine, QCPScatterStyle scsty = QCPScatterStyle::ssNone );
    void Example();
    void clear();
    void setColorScale(int ID);
    void logarithmic(bool newState);
    QColor baseList(int i);
    void exportToPng(QString _file);
    void exportToPDF(QString _file, int width = -1, int height = -1);

private slots:
  void titleDoubleClick(QMouseEvent *event,  QCPTextElement *title);
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void addRandomGraph();
  void removeSelectedGraph();
  void removeAllGraphs();
  void contextMenuRequest(QPoint pos);
  void moveLegend();
  void graphClicked(QCPAbstractPlottable *plottable);
  
private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
