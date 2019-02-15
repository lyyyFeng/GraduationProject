#include "talkwindow.h"
#include "ui_talkwindow.h"

#define TOOL_BUTTON_SIZE 30
#define STRETCH_RECT_WIDTH  8
#define STRETCH_RECT_HEIGHT 8
#define MIN_WIDTH   442
#define MIN_HEIGHT  495



TalkWindow::TalkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalkWindow),
    m_bMousePressed(false),
    m_nMouseStyle(NO_SELECT)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    initTitleBar();
    setToolWidget();
    setContentWidget();
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    setMouseTracking(true);
    updateWindowStretchRect();

    connect(titlebar->pButton1, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(titlebar->pButton2, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
    connect(titlebar->pButton3, SIGNAL(clicked()), this, SLOT(onButtonCloClicked()));
}

TalkWindow::~TalkWindow()
{
    delete ui;
}

void TalkWindow::initTitleBar()
{
    titlebar = new TitleBar(this);
    titlebar->setBackgroundColor(61, 184, 255, false);
    titlebar->move(0, 0);
    titlebar->raise();
    titlebar->setSize(BUTTON_WIDTH, BUTTON_HEIGHT, this->width(), TITLEBAR_HEIGHT);
    titlebar->setIcon(":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/maximize.svg", ":/Icon/Resources/icon/close.svg");
}

void TalkWindow::setToolWidget()
{
    toolWidget = new QWidget(this);
    video = new QPushButton(toolWidget);
    call = new QPushButton(toolWidget);

    video->setFixedSize(QSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE));
    call->setFixedSize(QSize(TOOL_BUTTON_SIZE, TOOL_BUTTON_SIZE));

    QHBoxLayout *toolLayout = new QHBoxLayout;
    toolLayout->addStretch();
    toolLayout->addWidget(video);
    toolLayout->addWidget(call);
    toolLayout->setSpacing(10);
    toolWidget->setLayout(toolLayout);

    toolWidget->setGeometry(3, TITLEBAR_HEIGHT, width() - 6, TITLEBAR_HEIGHT);
}

void TalkWindow::setContentWidget()
{
    pSplitter = new QSplitter(Qt::Vertical, this);
    pSplitter->setStyleSheet("QSplitter:handle{background-color:grey}");
    pSplitter->setHandleWidth(0);

    contentTool = new QWidget(this);
    functionWidget = new QWidget;
    functionWidget->setFixedHeight(30);
    //functionWidget->setStyleSheet("background-color:#000000;");

    emotion = new QPushButton;
    chooseFile = new QPushButton;
    screen = new QPushButton;
    content = new QFrame;
    content->setStyleSheet("QFrame {background-color:#FFFFFF;}");
    input = new QTextEdit;

    emotion->setFixedSize(QSize(25, 25));
    chooseFile->setFixedSize(QSize(25, 25));
    screen->setFixedSize(QSize(25, 25));

    QHBoxLayout *functionLayout = new QHBoxLayout(functionWidget);
    functionLayout->addWidget(emotion, 0, Qt::AlignTop);
    functionLayout->addWidget(chooseFile, 0, Qt::AlignTop);
    functionLayout->addWidget(screen, 0, Qt::AlignTop);
    functionLayout->addStretch();
    functionLayout->setSpacing(5);
    functionLayout->setContentsMargins(0, 0, 0, 0);
    functionWidget->setLayout(functionLayout);

    QVBoxLayout *contentLayout = new QVBoxLayout(contentTool);
    contentLayout->addWidget(functionWidget);
    contentLayout->addWidget(input);
    contentLayout->setSpacing(0);
    contentTool->setContentsMargins(0, 0, 0, 0);
    contentTool->setLayout(contentLayout);

    pSplitter->addWidget(content);
    pSplitter->addWidget(contentTool);
    pSplitter->setStretchFactor(0,95);
    pSplitter->setStretchFactor(1,5);
}

