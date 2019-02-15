#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QIcon>
#include <QSvgRenderer>
#include <QDebug>
#include <QPainter>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void setIcon(const QString set, const QString min, const QString clo);
    void setSize(int width, int height, int titalWidth, int titalHeight);
    void setBackgroundColor(int r, int g, int b, bool isTransparent);

    QLabel *pIconLabel;
    QLabel *pTitelContent;
    QPushButton *pButton1;
    QPushButton *pButton2;
    QPushButton *pButton3;

signals:
    //按钮信号
    //void signalButtonSet();
    //void signalButtonMin();
    //void signalButtonClo();

public slots:

private:
    void initTitleBar();
    QPoint mPntStart;   //鼠标上次移动开始时相对屏幕的位置
    bool isKeepPressed; //鼠标是否持续按住

    // 标题栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;
    bool m_isTransparent;

    QWidget *parentWin;

protected:
    //重写鼠标事件
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

};

#endif // TITLEBAR_H
