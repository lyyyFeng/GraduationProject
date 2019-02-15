#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    initTitleBar();
    initLineEdit();
    //ui->label->setStyleSheet("QLabel {background-color: transparent;}");

    //this->setAutoFillBackground(true);//必须有这条语句
    this->setPalette(QPalette(QColor(255,255,255)));


    //头像添加阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-3, 3);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(6);
    ui->labelFace->setGraphicsEffect(shadow_effect);

    QMovie *movie = new QMovie(":/Icon/Resources/icon/loginBG.gif");
    ui->label->setMovie(movie);
    movie->start();

    this->setStyleSheet("QLineEdit{font-size:13px;background:transparent;border:none;border-bottom:1px solid rgb(229, 229, 229);}\
                            QLineEdit:hover{border-bottom:1px solid rgb(193,193, 193);}\
                            QLineEdit:focus{border-bottom:1px solid rgb(18, 183, 245);}");


    ui->registerButton->setStyleSheet("QPushButton{font: 25 10pt \"Microsoft JhengHei UI Light\";\
                                       border:none;\
                                       background:transparent;\
                                       color: rgb(89, 89, 89);}\
                                       QPushButton:hover{color: rgb(31, 31, 31);} \
                                       QPushButton:pressed{color: rgb(39, 183, 255);}");



    connect(titlebar->pButton1, SIGNAL(clicked()),this, SLOT(onButtonSetClicked()));
    connect(titlebar->pButton2, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(titlebar->pButton3, SIGNAL(clicked()), this, SLOT(onButtonCloClicked()));

    //设置tab顺序
    QWidget::setTabOrder(pLineEditAccount, pLineEditPasswd);
    QWidget::setTabOrder(pLineEditPasswd, pRemenberPwd);
    QWidget::setTabOrder(pRemenberPwd, pAutoLogin);
    QWidget::setTabOrder(pAutoLogin, pforgetPwd);
    QWidget::setTabOrder(pforgetPwd, ui->registerButton);
    QWidget::setTabOrder(ui->registerButton, ui->loginButton);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::initTitleBar()
{
    titlebar = new TitleBar(this);
    titlebar->move(0, 0);
    titlebar->raise();
    titlebar->setBackgroundColor(255, 255, 255, true);
    titlebar->setSize(BUTTON_WIDTH, BUTTON_HEIGHT, ui->label->width() + 1, TITLEBAR_HEIGHT);
    titlebar->setIcon(":/Icon/Resources/icon/setting.svg", ":/Icon/Resources/icon/minize.svg", ":/Icon/Resources/icon/close.svg");
}

void LoginWindow::initLineEdit()
{
    QLabel *pLabelAccount = new QLabel;
    pLabelAccount->setFixedSize(QSize(20, 20));
    pLabelAccount->setPixmap(QIcon(":/Icon/Resources/icon/account.svg").pixmap(pLabelAccount->size()));

    QLabel *pLabelPasswd = new QLabel;
    pLabelPasswd->setFixedSize(QSize(20, 20));
    pLabelPasswd->setPixmap(QIcon(":/Icon/Resources/icon/passwd.svg").pixmap(pLabelPasswd->size()));

    QPushButton *pButtonPullDown = new QPushButton;
    pButtonPullDown->setCursor(Qt::ArrowCursor);
    pButtonPullDown->setFixedSize(QSize(20, 20));
    pButtonPullDown->setStyleSheet("QPushButton{border-image:url(:/Icon/Resources/icon/pullDown.svg);}\
                                        QPushButton:hover{border-image:url(:/Icon/Resources/icon/pullDown.svg)}");

    QPushButton *pButtonKeyborad = new QPushButton;
    pButtonKeyborad->setCursor(Qt::ArrowCursor);
    pButtonKeyborad->setFixedSize(QSize(20,20));
    pButtonKeyborad->setCursor(QCursor(Qt::PointingHandCursor));
    pButtonKeyborad->setStyleSheet("QPushButton{border-image:url(:/Icon/Resources/icon/keyboard.svg);}\
                                        QPushButton:hover{border-image:url(:/Icon/Resources/icon/keyboard.svg);}\
                                        QPushButton:pressed{border-image:url(:/Icon/Resources/icon/keyboard.svg);}");

    pLineEditAccount = new MyLineEdit;
    pLineEditAccount->setPlaceholderText("用户账号/手机/邮箱");
    pLineEditAccount->setTextMargins(25, 0, 25, 0);
    pLineEditAccount->setFixedSize(QSize(238, 28));
    //pLineEditAccount->setStyleSheet("QLineEdit{font: 25 10pt;}");

    connect(pLineEditAccount, &MyLineEdit::signalIsMouseIn, this, [=](bool isMouseIn)
    {
       if(isMouseIn)
       {
           pLabelAccount->setPixmap(QIcon(":/Icon/Resources/icon/account_focus.svg").pixmap(pLabelAccount->size()));
           //pLineEditAccount->setStyleSheet("QLineEdit{font: 75 13pt \"Microsoft JhengHei\";}");
       }
       else
       {
           pLabelAccount->setPixmap(QIcon(":/Icon/Resources/icon/account.svg").pixmap(pLabelAccount->size()));
       }
    });


    QHBoxLayout *pHAccountLayout = new QHBoxLayout(pLineEditAccount);
    pHAccountLayout->addWidget(pLabelAccount);
    pHAccountLayout->addStretch();
    pHAccountLayout->addWidget(pButtonPullDown);
    pHAccountLayout->setMargin(0);

    pLineEditPasswd = new MyLineEdit;
    //pLineEditPasswd->setAlignment(Qt::AlignCenter);
    pLineEditPasswd->setPlaceholderText("密码");
    pLineEditPasswd->setEchoMode(QLineEdit::Password);
    pLineEditPasswd->setTextMargins(25, 0, 25, 0);
    pLineEditPasswd->setFixedSize(QSize(238, 28));
    connect(pLineEditPasswd, &MyLineEdit::signalIsMouseIn, this, [=](bool isMouseIn)
    {
       if(isMouseIn)
       {
           pLabelPasswd->setPixmap(QIcon(":/Icon/Resources/icon/passwd_focus.svg").pixmap(pLabelPasswd->size()));
           pLineEditPasswd->setFocus();
       }
       else
       {
           pLabelPasswd->setPixmap(QIcon(":/Icon/Resources/icon/passwd.svg").pixmap(pLabelPasswd->size()));
       }
    });

    //复选框
    pAutoLogin = new QCheckBox("自动登录", this);
    pAutoLogin->setFixedSize(QSize(80, 16));
    pAutoLogin->setStyleSheet("QCheckBox{font: 25 10pt \"Microsoft JhengHei UI Light\";\
                                color: rgb(89, 89, 89);}");


    pRemenberPwd = new QCheckBox("记住密码", this);
    pRemenberPwd->setFixedSize(QSize(80, 16));
    pRemenberPwd->setStyleSheet("QCheckBox{font: 25 10pt \"Microsoft JhengHei UI Light\";\
                                  color: rgb(89, 89, 89);}");


    pforgetPwd = new QPushButton;
    pforgetPwd->setText(tr("找回密码"));
    pforgetPwd->setFixedSize(QSize(55, 16));
    pforgetPwd->setFlat(true);
    pforgetPwd->setCursor(QCursor(Qt::PointingHandCursor));
    pforgetPwd->setStyleSheet("QPushButton{font: 25 10pt \"Microsoft JhengHei UI Light\";\
                                              border:none;\
                                              background:transparent;\
                                              color: rgb(89, 89, 89);}\
                                              QPushButton:hover{color: rgb(31, 31, 31);} \
                                              QPushButton:pressed{color: rgb(39, 183, 255);}");

    QHBoxLayout *pCheckBoxLayout = new QHBoxLayout;
    pCheckBoxLayout->addWidget(pAutoLogin);
    pCheckBoxLayout->addWidget(pRemenberPwd);
    pCheckBoxLayout->addWidget(pforgetPwd);
    pCheckBoxLayout->setMargin(0);

    QHBoxLayout *pHpwdLayout = new QHBoxLayout(pLineEditPasswd);
    pHpwdLayout->addWidget(pLabelPasswd);
    pHpwdLayout->addStretch();
    pHpwdLayout->addWidget(pButtonKeyborad);
    pHpwdLayout->setMargin(0);

    QVBoxLayout *pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->addStretch();
    pVBoxLayout->addWidget(pLineEditAccount);
    pVBoxLayout->addWidget(pLineEditPasswd);
    pVBoxLayout->addLayout(pCheckBoxLayout);
    pVBoxLayout->addStretch();
    pVBoxLayout->setSpacing(12);
    pVBoxLayout->setMargin(0);

    QHBoxLayout *pLineEditLayout = new QHBoxLayout(this);
    pLineEditLayout->addStretch();
    pLineEditLayout->setContentsMargins(20, 100, 0, 0);
    pLineEditLayout->addLayout(pVBoxLayout);
    pLineEditLayout->addStretch();
    //pLineEditLayout->setMargin(0);
}

void LoginWindow::paintEvent(QPaintEvent *)
{
    QString file = "E:\\GraduationProject\\IMSG\\Resources\\head.jpg";
    QPixmap pixmapa(file);
    QPixmap pixmap(65,65);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(1, 1, 65, 65);
    painter.setClipPath(path);
    painter.drawPixmap(1, 1, 65, 65, pixmapa);
    ui->labelFace->setPixmap(pixmap);


    /*----------------------*/
    /*
    QPainter painter1(this);
    QPixmap m_shadow;
    m_shadow.load(":/Icon/Resources/icon/m_shadow.png");
    QRect bottom(5, 136, 200, 1);
    QRect top(5, 0, 200, 1);
    QRect left(0, 3, 1, 133);
    QRect right(205, 3, 1, 133);
    QRect topRight(205, 0, 1, 1);
    QRect topLeft(0, 0, 1, 1);
    QRect bottomLeft(0, 136, 1, 1);
    QRect bottomRight(205, 136, 1, 1);
    QRect tBottom(5, this->height() - 1, this->width() - 1, 1);
    QRect tTop(5, 0, this->width() - 1, 1);
    QRect tLeft(0, 1, 1, this->height() - 1);
    QRect tRight(this->width() - 1, 3, 1, this->height() - 1);
    QRect tTopLeft(0, 0, 5, 1);
    QRect tTopRight(this->width() - 5, 0, 1, 1);
    QRect tBottomLeft(0, this->height() - 4, 1, 1);
    QRect tBottomRight(this->width() - 5, this->height() - 7, 1, 1);
    painter1.drawPixmap(tBottom, m_shadow, bottom);
    painter1.drawPixmap(tTop, m_shadow, top);
    painter1.drawPixmap(tLeft, m_shadow, left);
    painter1.drawPixmap(tRight, m_shadow, right);
    painter1.drawPixmap(tTopRight, m_shadow, topRight);
    painter1.drawPixmap(tTopLeft, m_shadow, topLeft);
    painter1.drawPixmap(tBottomLeft, m_shadow, bottomLeft);
    painter1.drawPixmap(tBottomRight, m_shadow, bottomRight);
    */

    QPainter painter1(this);
    QColor color(0, 0, 0, 0);
    for(int i=0; i<4; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(2-i, 2-i, this->width()-(2-i)*2, this->height()-(2-i)*2);
        //color.setAlpha(50 - i*10);
        color.setAlpha(30);
        painter1.setPen(color);
        painter1.drawPath(path);
    }

}


//槽实现
void LoginWindow::onButtonSetClicked()
{

}

void LoginWindow::onButtonMinClicked()
{
    setWindowState(Qt::WindowMinimized);
}

void LoginWindow::onButtonCloClicked()
{
    close();
}