void TalkWindow::paintEvent(QPaintEvent *event)
{

}

void TalkWindow::resizeEvent(QResizeEvent *event)
{
    pSplitter->setGeometry(3, 2 * TITLEBAR_HEIGHT, width() - 6, height() - 3 * TITLEBAR_HEIGHT);
    toolWidget->setGeometry(3, TITLEBAR_HEIGHT, width() - 6, TITLEBAR_HEIGHT);
    event->ignore();
}

void TalkWindow::onButtonMinClicked()
{
    showMinimized();
}

void TalkWindow::onButtonMaxClicked()
{
    if(isMaximized())
    {
        titlebar->setIcon(":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/maximize.svg", ":/Icon/Resources/icon/close.svg");
        showNormal();
    }
    else
    {
        titlebar->setIcon(":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/maxback.svg", ":/Icon/Resources/icon/close.svg");
        showMaximized();
    }
}

void TalkWindow::onButtonCloClicked()
{
    close();
}

void TalkWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMousePressed = false;
    calculateCurrentStretchRect();
    event->ignore();
}

void TalkWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isMaximized())
    {
        return;
    }
//    stretchState = getCurrentStretchState(event->pos());
    QPoint curPoint = event->pos();

    //获取当前鼠标样式
    if (!m_bMousePressed)
    {
        m_nMouseStyle = setCursorStyle(curPoint);
    }
    //拉伸窗口
    if (m_bMousePressed && stretchState != NO_SELECT)
    {
        m_endPoint = this->mapToGlobal(event->pos());
        updateWindowSize();
    }
    //移动窗口
    if (m_bMousePressed && stretchState == NO_SELECT)
    {
        this->move(event->globalPos() - m_moveStartPoint);
    }
    updateWindowStretchRect();
    event->ignore();
}

void TalkWindow::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton)
    {
        m_bMousePressed = true;
        m_moveStartPoint = event->globalPos() - this->pos();
        //当前窗口位置大小
        windowRect = this->geometry();
    }
    event->ignore();    //表示继续向下传递事件，其他的控件还可以去获取
}


