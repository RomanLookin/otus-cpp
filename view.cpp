#include "view.h"
#include "controller.h"
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <iostream>

View::View(QWidget *parent, QString name)
  : QWidget(parent), appName(name) {
    gui();
  /*this->setWindowTitle(appName);
  //Create a horizontal container widgets.
  hlayout = new QHBoxLayout(this);
  hlayout->setSpacing(1);
  ruppesinfo = new QLineEdit(this);
  ruppesinfo->setPlaceholderText("RuppesInfo");
  dollorinfo = new QLineEdit(this);
  dollorinfo->setPlaceholderText("DollorInfo");
  QString buttonname = "Convert";
  press = new QPushButton(buttonname, this);
  QString clearname = "Clear";
  clear = new QPushButton(clearname, this);

  //Now add all child widgets inside parent one
  hlayout->addWidget(ruppesinfo);
  hlayout->addWidget(dollorinfo);
  hlayout->addWidget(press);
  hlayout->addWidget(clear);
  //Connect the appropriate signal
  connect(press, SIGNAL(clicked(bool)), this, SLOT(ConvertButtonClicked()));
  connect(clear, SIGNAL(clicked(bool)), this, SLOT(ClearButtonClicked()));*/
}
View::~View(){}
void View::setController(Controller* c) {controller = c;}
QString View::getDollor()        {return dollorinfo->text();}
QString View::getRuppes()        {return ruppesinfo->text();}
void View::setDollor(QString d)  {dollorinfo->setText(d);}
void View::setRuppes(QString r)  {ruppesinfo->setText(r);}
void View::ConvertButtonClicked(){controller->OnConvertButtonClicked();}//this);}
void View::ClearButtonClicked()  {controller->OnClearButtonClicked();}//this);}
/*void View::gui(){
    this->setWindowTitle(appName);
    //Create a horizontal container widgets.
    hlayout = new QHBoxLayout(this);
    hlayout->setSpacing(1);
    ruppesinfo = new QLineEdit(this);
    ruppesinfo->setPlaceholderText("RuppesInfo");
    dollorinfo = new QLineEdit(this);
    dollorinfo->setPlaceholderText("DollorInfo");
    QString buttonname = "Convert";
    press = new QPushButton(buttonname, this);
    QString clearname = "Clear";
    clear = new QPushButton(clearname, this);

    //Now add all child widgets inside parent one
    hlayout->addWidget(ruppesinfo);
    hlayout->addWidget(dollorinfo);
    hlayout->addWidget(press);
    hlayout->addWidget(clear);
    //Connect the appropriate signal
    connect(press, SIGNAL(clicked(bool)), this, SLOT(ConvertButtonClicked()));
    connect(clear, SIGNAL(clicked(bool)), this, SLOT(ClearButtonClicked()));


}*/
