#include "guesser.h"

guesser::guesser(QObject *parent) : QObject(parent)
{
    mode = 0;
    cur_guess = "";
    bn = "0";
    cn = "0";
}

void guesser::start()
{
    emit visibility(1);
    pos_ans.clear();
    for (int i = 1; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (j != i)
            {
                for (int k = 0; k < 10; ++k)
                {
                    if (k != j && k != i)
                    {
                        for (int g = 0; g < 10; ++g)
                        {
                            if (g != k && g != j && g != i)
                            {
                                pos_ans.insert(QString::number(i * 1000 + j * 100 + k * 10 + g));
                            }
                        }
                    }
                }
            }
        }
    }
    make_a_guess();
}

void guesser::make_a_guess()
{
    if (pos_ans.size() == 0)
    {
        cur_guess = "Impossible";
        end();
        return;
    }
    if (pos_ans.size() == 1)
    {
        end();
        return;
    }
    cur_guess = *pos_ans.begin();
    emit send_text(QString("What about ") + cur_guess + QString("? (Please type correctly)"));
}

void guesser::value_changed_b(QString s)
{
    bn = s;
}

void guesser::value_changed_c(QString s)
{
    cn = s;
}

std::pair<int, int> guesser::count(QString a, QString b)
{
    int bulls = 0, cows = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (a[i] == b[j])
            {
                if (i == j)
                    ++bulls;
                else
                    ++cows;
            }
    return std::make_pair(bulls, cows);
}

void guesser::checker()
{
    bool ok;
    int b_val = bn.toInt(&ok);
    if (!ok || b_val < 0 || b_val > 4)
    {
        emit send_text(QString("What about ") + cur_guess + QString("? (PLEASE TYPE CORRECTLY)"));
        return;
    }
    int c_val = cn.toInt(&ok);
    if (!ok || c_val < 0 || c_val > 4)
    {
        emit send_text(QString("What about ") + cur_guess + QString("? (PLEASE TYPE CORRECTLY)"));
        return;
    }
    std::pair<int, int> true_ans = std::make_pair(b_val, c_val);
    std::set<QString> new_pos_ans;
    for (QString s : pos_ans)
    {
        if (count(s, cur_guess) == true_ans)
            new_pos_ans.insert(s);
    }
    pos_ans = new_pos_ans;
    make_a_guess();
}

void guesser::end()
{
    mode = 2;
    emit visibility(0);
    if (cur_guess != QString("Impossible"))
        emit send_text(QString("Your number was ") + *pos_ans.begin() + QString("! If not it's totally your fault :) New game?"));
    else
        emit send_text(QString("Your answers were contradictory - there are no variants. New game?"));
}

void guesser::ok()
{
    if (mode == 0)
    {
        start();
        mode = 1;
    }
    else if (mode == 1)
    {
        checker();
    }
    else if (mode == 2)
    {
        emit send_text("Choose a number. Are you ready?");
        mode = 0;
    }
}
