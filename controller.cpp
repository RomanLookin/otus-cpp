#include "controller.h"
#include "model.h"
#include "view.h"
#include <QString>

Controller::Controller(Model* m):model(m){}
Controller::~Controller(){}
void Controller::OnConvertButtonClicked(View* v) {
  QString rub = v->getRub();
  model->ConvertRubIntoDollor(rub.toFloat());
  QString ds = QString::number(model->GetDollorValue());
  v->setDollor(ds);
}
void Controller::OnClearButtonClicked(View* v) {
  v->setDollor(QString());
  v->setRub(QString());
  model->clear();
}
