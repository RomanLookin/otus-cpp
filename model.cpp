#include "model.h"

Model::Model(double frtd_): r(0),d(0),frtd(frtd_) {}
Model::~Model(){}
double Model::ConvertRuppesIntoDollor(double rs) {
  r = rs;
  d = r/frtd;//64.0;
  return d;
}
double Model::GetDollorValue() const { return d;}
double Model::GetRuppeValue()  const { return r;}
void Model::clear() {
  r = 0;
  d = 0;
}
