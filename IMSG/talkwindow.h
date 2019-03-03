#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QSplitter>
#include <QFrame>
#include "titlebar.h"
#include "message.h"

#define BUTTON_HEIGHT 35
#define BUTTON_WIDTH 33
#define TITLEBAR_HEIGHT 40

//enum StretchRectState
//{
//    NO_SELECT = 0, TOP_BORDER, BOTTOM_BORDER, LEFT_BORDER, RIGHT_BORDER,
//    LEFT_TOP_RECT, LEFT_BOTTOM_RECT, RIGHT_TOP_RECT, RIGHT_BOTTOM_RECT,
//};

enum Direction {
    UP, DOWN, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE
};

namespace Ui {
class TalkWindow;
}

class TalkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TalkWindow(QWidget *parent = nullptr);
    ~TalkWindow();

    void dealMessage(Message *message, QListWidgetItem *item, QString text, QString time, Message::User_Type user_type);
    void dealMessageTime(QString curMsgTime);

private:
    Ui::TalkWindow *ui;

    const int Padding = 2;
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;   // 窗口移动拖动时需要记住的点
    // 窗口大小改变时，记录改变方向
    Direction dir;

    /*视频，语音按钮栏*/
    QWidget *toolWidget;
    QPushButton *video;
    QPushButton *call;

    /*消息界面*/
    QListWidget *content;
    QWidget *functionWidget;
    QPushButton *emotion;
    QPushButton *chooseFile;
    QPushButton *screen;

    QTextEdit *input;

    QSplitter *pSplitter;

    void judgeRegionSetCursor(const QPoint&);   //判断位置

    void setToolWidget();   //设置视频语音按钮栏
    void setContentWidget();

signals:
    //按钮信号
    //void signalButtonSet();
    //void signalButtonMin();
    //void signalButtonClo();

public slots:
    //按钮自定义槽
    void onButtonMinClicked();
    void onButtonMaxClicked();
    void onButtonCloClicked();

protected:
    void initTitleBar();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    TitleBar *titlebar;
private slots:
    void on_sendBtn_clicked();
};

#endif // TALKWINDOW_H
