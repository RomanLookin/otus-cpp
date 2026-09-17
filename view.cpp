#include "view.h"
#include "controller.h"
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <iostream>

View::View(QWidget *parent, QString name)
  : QWidget(parent), appName(name) {
  this->setWindowTitle(appName);
  //Create a horizontal container widgets.
  hlayout = new QHBoxLayout(this);
  hlayout->setSpacing(1);
  rubinfo = new QLineEdit(this);
  rubinfo->setPlaceholderText("RubInfo");
  dollorinfo = new QLineEdit(this);
  dollorinfo->setPlaceholderText("DollorInfo");
  QString buttonname = "Convert";
  press = new QPushButton(buttonname, this);
  QString clearname = "Clear";
  clear = new QPushButton(clearname, this);

  //Now add all child widgets inside parent one
  hlayout->addWidget(rubinfo);
  hlayout->addWidget(dollorinfo);
  hlayout->addWidget(press);
  hlayout->addWidget(clear);
  //Connect the appropriate signal
  connect(press, SIGNAL(clicked(bool)), this, SLOT(ConvertButtonClicked()));
  connect(clear, SIGNAL(clicked(bool)), this, SLOT(ClearButtonClicked()));
}
View::~View(){}
void View::setController(Controller* c) {controller = c;}
QString View::getDollor()        {return dollorinfo->text();}
QString View::getRub()        {return rubinfo->text();}
void View::setDollor(QString d)  {dollorinfo->setText(d);}
void View::setRub(QString r)  {rubinfo->setText(r);}
void View::ConvertButtonClicked(){controller->OnConvertButtonClicked(this);}
void View::ClearButtonClicked()  {controller->OnClearButtonClicked(this);}
