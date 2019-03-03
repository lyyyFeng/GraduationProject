#include "talkwindow.h"
#include "ui_talkwindow.h"

#define TOOL_BUTTON_SIZE 30
#define STRETCH_RECT_WIDTH  8
#define STRETCH_RECT_HEIGHT 8
#define MIN_WIDTH   442
#define MIN_HEIGHT  495



TalkWindow::TalkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalkWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    initTitleBar();
    setToolWidget();
    setContentWidget();
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    setMouseTracking(true);

    setStyleSheet("background-color:#FFFFFF;");

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
    pSplitter->setStyleSheet("QSplitter:handle{background-color:rgb(184, 184, 184);}");
    pSplitter->setHandleWidth(1);

    functionWidget = new QWidget;
    functionWidget->setFixedHeight(40);
    //functionWidget->setStyleSheet("background-color:#000000;");

    emotion = new QPushButton;
    chooseFile = new QPushButton;
    screen = new QPushButton;
    content = new QListWidget;
    content->setMinimumHeight(40);
    content->setStyleSheet("QListWidget{background-color: rgb(255, 255, 255); color:rgb(51,51,51); border: 0px solid;outline:0px;}\
                           QListWidget::Item{background-color: rgb(255, 255, 255);} ");
    input = new QTextEdit;
    input->setStyleSheet("border:0;");

    emotion->setFixedSize(QSize(20, 20));
    emotion->setStyleSheet("QPushButton{border:0; border-radius:10px; border-image:url(:/Icon/Resources/icon/emotion.png);overflow:hidden;}\
                            QPushButton:hover{ background-color:yellow;}");

    chooseFile->setFixedSize(QSize(30, 30));
    screen->setFixedSize(QSize(30, 30));

    QHBoxLayout *functionLayout = new QHBoxLayout(functionWidget);
    functionLayout->addWidget(emotion, 0, Qt::AlignTop);
    functionLayout->addWidget(chooseFile, 0, Qt::AlignTop);
    functionLayout->addWidget(screen, 0, Qt::AlignTop);
    functionLayout->addStretch();
    functionLayout->setSpacing(8);
    functionLayout->setContentsMargins(8, 10, 0, 0);
    functionWidget->setLayout(functionLayout);

    pSplitter->addWidget(content);
    pSplitter->addWidget(functionWidget);
    pSplitter->addWidget(input);
    pSplitter->setStretchFactor(1,0);
    pSplitter->setStretchFactor(0,90);
    pSplitter->setStretchFactor(1,5);
    pSplitter->setStretchFactor(2,5);
    pSplitter->setCollapsible(0, false);
    pSplitter->setCollapsible(1, false);

    QSplitterHandle *handle = pSplitter->handle(2);
    if(handle)
    {
        handle->setFixedWidth(0);
    }
}

void TalkWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color(0, 0, 0, 0);
    for(int i=0; i<4; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(2-i, 2-i, this->width()-(2-i)*2, this->height()-(2-i)*2);
        //color.setAlpha(50 - i*10);
        color.setAlpha(30);
        painter.setPen(color);
        painter.drawPath(path);
    }
    event->ignore();
}

void TalkWindow::resizeEvent(QResizeEvent *event)
{
    pSplitter->setGeometry(3, 2 * TITLEBAR_HEIGHT, width() - 6, height() - 3 * TITLEBAR_HEIGHT);
    toolWidget->setGeometry(3, TITLEBAR_HEIGHT, width() - 6, TITLEBAR_HEIGHT);
    ui->closeBtn->move(width() - 186, height() - 39);
    ui->sendBtn->move(width() - 96, height() - 39);

    if(!isMaximized())
    {
        titlebar->setIcon(":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/maximize.svg", ":/Icon/Resources/icon/close.svg");
    }
    else
    {
        titlebar->setIcon(":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/maxback.svg", ":/Icon/Resources/icon/close.svg");
    }

    for(int i = 0; i < content->count(); i++) {
        Message* messageW = (Message*)content->itemWidget(content->item(i));
        QListWidgetItem* item = content->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->user());
    }

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
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        if (dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void TalkWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if (!isLeftPressDown)
    {
        this->judgeRegionSetCursor(gloPoint);
    }
    else
    {
        if (dir != NONE)
        {
            QRect rMove(tl, rb);

            switch (dir) {
            case LEFT:
                if (rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if (rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if (rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if (rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        }
        else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    QWidget::mouseMoveEvent(event);
}

void TalkWindow::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if (dir != NONE) {
            this->mouseGrabber();
        }
        else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    default:
        QWidget::mousePressEvent(event);
    }
}

void TalkWindow::judgeRegionSetCursor(const QPoint& currentPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = currentPoint.x();
    int y = currentPoint.y();

    if (tl.x() + Padding >= x && tl.x() <= x && tl.y() + Padding >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if (x >= rb.x() - Padding && x <= rb.x() && y >= rb.y() - Padding && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (x <= tl.x() + Padding && x >= tl.x() && y >= rb.y() - Padding && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - Padding && y >= tl.y() && y <= tl.y() + Padding) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= tl.x() + Padding && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - Padding) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (y >= tl.y() && y <= tl.y() + Padding) {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (y <= rb.y() && y >= rb.y() - Padding) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void TalkWindow::dealMessage(Message *message, QListWidgetItem *item, QString text, QString time, Message::User_Type user_type)
{
    message->setFixedWidth(this->width());
    QSize size = message->fontRect(text);
    item->setSizeHint(size);
    message->setText(text, time, size, user_type);
    content->setItemWidget(item, message);
}

void TalkWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(content->count() > 0) {
        QListWidgetItem* lastItem = content->item(content->count() - 1);
        Message* messageW = (Message*)content->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        Message* messageTime = new Message(content->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(content);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, Message::User_Time);
        content->setItemWidget(itemTime, messageTime);
    }
}

void TalkWindow::on_sendBtn_clicked()
{
    QString msg = input->toPlainText();
    input->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中
    if(content->count() > 4) {
        if(isSending) {
            dealMessageTime(time);

            Message* messageW = new Message(content->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(content);
            dealMessage(messageW, item, msg, time, Message::User_Me);
        } else {
            bool isOver = true;
            for(int i = content->count() - 1; i > 0; i--) {
                Message* messageW = (Message*)content->itemWidget(content->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                Message* messageW = new Message(content->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(content);
                dealMessage(messageW, item, msg, time, Message::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            Message* messageW = new Message(content->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(content);
            dealMessage(messageW, item, msg, time, Message::User_Other);
        }
    }
    content->setCurrentRow(content->count()-1);
}
