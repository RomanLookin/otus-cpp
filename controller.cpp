#include "controller.h"
#include "model.h"
#include "view.h"
#include <QString>


Controller::Controller(Model* m, View* v):model(m), view(v){}
Controller::Controller(std::shared_ptr<Model> m, std::shared_ptr<View> v):model(m), view(v){}
Controller::~Controller(){}
void Controller::OnConvertButtonClicked(){//View* v) {
  QString ruppes = view->getRuppes();
  model->ConvertRuppesIntoDollor(ruppes.toFloat());
  QString ds = QString::number(model->GetDollorValue());
  view->setDollor(ds);
}
void Controller::OnClearButtonClicked(){//View* v) {
  view->setDollor(QString());
  view->setRuppes(QString());
  model->clear();
}
