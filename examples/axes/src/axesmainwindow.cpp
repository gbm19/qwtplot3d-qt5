#include <qsplitter.h>
#include <qlayout.h>
#include <qcombobox.h>
#include <qaction.h>
#include <qslider.h>
#include <qcheckbox.h>
#include <qmenubar.h>
#include <qdatetime.h>

#include "axes.h"
#include "axesmainwindow.h"
#include "../../../include/qwt3d_function.h"

using namespace std;
using namespace Qwt3D;

// Example function
class Rosenbrock : public Function
{
public:
    Rosenbrock(SurfacePlot &pw) : Function(pw) { }

    double operator()(double x, double y) { return log10((1 - x) * (1 - x) + 1 * (y - x * x) * (y - x * x)); }
};

// Main widget

AxesMainWindow::AxesMainWindow(QWidget *parent) : DummyBase(parent)
{
#if QT_VERSION < 0x040000
    setCaption("axes");
    QGridLayout *grid = new QGridLayout(frame, 0, 0);
#else
    setupUi(this);
    QGridLayout *grid = new QGridLayout(frame);
#endif

    plot = new SurfacePlot(frame);
    grid->addWidget(plot, 0, 0);

    plot->setZoom(0.8);
    plot->setRotation(30, 0, 15);

    plot->coordinates()->setGridLines(true, true);
    plot->setCoordinateStyle(BOX);
    // plot->setCoordinateStyle(NOCOORD);
    // plot->setPlotStyle(FILLED);

    rosenbrock = new Rosenbrock(*plot);

    rosenbrock->setMesh(31, 33);
    rosenbrock->setDomain(-1.73, 1.8, -1.9, 1.8);
    rosenbrock->setMinZ(-100);

    rosenbrock->create();

    for (unsigned i = 0; i != plot->coordinates()->axes.size(); ++i) {
        plot->coordinates()->axes[i].setMajors(5);
        plot->coordinates()->axes[i].setMinors(4);
        plot->coordinates()->axes[i].setLabelColor(RGBA(0, 0, 0.4));
    }

    // plot->setTitle("Rosenbrock");
    plot->setMeshLineWidth(1);
    plot->coordinates()->setGridLinesColor(RGBA(0, 0, 0.5));
    plot->coordinates()->setLineWidth(1);
    plot->coordinates()->setNumberColor(RGBA(0, 0.5, 0));
    plot->coordinates()->setNumberFont("Courier", 10);
    plot->setTitleFont("Courier", 11);
    plot->coordinates()->setLabelFont("Courier", 12, QFont::Bold);
    plot->coordinates()->axes[X1].setLabelString("X1");
    plot->coordinates()->axes[Y1].setLabelString("Y1");
    plot->coordinates()->axes[Z1].setLabelString("Z1");
    plot->coordinates()->axes[X2].setLabelString("X2");
    plot->coordinates()->axes[Y2].setLabelString("Y2");
    plot->coordinates()->axes[Z2].setLabelString("Z2");
    plot->coordinates()->axes[X3].setLabelString("X3");
    plot->coordinates()->axes[Y3].setLabelString("Y3");
    plot->coordinates()->axes[Z3].setLabelString("Z3");
    plot->coordinates()->axes[X4].setLabelString("X4");
    plot->coordinates()->axes[Y4].setLabelString("Y4");
    plot->coordinates()->axes[Z4].setLabelString("Z4");

    plot->coordinates()->setLineSmooth(true);
    smoothBox->setDown(true);

#if QT_VERSION < 0x040000
    Items->insertItem("&Standard", this, SLOT(standardItems()), ALT + Key_S);
    Items->insertItem("&Imaginary", this, SLOT(complexItems()), ALT + Key_I);
    Items->insertItem("&Letter", this, SLOT(letterItems()), ALT + Key_L);
    Items->insertItem("&Time", this, SLOT(timeItems()), ALT + Key_T);
    Items->insertItem("&Log", this, SLOT(customScale()), ALT + Key_C);
#else
    QMenu *Items = menuBar()->addMenu("Item");
    Items->addAction("&Standard", this, SLOT(standardItems()), QKeySequence("ALT+S"));
    Items->addAction("&Imaginary", this, SLOT(complexItems()), QKeySequence("ALT+I"));
    Items->addAction("&Letter", this, SLOT(letterItems()), QKeySequence("ALT+L"));
    Items->addAction("&Time", this, SLOT(timeItems()), QKeySequence("ALT+T"));
    Items->addAction("&Log", this, SLOT(customScale()), QKeySequence("ALT+C"));
#endif

    plot->makeCurrent();
    plot->updateData();
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif

    connect(smoothBox, SIGNAL(toggled(bool)), this, SLOT(setSmoothLines(bool)));
    connect(numbergapslider, SIGNAL(valueChanged(int)), this, SLOT(setNumberGap(int)));
    connect(labelgapslider, SIGNAL(valueChanged(int)), this, SLOT(setLabelGap(int)));
    connect(ticLengthSlider, SIGNAL(valueChanged(int)), this, SLOT(setTicLength(int)));
    connect(ticNumberSlider, SIGNAL(valueChanged(int)), this, SLOT(setTicNumber(int)));

    tics = plot->coordinates()->axes[X1].majors();

    // resetTics();

    customScale();

    plot->setPolygonOffset(10);
}

