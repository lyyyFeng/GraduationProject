#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include <QGraphicsDropShadowEffect>
#include <QRect>
#include <QtMath>
#include <QCheckBox>
#include "titlebar.h"
#include "mylineedit.h"

#define BUTTON_HEIGHT 30
#define BUTTON_WIDTH 30
#define TITLEBAR_HEIGHT 60

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

    MyLineEdit *pLineEditAccount;
    MyLineEdit *pLineEditPasswd;
    QCheckBox *pAutoLogin;
    QCheckBox *pRemenberPwd;
    QPushButton *pforgetPwd;

public slots:
    //按钮自定义槽
    void onButtonSetClicked();
    void onButtonMinClicked();
    void onButtonCloClicked();

protected:
    void initTitleBar();
    void initLineEdit();
    void paintEvent(QPaintEvent *event);

    TitleBar *titlebar;
};

#endif // LOGINWINDOW_H
