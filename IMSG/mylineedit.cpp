#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget* parent)
    : QLineEdit (parent)
{}

MyLineEdit::~MyLineEdit()
{}

void MyLineEdit::setPlaceholderText(const QString &text)
{
    placeHolderText = text;
    QLineEdit::setPlaceholderText(text);
}

void MyLineEdit::focusInEvent(QFocusEvent *event)
{
    if(this->text().isEmpty())
    {
        QLineEdit::setPlaceholderText("");
    }
    emit signalIsMouseIn(true);
    QLineEdit::focusInEvent(event);
}

void MyLineEdit::focusOutEvent(QFocusEvent *event)
{
    if(this->text().isEmpty())
    {
        this->setPlaceholderText(placeHolderText);
    }
    emit signalIsMouseIn(false);
    QLineEdit::focusOutEvent(event);
}

void MyLineEdit::setStyleSheet(const QString style)
{
    QLineEdit::setStyleSheet(style);
}
