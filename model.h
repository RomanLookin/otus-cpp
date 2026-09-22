#ifndef MODEL_H
#define MODEL_H

class iModel
{
public:
    virtual double ConvertRuppesIntoDollor(double rs) = 0;
    virtual ~iModel() = default;
};


class Model:public iModel {
public:
  Model(double frtd_);
  ~Model() override;
  double ConvertRuppesIntoDollor (double rs)  override;
  double GetDollorValue()const;
  double GetRuppeValue() const;
  void clear();
private:
  double r;
  double d;
  double frtd;
};
#endif // MODEL_H