void TalkWindow::calculateCurrentStretchRect()
{
    int width_X = width() - STRETCH_RECT_WIDTH * 2;
    int height_Y = height() - STRETCH_RECT_HEIGHT * 2;
    m_topBorderRect = QRect(STRETCH_RECT_WIDTH, 0, width_X, STRETCH_RECT_HEIGHT);
    m_bottomBorderRect = QRect(STRETCH_RECT_WIDTH, height() - STRETCH_RECT_HEIGHT,
                               width_X, STRETCH_RECT_HEIGHT);
    m_leftBorderRect = QRect(0, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, height_Y);
    m_rightBorderRect = QRect(width() - STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT,
                              STRETCH_RECT_WIDTH, height_Y);
    m_leftTopRect = QRect(0, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_leftBottomRect = QRect(0, height() - STRETCH_RECT_HEIGHT,
                             STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightTopRect = QRect(width() - STRETCH_RECT_WIDTH, 0,
                           STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightBottomRect = QRect(width() - STRETCH_RECT_WIDTH, height() - STRETCH_RECT_HEIGHT,
                              STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
}

void TalkWindow::updateWindowStretchRect()
{
    calculateCurrentStretchRect();
}

StretchRectState TalkWindow::getCurrentStretchState(QPoint curPoint)
{
    StretchRectState stretchState;
    if (m_leftTopRect.contains(curPoint))
        stretchState = LEFT_TOP_RECT;
    else if (m_leftBottomRect.contains(curPoint))
        stretchState = LEFT_BOTTOM_RECT;
    else if (m_rightTopRect.contains(curPoint))
        stretchState = RIGHT_TOP_RECT;
    else if (m_rightBottomRect.contains(curPoint))
        stretchState = RIGHT_BOTTOM_RECT;
    else if (m_leftBorderRect.contains(curPoint))
        stretchState = LEFT_BORDER;
    else if (m_rightBorderRect.contains(curPoint))
        stretchState = RIGHT_BORDER;
    else if (m_topBorderRect.contains(curPoint))
        stretchState = TOP_BORDER;
    else if (m_bottomBorderRect.contains(curPoint))
        stretchState = BOTTOM_BORDER;
    else
        stretchState = NO_SELECT;
    return stretchState;
}

void TalkWindow::updateWindowSize()
{
    switch(stretchState)
    {
    case LEFT_BORDER:
    {
        QPoint topLeftPoint = windowRect.topLeft();
        topLeftPoint.setX(m_endPoint.x());
        windowRect.setTopLeft(topLeftPoint);
    }
        break;
    case RIGHT_BORDER:
    {
        QPoint bottomRightPoint = windowRect.bottomRight();
        bottomRightPoint.setX(m_endPoint.x());
        windowRect.setBottomRight(bottomRightPoint);
    }
        break;
    case TOP_BORDER:
    {
        QPoint topLeftPoint = windowRect.topLeft();
        topLeftPoint.setY(m_endPoint.y());
        windowRect.setTopLeft(topLeftPoint);
    }
        break;
    case BOTTOM_BORDER:
    {
        QPoint bottomRightPoint = windowRect.bottomRight();
        bottomRightPoint.setY(m_endPoint.y());
        windowRect.setBottomRight(bottomRightPoint);
    }
        break;
    case LEFT_TOP_RECT:
    {
        QPoint topLeftPoint = windowRect.topLeft();
        topLeftPoint.setX(m_endPoint.x());
        topLeftPoint.setY(m_endPoint.y());
        windowRect.setTopLeft(topLeftPoint);
    }
        break;
    case LEFT_BOTTOM_RECT:
    {
        QPoint bottomLeftPoint = windowRect.bottomLeft();
        bottomLeftPoint.setX(m_endPoint.x());
        bottomLeftPoint.setY(m_endPoint.y());
        windowRect.setBottomLeft(bottomLeftPoint);
    }
        break;
    case RIGHT_TOP_RECT:
    {
        QPoint topRightPoint = windowRect.topRight();
        topRightPoint.setX(m_endPoint.x());
        topRightPoint.setY(m_endPoint.y());
        windowRect.setTopRight(topRightPoint);
    }
        break;
    case RIGHT_BOTTOM_RECT:
    {
        QPoint bottomRightPoint = windowRect.bottomRight();
        bottomRightPoint.setX(m_endPoint.x());
        bottomRightPoint.setY(m_endPoint.y());
        windowRect.setBottomRight(bottomRightPoint);
    }
        break;
    default:
        break;
    }

    if (windowRect.width() < MIN_WIDTH)
    {
        windowRect.setLeft(this->geometry().left());
        windowRect.setWidth(MIN_WIDTH);
    }
    if (windowRect.height() < MIN_HEIGHT)
    {
        windowRect.setTop(this->geometry().top());
        windowRect.setHeight(MIN_HEIGHT);
    }
    this->setGeometry(windowRect);
}

int TalkWindow::setCursorStyle(const QPoint& curPoint)
{
    stretchState = getCurrentStretchState(curPoint);
    switch(stretchState)
    {
    case LEFT_TOP_RECT:
    case RIGHT_BOTTOM_RECT:
    {
        setCursor(Qt::SizeFDiagCursor);
    }
        break;
    case RIGHT_TOP_RECT:
    case LEFT_BOTTOM_RECT:
    {
        setCursor(Qt::SizeBDiagCursor);
    }
        break;
    case LEFT_BORDER:
    case RIGHT_BORDER:
    {
        setCursor(Qt::SizeHorCursor);
    }
        break;
    case TOP_BORDER:
    case BOTTOM_BORDER:
    {
        setCursor(Qt::SizeVerCursor);
    }
        break;
    default:
    {
        setCursor(Qt::ArrowCursor);
    }
        break;
    }

    return stretchState;
}
