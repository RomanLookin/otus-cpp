#ifndef CONTROLLER_H
#define CONTROLLER_H
//Forward Declaration
#include <memory>

class Model;
class View;
class QString;

class iController
{

public:
    //explicit iView(QWidget *parent = nullptr);
    virtual void  OnConvertButtonClicked() = 0;
    virtual ~iController() = default;
};

class Controller : public iController {
public:
  Controller(Model* m, View* v);
  Controller(std::shared_ptr<Model> m, std::shared_ptr<View> v);
  virtual ~Controller();
  void OnConvertButtonClicked() override;//View* v);
  void OnClearButtonClicked();//View* v);
private:
  std::shared_ptr<Model> model;
  std::shared_ptr<View> view;
};
#endif // CONTROLLER_H