AxesMainWindow::~AxesMainWindow()
{
    delete rosenbrock;
}

void AxesMainWindow::setNumberGap(int gap)
{
    plot->coordinates()->adjustNumbers(gap);
    plot->makeCurrent();
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::setLabelGap(int gap)
{
    plot->coordinates()->adjustLabels(gap);
    plot->makeCurrent();
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::setSmoothLines(bool val)
{
    plot->coordinates()->setLineSmooth(val);
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::setTicLength(int val)
{
    double majl = (plot->coordinates()->second() - plot->coordinates()->first()).length() / 1000.;
    majl = majl * val;
    plot->coordinates()->setTicLength(majl, 0.6 * majl);
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::setTicNumber(int degree)
{
    plot->coordinates()->axes[X1].setMajors(tics + degree);
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::resetTics()
{
    ticNumberSlider->setEnabled(false);
    plot->setTitle("");
    plot->coordinates()->axes[X1].setMajors(5);
    plot->coordinates()->setAutoScale(true);
    plot->coordinates()->setStandardScale();
    plot->coordinates()->axes[Z2].setLabelString("Z4");
    plot->coordinates()->setGridLines(false, false, Qwt3D::BACK);
}

void AxesMainWindow::standardItems()
{
    resetTics();
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::letterItems()
{
    resetTics();
    ticNumberSlider->setEnabled(true);
    plot->coordinates()->axes[X1].setAutoScale(false);
    plot->coordinates()->setStandardScale();
    plot->coordinates()->axes[X1].setScale(new Letter);
    plot->coordinates()->axes[X2].setScale(new Letter);
    plot->coordinates()->axes[X3].setScale(new Letter);
    plot->coordinates()->axes[X4].setScale(new Letter);
    plot->coordinates()->axes[Y1].setScale(new Letter(false));
    plot->coordinates()->axes[Y2].setScale(new Letter(false));
    plot->coordinates()->axes[Y3].setScale(new Letter(false));
    plot->coordinates()->axes[Y4].setScale(new Letter(false));
    plot->setTitle("Use the tics slider for this example!");
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::complexItems()
{
    resetTics();
    plot->coordinates()->axes[Y1].setScale(new Imaginary);
    plot->coordinates()->axes[Y2].setScale(new Imaginary);
    plot->coordinates()->axes[Y3].setScale(new Imaginary);
    plot->coordinates()->axes[Y4].setScale(new Imaginary);
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::timeItems()
{
    resetTics();
    plot->coordinates()->axes[Z1].setScale(new TimeItems);
    plot->coordinates()->axes[Z2].setScale(new TimeItems);
    plot->coordinates()->axes[Z3].setScale(new TimeItems);
    plot->coordinates()->axes[Z4].setScale(new TimeItems);
#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}

void AxesMainWindow::customScale()
{
    resetTics();
    plot->coordinates()->axes[Z1].setScale(LOG10SCALE);
    plot->coordinates()->axes[Z3].setScale(LOG10SCALE);
    plot->coordinates()->axes[Z4].setScale(LOG10SCALE);
    plot->coordinates()->axes[Z2].setLabelString("log10(z)");
    //  plot->coordinates()->axes[Z4].setScale(new LogScale);
    //  plot->coordinates()->axes[Z1].setAutoScale(false);
    //  plot->coordinates()->axes[Z2].setAutoScale(false);
    //  plot->coordinates()->axes[Z3].setAutoScale(false);
    //  plot->coordinates()->axes[Z4].setAutoScale(false);

    plot->coordinates()->setGridLines(true, true, Qwt3D::BACK);

#if QT_VERSION < 0x050000
    plot->updateGL();
#else
    plot->update();
#endif
}
