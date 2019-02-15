#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QDialog>
#include <QScrollArea>
#include <QTextEdit>
#include <QSplitter>
#include <QFrame>
#include "titlebar.h"

#define BUTTON_HEIGHT 35
#define BUTTON_WIDTH 33
#define TITLEBAR_HEIGHT 40

enum StretchRectState
{
    NO_SELECT = 0, TOP_BORDER, BOTTOM_BORDER, LEFT_BORDER, RIGHT_BORDER,
    LEFT_TOP_RECT, LEFT_BOTTOM_RECT, RIGHT_TOP_RECT, RIGHT_BOTTOM_RECT,
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

private:
    Ui::TalkWindow *ui;

    //四条边
    QRect m_topBorderRect;
    QRect m_bottomBorderRect;
    QRect m_leftBorderRect;
    QRect m_rightBorderRect;
    //四个角
    QRect m_leftTopRect;
    QRect m_leftBottomRect;
    QRect m_rightTopRect;
    QRect m_rightBottomRect;

    bool   m_bMousePressed;    // 鼠标是否按下
    int    m_nMouseStyle;     // 鼠标样式

    QPoint m_moveStartPoint;
    QPoint m_endPoint;
    QRect windowRect;
    StretchRectState stretchState;

    /*视频，语音按钮栏*/
    QWidget *toolWidget;
    QPushButton *video;
    QPushButton *call;

    /*消息界面*/
    QFrame *content;
    //表情、文件、截图按钮
    QWidget *contentTool;
    QWidget *functionWidget;
    QPushButton *emotion;
    QPushButton *chooseFile;
    QPushButton *screen;

    QTextEdit *input;

    QSplitter *pSplitter;

    void calculateCurrentStretchRect();
    int setCursorStyle(const QPoint& curPoint);    // 当前位置设置鼠标样式
    void updateWindowStretchRect();
    StretchRectState getCurrentStretchState(QPoint curPoint);
    void updateWindowSize();
    void setSupportStretch(bool isSupportStretch);

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
};

#endif // TALKWINDOW_H
