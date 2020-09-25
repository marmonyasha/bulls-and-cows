#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QVector>

class Counter : public QObject
{
    Q_OBJECT
private:
    int tries;
    QString m_str;
    QString last_try;
    bool win;
    QVector <QPair<int, QString>> vec;
public:
    int ans;
    explicit Counter(QObject *parent = 0);


signals:
    void correct(QString);
    void incorrect(QString);
    void won(QString);
    void won2(QString);
    void won3(QString);
    void wonnum(int);
    void not_won(QString);
    void bulls_num(int);
    void cows_num(int);
    void bntxt (QString);
    void cntxt (QString);
    void newgame(QString);
    void newgame2(QString);
    void newgame3(QString);
    void bu_clicked();
    void askname();
    void update_text(const QString s);
public slots:
    void UpdateValue(QString);
    void Check();
    void result();
    void new_game();
    void click();
    void compare();
    void results();
};

#endif // COUNTER_H
