#ifndef GUESSER_H
#define GUESSER_H

#include <QObject>
#include <set>

class guesser : public QObject
{
    Q_OBJECT
public:
    int mode;
    QString cur_guess;
    explicit guesser(QObject *parent = 0);
    std::set<QString> pos_ans;
    std::pair<int, int> count(QString a, QString b);
    QString bn, cn;
    void start();
    void make_a_guess();
    void end();
    void checker();

signals:
    void send_text(QString);
    void visibility(int);

public slots:
    void ok();
    void value_changed_b(QString s);
    void value_changed_c(QString s);

};

#endif // guesser_H
