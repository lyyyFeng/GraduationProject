#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent),
    m_colorR(255), m_colorG(255), m_colorB(255), m_isTransparent(false)
{
    initTitleBar();
    parentWin = parent;
    QFile file(":/Qss/Resources/qss/loginWindow.qss");
    if(file.open(QFile::ReadOnly)){
        QString style = QString::fromLatin1(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }

    //setMouseTracking(true);
}

TitleBar::~TitleBar()
{}

void TitleBar::setIcon(const QString set, const QString min, const QString clo)
{
    QIcon setIcon, minIcon, cloIcon;
    setIcon.addFile(set);
    pButton1->setIcon(setIcon);
    pButton1->setChecked(true);
    minIcon.addFile(min);
    pButton2->setIcon(minIcon);
    cloIcon.addFile(clo);
    pButton3->setIcon(cloIcon);
}

void TitleBar::setSize(int width, int height, int titalWidth, int titalHeight)
{
    //pIconLabel->setFixedSize(QSize(width, height));
    //pTitelContent->setFixedSize(QSize(titalWidth / 2, height));
    pButton1->setFixedSize(QSize(width, height));
    pButton2->setFixedSize(QSize(width, height));
    pButton3->setFixedSize(QSize(width, height));
    this->setFixedSize(titalWidth, titalHeight);
}

void TitleBar::initTitleBar()
{
    pIconLabel = new QLabel();

    pTitelContent = new QLabel();
    pTitelContent->setScaledContents(true);
    pTitelContent->setText(tr("小陈"));
    pTitelContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pTitelContent->setAlignment(Qt::AlignVCenter);


    pButton1 = new QPushButton(this);
    pButton2 = new QPushButton(this);
    pButton3 = new QPushButton(this);

    pButton1->setObjectName("ButtonSet");
    pButton2->setObjectName("ButtonMin");
    pButton3->setObjectName("ButtonClo");

    QHBoxLayout *qHBoxLayout = new QHBoxLayout(this);
    //qHBoxLayout->addStretch();
    qHBoxLayout->addWidget(pIconLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    //qHBoxLayout->addSpacing(5);
    qHBoxLayout->addStretch();
    qHBoxLayout->addWidget(pTitelContent, 0, Qt::AlignHCenter);
    qHBoxLayout->addStretch();
    //qHBoxLayout->addSpacing(1);
    qHBoxLayout->addWidget(pButton1, 0, Qt::AlignRight | Qt::AlignTop);
    qHBoxLayout->addWidget(pButton2, 0, Qt::AlignRight | Qt::AlignTop);
    qHBoxLayout->addWidget(pButton3, 0, Qt::AlignRight | Qt::AlignTop);
    qHBoxLayout->setContentsMargins(80, 0, 0, 0);
    qHBoxLayout->setSpacing(0); //组件之间的间隔

    this->setWindowFlags(Qt::FramelessWindowHint);
}

void TitleBar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    m_isTransparent = isTransparent;
    update();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(isKeepPressed)
    {
        // 将父窗体移动到父窗体之前的位置加上鼠标移动的位置【event->globalPos()- mPntStart】
        parentWin->move(parentWin->geometry().topLeft() + event->globalPos()- mPntStart);
        // 将鼠标在屏幕中的位置替换为新的位置
        mPntStart = event->globalPos();
    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    // 鼠标左键按下事件
        if (event->button() == Qt::LeftButton)
        {
            // 记录鼠标状态
            isKeepPressed = true;
            // 记录鼠标在屏幕中的位置
            mPntStart = event->globalPos();
        }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isKeepPressed = false;
    }
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    if(!m_isTransparent)
    {
        //设置背景色;
        QPainter painter(this);
        QPainterPath pathBack;
        pathBack.setFillRule(Qt::WindingFill);
        pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    }

    // 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
    if (this->width() != this->parentWidget()->width())
    {
        this->setFixedWidth(this->parentWidget()->width());
    }
    QWidget::paintEvent(event);
}
