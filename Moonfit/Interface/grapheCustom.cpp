#include "grapheCustom.h"
//#include "ui_grapheCustom.h"

#include <QAction>
#include <QMenu>
#include <QMap>     // for the gradients of colors
//#define PLOT PLOT
#define PLOT this->bigPlot

#define MAXCURVES 100


void grapheCustom::setColorScale(int ID){
    //std::cerr << "SET COLOR SCALE " << ID << std::endl;
    currentColorScale = ID;
}

QColor grapheCustom::baseList(int i){
    switch(currentColorScale){
    case MULTICOL:{
        switch(i){
        // see https://betterfigures.org/2015/06/23/picking-a-colour-scale-for-scientific-graphics/
    case 0: {return QColor(0, 204, 153);} // blue green 0,158,115) - 188-115
    case 1: {return QColor(255,77,77);} // vermillon 213,94,0
    case 2: {return QColor(250,159,0);} // orange 230,159,0
    case 3: {return QColor(0,114,178);} // blue
    case 4: {return QColor(255, 51, 204);} // pink (204,121,167)
    case 5: {return QColor(51,51,255);} // sky blue 86,180,233)
    case 6: {return QColor(153, 255, 102);} // green
    case 7: {return QColor(204, 0, 0);} // darkred
    case 8: {return QColor(153,0,204);}
    case 9: {return QColor(Qt::magenta);}
    case 10: {return QColor(Qt::darkBlue);}
    case 11: {return QColor(Qt::red);}
    case 12: {return QColor(Qt::lightGray);}
    case 13: {return QColor(Qt::yellow);}
    case 14: {return QColor(Qt::darkCyan);}
    case 15: {return QColor(Qt::blue);}
    case 16: {return QColor(Qt::darkGray);}
    case 17: {return QColor(Qt::lightGray);}
    case 18: {return QColor(Qt::yellow);}
    case 19: {return QColor(Qt::darkCyan);}
    case 20: {return QColor(Qt::darkRed);}
    default: {return QColor(Qt::darkRed);}
        }

        /* old palette switch(i){
        case 0: {return QColor(Qt::darkGreen);}
        case 1: {return QColor(Qt::red);}
        case 2: {return QColor(Qt::cyan);}
        case 3: {return QColor(Qt::darkMagenta);}
        case 4: {return QColor(Qt::darkBlue);}
        case 5: {return QColor(Qt::gray);}
        case 6: {return QColor(Qt::green);}
        case 7: {return QColor(Qt::darkRed);}
        case 8: {return QColor(Qt::darkYellow);}
        case 9: {return QColor(Qt::magenta);}
        case 10: {return QColor(Qt::blue);}
        case 11: {return QColor(Qt::darkGray);}
        case 12: {return QColor(Qt::lightGray);}
        case 13: {return QColor(Qt::yellow);}
        case 14: {return QColor(Qt::darkCyan);}
            // have to find better colors
        case 15: {return QColor(Qt::blue);}
        case 16: {return QColor(Qt::darkGray);}
        case 17: {return QColor(Qt::lightGray);}
        case 18: {return QColor(Qt::yellow);}
        case 19: {return QColor(Qt::darkCyan);}
        case 20: {return QColor(Qt::darkRed);}
        default: {return QColor(Qt::darkRed);}*/
        break;}



#define mytrick 12.0
    case GREEN_BLUE_RED :{
        static QCPColorGradient* myGrad = new QCPColorGradient();
        static bool gradInit = false;
        if(!gradInit){
            myGrad->setColorInterpolation(QCPColorGradient::ciRGB);
            myGrad->setLevelCount(250);
            QMap<double, QColor> colStops;
            colStops.insert(0.0, QColor(Qt::darkBlue));
            colStops.insert(3.0/mytrick, QColor(Qt::cyan));
            //colStops.insert(0.0, QColor(Qt::yellow));
            colStops.insert(5.9/mytrick, QColor(Qt::green));
            //colStops.insert(6.0/mytrick, QColor(Qt::black));
            colStops.insert(6.1/mytrick, QColor(Qt::green));
            colStops.insert(7.5/mytrick, QColor(Qt::yellow));
            colStops.insert(1.0, QColor(Qt::red));

            /*colStops.insert(0.0, QColor(Qt::green));
            colStops.insert(4.0/12.0, QColor(Qt::darkGreen));
            //colStops.insert(0.0, QColor(Qt::yellow));
            colStops.insert(6.9/12.0, QColor(Qt::blue));
            colStops.insert(7.0/12.0, QColor(Qt::gray));
            colStops.insert(7.1/12.0, QColor(Qt::blue));
            colStops.insert(1.0, QColor(Qt::red));*/


            myGrad->setColorStops(colStops);
            gradInit = true;
        }

        switch(i){
        case 0: {return QColor(myGrad->color(0.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 1: {return QColor(myGrad->color(1.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 2: {return QColor(myGrad->color(2.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 3: {return QColor(myGrad->color(3.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 4: {return QColor(myGrad->color(4.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 5: {return QColor(myGrad->color(5.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 6: {return QColor(myGrad->color(6.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 7: {return QColor(myGrad->color(7.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 8: {return QColor(myGrad->color(8.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 9: {return QColor(myGrad->color(9.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 10: {return QColor(myGrad->color(10.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 11: {return QColor(myGrad->color(11.0 / 12.0, QCPRange(0.0, 1.0)));}
        case 12: {return QColor(myGrad->color(12.0 / 12.0, QCPRange(0.0, 1.0)));}
        default: {return QColor(Qt::gray);}
        }
        break;
    }
    }
    return QColor(Qt::black);
}


grapheCustom::grapheCustom(QWidget *parent) :
  QWidget(parent), currentColorScale(MULTICOL)
  //ui(new Ui::grapheCustom)
{
  srand(QDateTime::currentDateTime().toTime_t());
  //ui->setupUi(this);

  PLOT = new QCustomPlot(parent);
  PLOT->resize(parent->size());
  
  PLOT->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
  //PLOT->xAxis->setRange(-8, 8);
  //PLOT->yAxis->setRange(-5, 5);
  PLOT->axisRect()->setupFullAxesBox();
  
  PLOT->plotLayout()->insertRow(0);
  currentTitle = new  QCPTextElement(PLOT, "Example Curve");
  PLOT->plotLayout()->addElement(0, 0, currentTitle);
  
  PLOT->xAxis->setLabel("time");
  PLOT->yAxis->setLabel("-");
  //PLOT->xAxis->setLabelFont(QFont("Helvetica",9));
  //PLOT->yAxis->setLabelFont(QFont("Helvetica",9));
  PLOT->legend->setFont(QFont("Helvetica",6));
  PLOT->legend->setIconSize(QSize(15,10));
  PLOT->legend->setVisible(true);
  //QFont legendFont = QFont("Helvetica",8); //font();
  //legendFont.setPointSize(8);
  //PLOT->legend->setFont(legendFont);
  //PLOT->legend->setSelectedFont(legendFont);
  PLOT->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
  
  // connect slot that ties some axis selections together (especially opposite axes):
  connect(PLOT, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
  // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
  connect(PLOT, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
  connect(PLOT, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
  
  // make bottom and left axes transfer their ranges to top and right axes:
  connect(PLOT->xAxis, SIGNAL(rangeChanged(QCPRange)), PLOT->xAxis2, SLOT(setRange(QCPRange)));
  connect(PLOT->yAxis, SIGNAL(rangeChanged(QCPRange)), PLOT->yAxis2, SLOT(setRange(QCPRange)));
  
  // connect some interaction slots:
  //// does not exist anymore in QCP 2.0 connect(PLOT, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
  connect(PLOT, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
  connect(PLOT, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

  // connect slot that shows a message in the status bar when a graph is clicked:
  //// does not exist anymor QCP 2.0 connect(PLOT, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
  
  // setup policy and connect slot for context menu popup:
  PLOT->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(PLOT, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));


  PLOT->addGraph();
  setNbCurves(1);
}

void grapheCustom::clear(){
    setNbCurves(nbCurves);
}

void grapheCustom::setTitle(QString _titre){
    //PLOT->plotLayout()->addElement(0, 0, new QCPPlotTitle(PLOT, _titre.toStdString().c_str()));
    //QCPPlotTitle* qcp = PLOT->plotLayout()->element(0,0)->children()[0];
    //qcp->setText(_titre);
    currentTitle->setText(_titre);

}

void grapheCustom::logarithmic(bool newState){

    //std::cout <<" Put to log ?" << ((newState) ? "Yes" : "No") << std::endl;

    if(newState) {
        PLOT->yAxis->setScaleType(QCPAxis::stLogarithmic);
        //PLOT->yAxis->setLogBase(10); // setScaleLogBAse replaced by setLogBase in QCP2
        PLOT->yAxis->setRange(100,1000);
    }
    else {
        PLOT->yAxis->setScaleType(QCPAxis::stLinear);
    }
}


void grapheCustom::setNbCurves(int _nbCurves){
    if((_nbCurves < 1) || (_nbCurves > MAXCURVES)) {std::cerr << "ERR: Graphe::setNbCurves(" << _nbCurves << ", not an authorized value\n"; return;}

    nbCurves = PLOT->graphCount();
    /*for(int i = 0; i < nbCurves ; ++i){
        PLOT->removeGraph(PLOT->graph(i));
    }
    PLOT->replot();*/

    for(int i = 0; i < (int) Data.size(); ++i){
        if(Data[i]) delete Data[i];
    }
    for(int i = 0; i < (int) xpoints.size(); ++i){
        if(xpoints[i]) delete xpoints[i];
    }
    for(int i = 0; i < (int) Errbars.size(); ++i){
        if(Errbars[i]) Errbars[i];
    }
    nbCurves = _nbCurves;
    Data.clear(); xpoints.clear(); Errbars.clear();
    PLOT->clearGraphs();
    for(int i = 0; i < nbCurves; ++i){
        PLOT->addGraph();
        QCPErrorBars *errorBars = new QCPErrorBars(PLOT->xAxis, PLOT->yAxis);
        errorBars->removeFromLegend();
        errorBars->setAntialiased(false);
        errorBars->setDataPlottable(PLOT->graph(i));
        errorBars->setPen(QPen(QColor(180,180,180)));
        Errbars.push_back(errorBars);
        //customPlot->graph(i)->setName("Measurement");
    }






    Data.resize(nbCurves);
    xpoints.resize(nbCurves);

    static int cptNew = 0;
    cptNew++;
    if(cptNew > 10000) std::cerr << "WRN: Would need to free memory inside evolution::newValue" << std::endl;

    for(int i = 0; i < nbCurves; ++i){
        Data[i] = new QVector<double>();
        xpoints[i] = new QVector<double>();
        PLOT->graph(i)->setName(QString("New graph %1").arg(PLOT->graphCount()-1));
        ////////PLOT->graph(i)->setData(*(xpoints[i]), *(Data[i]));
        //PLOT->graph(i)->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
        //if (rand()%100 > 50)
        //  PLOT->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
        //QPen graphPen;
        //graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
        //graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
        //PLOT->graph()->setPen(graphPen);
    }

    //logarithmic(true);
    PLOT->replot();
    //BigPlot->replot();

}

void grapheCustom::Plot(int IDCurve, vector<double> y_to_plot, vector<double> x_to_plot, QString _titre, QColor _color, Qt::PenStyle ps, QCPScatterStyle scsty){
    Plot(IDCurve, y_to_plot, vector<double>(), x_to_plot, _titre, _color, ps, scsty);
}

void grapheCustom::Plot(int IDCurve, vector<double> y_to_plot, vector<double> yerr_to_plot, vector<double> x_to_plot, QString _titre, QColor _color, Qt::PenStyle ps, QCPScatterStyle scsty){
    if((IDCurve < 0) || (IDCurve >= nbCurves)) {std::cerr << "ERR Graphe::Plot(IDCurve=" << IDCurve <<",...), curve ID not valid (only " << nbCurves << " curves defined. Indices start at 0.\n"; return;}
    int size = y_to_plot.size();
    if((int) x_to_plot.size() < size) {std::cerr << "ERR: Graphe1::Plot , error, the vector of x points is smaller than the vector of y points\n "; return;}
    x_to_plot.resize(size);

    // std::cerr << "Size of data plotted : " << size << std::endl;
    /*for(int i = 0; i < size; ++i){
        std::cerr << i << "\t" << x_to_plot[i] << "\t" << y_to_plot[i] << std::endl;
    }*/
    int i = IDCurve;
    Data[i]->clear();
    delete Data[i];
    Data[i] = new QVector<double>(QVector<double>::fromStdVector(y_to_plot));
    xpoints[i]->clear();
    delete xpoints[i];
    xpoints[i] = new QVector<double>(QVector<double>::fromStdVector(x_to_plot));

    if(i >= PLOT->graphCount()) return;
    //PLOT->removeGraph(i);
    if(size == 0) PLOT->graph(i)->removeFromLegend();
    else PLOT->graph(i)->addToLegend();


//std::cout << "Hehe" << std::endl;
//std::cout << "Plot curve " << i << " out of " << PLOT->graphCount() << " total curves" << std::endl;
    PLOT->graph(i)->setName(_titre);
    PLOT->graph(i)->setData(QVector<double>::fromStdVector(x_to_plot), QVector<double>::fromStdVector(y_to_plot));
//std::cout << "Hehe2" << std::endl;
    if(_titre.size() == 0){
        QCPPlottableLegendItem* lgd = PLOT->legend->itemWithPlottable(PLOT->graph(i));
        if(lgd) PLOT->legend->removeItem(lgd);
        //int nbLg = PLOT->legend->itemCount();
        //PLOT->legend->removeItem(nbLg-1);
    }
    //PLOT->graph(i)->setLineStyle(QCPGraph::LineStyle)  ((QCPGraph::LineStyle)(rand()%5+1));
    //if (rand()%100 > 50)
    //  PLOT->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
    QPen graphPen;
    graphPen.setWidth(2);
    graphPen.setStyle(ps);
    graphPen.setColor(_color);
    //graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    PLOT->graph(i)->setPen(graphPen);

    PLOT->graph(i)->setScatterStyle(scsty);

    PLOT->rescaleAxes(true);

    //////// Philippe : this is manual cheating !!!! /////////////////
    double newUpper = max(0.01, PLOT->yAxis->range().upper);
    double newLower = 0;
    if(PLOT->yAxis->scaleType() == QCPAxis::stLogarithmic){
        newLower = min(10000., PLOT->yAxis->range().lower);
    } else {
        newLower = min(0., PLOT->yAxis->range().lower);
    }
    PLOT->yAxis->setRange(newLower, newUpper);

    if((int) Errbars.size() <= i) std::cerr << "ERR: not as many ERRbars as curves defined inside grapheCustom" << std::endl;
    if(yerr_to_plot.size() > 0){
        QVector<double> dataErr = QVector<double>::fromStdVector(yerr_to_plot);
        //std::cerr << "Attempt to plot " << yerr_to_plot.size() << " error bars for curve " << IDCurve << std::endl;
        Errbars[i]->setPen(graphPen);//QPen(QColor(180,180,180)));
        Errbars[i]->setData(dataErr);
        Errbars[i]->setVisible(true);

    } else {
        QVector<double> emptyErr = QVector<double>(x_to_plot.size(),0.);
        Errbars[i]->setData(emptyErr);
        Errbars[i]->setVisible(false);
    }

    //if(PLOT->yAxis->scaleType() == QCPAxis::stLogarithmic)

    //PLOT->legend->setVisible(false);
    /*
     *   enum LineStyle { lsNone        ///< data points are not connected with any lines (e.g. data only represented
                             ///< with symbols according to the scatter style, see \ref setScatterStyle)
               ,lsLine       ///< data points are connected by a straight line
               ,lsStepLeft   ///< line is drawn as steps where the step height is the value of the left data point
               ,lsStepRight  ///< line is drawn as steps where the step height is the value of the right data point
               ,lsStepCenter ///< line is drawn as steps where the step is in between two data points
               ,lsImpulse    ///< each data point is represented by a line parallel to the value axis, which reaches from the data point to the zero-value-line
             };
Q_ENUMS(LineStyle)
//    Defines what kind of error bars are drawn for each data point

enum ErrorType { etNone   ///< No error bars are shown
               ,etKey   ///< Error bars for the key dimension of the data point are shown
               ,etValue ///< Error bars for the value dimension of the data point are shown
               ,etBoth  ///< Error bars for both key and value dimensions of the data point are shown
             };
Q_ENUMS(ErrorType)

*/

        //curveData[i]->setPen(QPen(Qt::DashDotLine));

        PLOT->replot();

}

void grapheCustom::exportToPng(QString _file){
    //double newUpper = max(10.0, PLOT->yAxis->range().upper);
    //PLOT->yAxis->setRange(0.0, newUpper);
    PLOT->savePng(_file);
}


void grapheCustom::exportToPDF(QString _file, int width, int height){
    //double newUpper = max(10.0, PLOT->yAxis->range().upper);
    //PLOT->yAxis->setRange(0.0, newUpper);
    //PLOT->savePng(_file);
   if((width < 0) || (height < 0)) PLOT->savePdf(_file);
   else PLOT->savePdf(_file, width, height);
   //seems that PDFs generated without width and height can not be used inside latex correctly
     //, 300, 183); //, width=8, int height=4); //, QCP::ExportPen exportPen=QCP::epAllowCosmetic, const QString &pdfCreator=QString(), const QString &pdfTitle=QString())

}

void grapheCustom::Example(){
    double p1[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5};
    double p2[] = {0, 0.5, 0.8, 0.3, 0.2, 0.1};
    double p3[] = {0, 0.4, 0.7, 0.4, 0.5, 0.2};

    vector<double> xs = vector<double>(p1, &p1[5]);
    vector<double> ys = vector<double>(p2, &p2[5]);
    vector<double> zs = vector<double>(p3, &p3[5]);
    setNbCurves(2);
    Plot(0, ys, xs, QString("Example of plot"), QColor(Qt::darkBlue));
    Plot(1, zs, xs, QString("With two curves"), QColor(Qt::darkBlue));
}



grapheCustom::~grapheCustom()
{
  //delete ui;
}

void grapheCustom::titleDoubleClick(QMouseEvent* event, QCPTextElement *title)
{
    std::cerr << "title doubleclicked" << std::endl;

  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    PLOT->replot();
  }
}

void grapheCustom::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    std::cerr << "axislabel doubleclicked" << std::endl;

  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      PLOT->replot();
    }
  }
}

void grapheCustom::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    std::cerr << "selection double click" << std::endl;

  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      PLOT->replot();
    }
  }
}

void grapheCustom::selectionChanged()
{
    std::cerr << "selection Changed" << std::endl;

  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.
   
   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.
   
   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */
  
  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (PLOT->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || PLOT->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      PLOT->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || PLOT->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    PLOT->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    PLOT->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (PLOT->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || PLOT->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      PLOT->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || PLOT->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    PLOT->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    PLOT->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  
  //std::cerr << "Middle" << std::endl;
  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<PLOT->graphCount(); ++i)
  {
    QCPGraph *graph = PLOT->graph(i);
    QCPPlottableLegendItem *item = PLOT->legend->itemWithPlottable(graph);
    if (item && (item->selected() || graph->selected()))
    {
      item->setSelected(true);
      //graph->setSelected(true); // not true in QCP2.0??
    }
  }
  std::cerr << "end selection changed" << std::endl;
}

void grapheCustom::mousePress()
{
    //std::cerr << "Mouse Press" << std::endl;

  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged
  
  if (PLOT->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    PLOT->axisRect()->setRangeDrag(PLOT->xAxis->orientation());
  else if (PLOT->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    PLOT->axisRect()->setRangeDrag(PLOT->yAxis->orientation());
  else
    PLOT->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void grapheCustom::mouseWheel()
{
    //std::cerr << "MouseWheel" << std::endl;

  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed
  
  if (PLOT->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    PLOT->axisRect()->setRangeZoom(PLOT->xAxis->orientation());
  else if (PLOT->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    PLOT->axisRect()->setRangeZoom(PLOT->yAxis->orientation());
  else
    PLOT->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void grapheCustom::addRandomGraph()
{
    std::cerr << "add random graph" << std::endl;

  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*5;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }
  
  PLOT->addGraph();
  PLOT->graph()->setName(QString("New graph %1").arg(PLOT->graphCount()-1));
  PLOT->graph()->setData(x, y);
  PLOT->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    PLOT->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  PLOT->graph()->setPen(graphPen);
  PLOT->replot();
}

void grapheCustom::removeSelectedGraph()
{
  if (PLOT->selectedGraphs().size() > 0)
  {
      std::cerr << "remove One Graph" << std::endl;

    PLOT->removeGraph(PLOT->selectedGraphs().first());
    PLOT->replot();
  }
}

void grapheCustom::removeAllGraphs()
{
    std::cerr << "removeAll" << std::endl;

  PLOT->clearGraphs();
  PLOT->replot();

}

void grapheCustom::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);

  static int cptNew = 0;
  cptNew++;
  if(cptNew > 10000) std::cerr << "WRN: Would need to free memory inside grapheCustom::contextmenurequest" << std::endl;


  menu->setAttribute(Qt::WA_DeleteOnClose);
  
  if (PLOT->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
    if (PLOT->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (PLOT->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }
  
  menu->popup(PLOT->mapToGlobal(pos));
}

void grapheCustom::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      PLOT->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      PLOT->replot();
    }
  }
  std::cerr << "moveLegend" << std::endl;

}

void grapheCustom::graphClicked(QCPAbstractPlottable *plottable)
{
    std::cerr << "GraphCLicked" << std::endl;
  //ui->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}




