#ifndef MODEL_H
#define MODEL_H
class Model {
public:
  Model();
  ~Model();
  double ConvertRubIntoDollor(double rs);
  double GetDollorValue()const;
  double GetRubValue() const;
  void clear();
private:
  double r;
  double d;
};
#endif // MODEL_H
