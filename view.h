#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QString>
// Forward Declaration
class QPushButton;
class QLineEdit;
class QHBoxLayout;
class Controller;

class iView
{

public:
    //explicit iView(QWidget *parent = nullptr);
    virtual void  setDollor(QString d) = 0;
    virtual ~iView() = default;
};


class View : public QWidget, public iView{
  Q_OBJECT
public:

  explicit View(QWidget *parent = nullptr, QString name = "MVC");
  virtual ~View() override;
  void setController(Controller* c);
  QString getDollor();
  QString getRuppes();
  void    setDollor(QString d) override;
  void    setRuppes(QString r);
  void gui();
public slots:
  void ConvertButtonClicked();
  void ClearButtonClicked();
private:
  QPushButton* press;
  QPushButton* clear;
  QLineEdit*   dollorinfo;
  QLineEdit*   ruppesinfo;
  QHBoxLayout* hlayout;
  Controller*  controller;
  QString      appName;
};
#endif // VIEW_H
