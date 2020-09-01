#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initItems();
    void connectItems();
    void keyPressEvent(QKeyEvent *event);
private slots:
    void setPlus();
    void setMin();
    void setMult();
    void setDiv();
    void setNeg();
    void clear();
    void back();
    void output();
    void keyPressed();
private:
    QLineEdit * entry;
    QPushButton ** numbers;
    QPushButton * equal;
    QPushButton * plus;
    QPushButton * min;
    QPushButton * mult;
    QPushButton * div;
    QPushButton * neg;
    QPushButton * clearBtn;
    QPushButton * backBtn;

    QGridLayout * glayout;
    QWidget * topWidget;


    double first;
    double second;
    double result;
    char mode;
};

#endif // MAINWINDOW_H
