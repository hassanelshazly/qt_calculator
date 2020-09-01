#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initItems();
    connectItems();
    this->setGeometry(200,200,400,300);
    this->setCentralWidget(topWidget);
    topWidget->setLayout(glayout);
    entry->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    glayout->addWidget(entry,0,0,1,5);
    glayout->addWidget(plus,1 ,3);
    glayout->addWidget(min,2 ,3);
    glayout->addWidget(mult,1 ,4);
    glayout->addWidget(div,2 ,4);
    glayout->addWidget(neg,3 ,4);
    glayout->addWidget(equal,3 ,3);

    glayout->addWidget(clearBtn,4 ,4);
    glayout->addWidget(backBtn,4 ,3);

    // Add numbers
    glayout->addWidget(numbers[0],4,1);
    glayout->addWidget(numbers[7],1,0);
    glayout->addWidget(numbers[8],1,1);
    glayout->addWidget(numbers[9],1,2);
    glayout->addWidget(numbers[4],2,0);
    glayout->addWidget(numbers[5],2,1);
    glayout->addWidget(numbers[6],2,2);
    glayout->addWidget(numbers[1],3,0);
    glayout->addWidget(numbers[2],3,1);
    glayout->addWidget(numbers[3],3,2);

//    for(int i = 0; i < 6 ; i++) {
//        glayout->setColumnMinimumWidth(i,30);
//        glayout->setRowMinimumHeight(i,30);
//    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::initItems()
{
#define MIN 40
    glayout = new QGridLayout();
    topWidget = new QWidget(this);
    entry = new QLineEdit(this);
    entry->setMinimumSize(400,35);
    entry->setAlignment(Qt::AlignRight);
    entry->setReadOnly(true);
//    entry->setClearButtonEnabled(true);

    equal = new QPushButton("=", this);
    plus = new QPushButton("+", this);
    min = new QPushButton("-", this);
    mult = new QPushButton("*", this);
    div = new QPushButton("/", this);
    neg = new QPushButton("+/-", this);
    clearBtn = new QPushButton("C", this);
    backBtn = new QPushButton("x", this);
    numbers = new QPushButton *[10];
    for(int i = 0; i < 10; i++) {
        numbers[i] = new QPushButton(QString::number(i), this);
        numbers[i]->setMaximumSize(MIN*2,MIN);
    }

    result = first = second = 0;

    equal->setMaximumSize(MIN*2,MIN);
    min->setMaximumSize(MIN*2,MIN);
    plus->setMaximumSize(MIN*2,MIN);
    mult->setMaximumSize(MIN*2,MIN);
    div->setMaximumSize(MIN*2,MIN);
    neg->setMaximumSize(MIN*2,MIN);
    clearBtn->setMaximumSize(MIN*2,MIN);
    backBtn->setMaximumSize(MIN*2,MIN);
}

void MainWindow::connectItems()
{
    connect(plus, SIGNAL(clicked()), this, SLOT(setPlus()));
    connect(min, SIGNAL(clicked()), this, SLOT(setMin()));
    connect(mult, SIGNAL(clicked()), this, SLOT(setMult()));
    connect(div, SIGNAL(clicked()), this, SLOT(setDiv()));
    connect(neg, SIGNAL(clicked()), this, SLOT(setNeg()));
    connect(equal, SIGNAL(clicked()), this, SLOT(output()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clear()));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(back()));
    for(int i = 0; i < 10; i++)
        connect(numbers[i], SIGNAL(clicked()), this, SLOT(keyPressed()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        output();
        break;
    case Qt::Key_Plus:
        setPlus();
        break;
    case Qt::Key_Minus:
        setMin();
        break;
    case Qt::Key_multiply:
    case 42:
        setMult();
        break;
    case Qt::Key_division:
    case 47:
        setDiv();
        break;
    case Qt::Key_0:
        entry->insert("0");
        break;
    case Qt::Key_1:
        entry->insert("1");
        break;
    case Qt::Key_2:
        entry->insert("2");
        break;
    case Qt::Key_3:
        entry->insert("3");
        break;
    case Qt::Key_4:
        entry->insert("4");
        break;
    case Qt::Key_5:
        entry->insert("5");
        break;
    case Qt::Key_6:
        entry->insert("6");
        break;
    case Qt::Key_7:
        entry->insert("7");
        break;
    case Qt::Key_8:
        entry->insert("8");
        break;
    case Qt::Key_9:
        entry->insert("9");
        break;
    case Qt::Key_Period:
        entry->insert(".");
        break;
    case Qt::Key_Backspace:
//    case 16777219:
        back();
        break;
    case Qt::Key_Clear:
    case 16777216:
        clear();
        break;
    default:
        break;
    }

}

void MainWindow::setPlus()
{
    mode = '+';
    first = (entry->text()).toDouble();
    entry->setText("");
//    entry->setFocus();
}

void MainWindow::setMin()
{
    mode = '-';
    first = (entry->text()).toDouble();
    entry->setText("");
//    entry->setFocus();
}

void MainWindow::setMult()
{
    mode = '*';
    first = (entry->text()).toDouble();
    entry->setText("");
//    entry->setFocus();
}

void MainWindow::setDiv()
{
    mode = '/';
    first = (entry->text()).toDouble();
    entry->setText("");
//    entry->setFocus();
}

void MainWindow::setNeg()
{
    QString temp = entry->text();
    if(temp[0] == '-')
        temp.replace("-","");
    else
        temp.insert(0,'-');
    entry->setText(temp);
    //    entry->setFocus();
}

void MainWindow::clear()
{
    result = first = second = 0;
    entry->setText("");
}

void MainWindow::back()
{
    QString temp = entry->text();
    temp.chop(1);
    entry->setText(temp);
}

void MainWindow::output()
{
    second =  (entry->text()).toDouble();
    switch (mode) {
    case '+':
        result = first + second ;
        break;
    case '-':
        result = first - second ;
        break;
    case '*':
        result = first * second ;
        break;
    case '/':
        result = first / second ;
        break;
    }
    // init for next operation
    first = result;
    // display the result
    entry->setText(QString::number(result));
}

void MainWindow::keyPressed()
{
    // get the sender text & insert to entry
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    entry->insert(button->text());
//    entry->setFocus();
}
