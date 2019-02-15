#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();

    void setStyleSheet(const QString style);
    void setPlaceholderText(const QString &text);

private:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    QString placeHolderText;

signals:
    void signalIsMouseIn(bool isFocusIn);

};

#endif // MYLINEEDIT_H
