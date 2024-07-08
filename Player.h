#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString name;
    int score;
    int turnScore;

public:
    Player();
    Player(const QString& name);

    QString get_name() const;
    int get_score() const;
    int get_turnScore() const;

    void set_name(const QString& name);
    void set_score(const int& score);
    void set_turnScore(const int& score);
    void score_up();
    void turnScore_up();
};

#endif // PLAYER_H
