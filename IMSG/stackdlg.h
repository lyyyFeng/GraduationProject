#ifndef STACKDLG_H
#define STACKDLG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>

class StackDlg : public QDialog
{
    Q_OBJECT
public:
    StackDlg(QWidget *parent = nullptr);
    ~StackDlg();

private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};

#endif // STACKDLG_H
