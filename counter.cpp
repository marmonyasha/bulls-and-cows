#include "counter.h"
#include <iostream>
#include <QInputDialog>
#include <QVector>
#include <QtAlgorithms>
#include <fstream>
#include <QMessageBox>
#include <random>
#include <ctime>

using namespace std;

int rand_num()
{
    int a = 0;
    QString s;
    bool ok = false;
    while (a < 1000 || !ok) {
        ok = true;
        a = rand() % 10000;
        s = QString::number(a);
        int i = 0;
        int j = 1;
        while (i < s.size() && ok) {
            while (j < s.size() && s[i] != s[j])
                ++j;
            if (j < s.size())
                ok = false;
            ++i;
            j = i + 1;
        }
        }
    return a;
}

Counter::Counter(QObject *parent) : QObject(parent)
{
    srand(time(NULL));
    ans = rand_num();
    tries = 0;
    m_str = "";
    last_try = "";
    win = false;
    std::ifstream fin("input.txt");
    if (fin) {
        std::string stringg;
        int iiiint;
        while (fin >> iiiint >> stringg)
        {
            vec.push_back(qMakePair(iiiint, QString::fromStdString(stringg)));
        }
    }
}

void Counter::UpdateValue(QString val)
{
    m_str = val;
}

void Counter::Check()
{
    int i = 0;
    int j = 1;
    bool ok = true;
    int val = m_str.toInt(&ok);
    if (val > 9999 || val < 1000)
        ok = false;
    if (ok) {
        m_str = QString::number(val);
        while (i < m_str.size() && ok) {
            while (j < m_str.size() && m_str[i] != m_str[j])
                ++j;
            if (j < m_str.size())
                ok = false;
            ++i;
            j = i + 1;
        }
    }
    if (ok) {
        if (last_try != m_str)
            ++tries;
        last_try = m_str;
        emit correct("Let me check...");
    }
    else
        emit incorrect("Number is incorrect. Try again.");
}

void Counter::result()
{
    int bulls = 0;
    int cows = 0;
    QString anss;
    anss = QString::number(ans);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (anss[i] == m_str[j]) {
                if (i == j)
                    ++bulls;
                else
                    ++cows; }
    if (bulls == 4) {
        emit won("Congratulations! You are right!");
        emit won2("Number of attempts:");
        emit won3("New game");
        emit wonnum(tries);
        win = true; }
    else {
        emit not_won("Oops! Seems like you're close, but still not perfect.");
        emit bulls_num(bulls);
        emit bntxt ("The number of bulls:");
        emit cntxt ("The number of cows:");
        emit cows_num(cows); }
}

void Counter::new_game()
{
    QString anss;
    anss = QString::number(ans);
    if (win)
        emit newgame("Let's play once again.");
    else
        emit newgame("Let's play once again. The answer was: "+ anss);
    win = false;
    ans = rand_num();
    cout << ans << endl;
    tries = 0;
    last_try = "";
    emit newgame2("I chose new number. Make your guess.");
    emit newgame3(" I give up");
}

void Counter::click()
{
    if (!win)
        emit bu_clicked();
}

void Counter::results() {
    QMessageBox mess;
    QString line;
    for (int i = 0; i < vec.size(); ++i)
        line += QString::number(i + 1) + QString(") ") + vec[i].second + QString(" - ") + QString::number(vec[i].first) + QString("\n");
    mess.setText(line);
    mess.setWindowTitle("Results");
    mess.exec();
}

void Counter::compare()
{
    if (vec.size() < 5 || tries < vec[4].first)
    {        bool ok;
            QString text = QInputDialog::getText(NULL, "Winner!",
                                                 "Type your name (without spaces):", QLineEdit::Normal,
                                                 "", &ok);
        if (!ok || text.isEmpty())
            text = "No_name";
        if (vec.size() < 5)
            vec.push_back(qMakePair(tries, text));
        else
            vec[4] = qMakePair(tries, text);
        qSort(vec.begin(), vec.end());
        std::ofstream fout("input.txt");
        for (auto a : vec) {
            fout << a.first << ' ' << a.second.toStdString() << std::endl;
        }
    }
}
