//#include "mainwindow.h"
#include <QApplication>
#include "view.h"
#include "model.h"
#include "controller.h"
#include <memory>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

void View::gui(){

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


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // Model model(64.0);
   // View window;

    auto sptr_model = std::make_shared<Model>(64.0);
    auto sptr_view = std::make_shared<View>();
    //Controller ctrl(&model, &window);
    Controller ctrl(sptr_model, sptr_view);
    //window.setController(&ctrl);
    //window.show();
    sptr_view->setController(&ctrl);
    sptr_view->show();
    return a.exec();
}
