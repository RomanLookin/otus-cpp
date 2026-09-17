#include "model.h"

Model::Model(): r(),d() {}
Model::~Model(){}
double Model::ConvertRubIntoDollor(double rs) {
  r = rs;
  d = r/64.0;
  return d;
}
double Model::GetDollorValue() const { return d;}
double Model::GetRubValue()  const { return r;}
void Model::clear() {
  r = 0;
  d = 0;
}
