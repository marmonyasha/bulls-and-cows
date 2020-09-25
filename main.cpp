#include <QMainWindow>
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include "counter.h"
#include <QPushButton>
#include <ctime>
#include <iostream>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QVector>
#include <QPair>
#include <QInputDialog>
#include <QStringList>
#include "guesser.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;

void i_guess() {
    QMainWindow * w = new QMainWindow;
    Counter * mycounter = new Counter();
    w->setGeometry(700, 400, 500, 200);
    std::cout << mycounter->ans << std::endl;
    QLineEdit *le = new QLineEdit(w);
    QPushButton *bu = new QPushButton("Submit!", w);
    bu->setGeometry(370, 10, 120, 40);
    QPushButton *bu2 = new QPushButton(w);
    bu2->setGeometry(370, 60, 120, 40);
    QLabel *lonb = new QLabel(" I give up", bu2);
    lonb->setGeometry(25, 0, 120, 40);
    le->setGeometry(10, 10, 350, 40);
    QLabel *l = new QLabel("I know you want to play with me...", w);
    QLabel *l2 = new QLabel("I chose a number. Make your guess.", w);
    l->setGeometry(10, 60, 360, 20);
    l2->setGeometry(10, 90, 360, 20);
    QLabel *b = new QLabel(w);
    QLabel *bn = new QLabel(w);
    QLabel *c = new QLabel(w);
    QLabel *cn = new QLabel(w);
    b->setGeometry(10, 120, 150, 20);
    c->setGeometry(10, 150, 150, 20);
    bn->setGeometry(170, 120, 100, 20);
    cn->setGeometry(170, 150, 100, 20);
    QPushButton *bu3 = new QPushButton("Results", w);
    bu3->setGeometry(370, 110, 120, 40);


    QMessageBox *mess = new QMessageBox;
    mess->setGeometry(850, 450, 500, 200);

    QObject::connect(le, SIGNAL(textChanged(QString)),
                         mycounter, SLOT(UpdateValue(QString)));
    QObject::connect(bu, SIGNAL(clicked()),
                         mycounter, SLOT(click()));
    QObject::connect(mycounter, SIGNAL(bu_clicked()),
                         mycounter, SLOT(Check()));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         l, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         l2, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(correct(QString)),
                         l, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(correct(QString)),
                         mycounter, SLOT(result()));
    QObject::connect(mycounter, SIGNAL(won(QString)),
                         l2, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(won3(QString)),
                         lonb, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(won2(QString)),
                         b, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(wonnum(int)),
                         bn, SLOT(setNum(int)));
    QObject::connect(mycounter, SIGNAL(won(QString)),
                         c, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(won(QString)),
                         cn, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(not_won(QString)),
                         l2, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(bntxt(QString)),
                         b, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(cntxt(QString)),
                         c, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(bulls_num(int)),
                         bn, SLOT(setNum(int)));
    QObject::connect(mycounter, SIGNAL(cows_num(int)),
                         cn, SLOT(setNum(int)));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         b, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         c, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         bn, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(incorrect(QString)),
                         cn, SLOT(clear()));
    QObject::connect(bu2, SIGNAL(clicked()),
                         mycounter, SLOT(new_game()));
    QObject::connect(mycounter, SIGNAL(newgame(QString)),
                         l, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(newgame2(QString)),
                         l2, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(newgame(QString)),
                         b, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(newgame(QString)),
                         bn, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(newgame3(QString)),
                         lonb, SLOT(setText(QString)));
    QObject::connect(mycounter, SIGNAL(newgame(QString)),
                         c, SLOT(clear()));
    QObject::connect(mycounter, SIGNAL(newgame(QString)),
                         cn, SLOT(clear()));
    QObject::connect(bu3, SIGNAL(clicked()),
                         mycounter, SLOT(results()));



    QObject::connect(mycounter, SIGNAL(wonnum(int)),
                         mycounter, SLOT(compare()));
    w->show();
}

void i_choose() {
    QMainWindow * w = new QMainWindow;
    guesser * myguesser = new guesser();
    QLabel * l1 = new QLabel("Number of bulls:");
    QLabel * l2 = new QLabel("Number of cows:");
    QLineEdit * le1 = new QLineEdit;
    QLineEdit * le2 = new QLineEdit;
    QHBoxLayout * hbox = new QHBoxLayout;
    le1->setText("0");
    le2->setText("0");
    l1->setVisible(0);
    le1->setVisible(0);
    l2->setVisible(0);
    le2->setVisible(0);
    hbox->addWidget(l1);
    hbox->addWidget(le1, 5);
    hbox->addStretch(1);
    hbox->addWidget(l2);
    hbox->addWidget(le2, 5);
    QLabel * lalala = new QLabel("Choose a number. Are you ready?");
    lalala->setAlignment(Qt::AlignCenter);
    QPushButton * bu = new QPushButton("OK");
    QVBoxLayout * vbox = new QVBoxLayout;
    vbox->addWidget(lalala);
    vbox->addLayout(hbox);
    vbox->addWidget(bu);
    QWidget * wiwiwi = new QWidget;
    wiwiwi->setLayout(vbox);
    w->setCentralWidget(wiwiwi);

    QObject::connect(myguesser, SIGNAL(send_text(QString)),
                         lalala, SLOT(setText(QString)));
    QObject::connect(le1, SIGNAL(textChanged(QString)),
                         myguesser, SLOT(value_changed_b(QString)));
    QObject::connect(le2, SIGNAL(textChanged(QString)),
                         myguesser, SLOT(value_changed_c(QString)));
    QObject::connect(bu, SIGNAL(clicked()),
                         myguesser, SLOT(ok()));
    QObject::connect(myguesser, &guesser::visibility, [=](int x) {
        l1->setVisible(x);
        le1->setVisible(x);
        l2->setVisible(x);
        le2->setVisible(x);
    });
    w->setGeometry(700, 400, 500, 200);
    w->show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString s = QInputDialog::getItem(0, "Game mode", "Do you want to choose a number or to guess it?",
                                      QStringList({QString("Choose"), QString("Guess")}));
    if (s == "Guess") {
        i_guess();
    } else {
        i_choose();
    }
    return a.exec();
}
