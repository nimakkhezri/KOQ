#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString name;
    int score;

public:
    Player();
    Player(const QString& name);

    QString get_name() const;
    int get_score() const;

    void set_name(const QString& name);
    void set_score(const int& score);
    void score_up();
};

#endif // PLAYER_H
