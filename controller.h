#ifndef CONTROLLER_H
#define CONTROLLER_H
//Forward Declaration
class Model;
class View;
class QString;

class Controller {
public:
  Controller(Model* m);
  virtual ~Controller();
  void OnConvertButtonClicked(View* v);
  void OnClearButtonClicked(View* v);
private:
  Model* model;
};
#endif // CONTROLLER_H