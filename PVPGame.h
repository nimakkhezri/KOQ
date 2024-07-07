#ifndef PVPGAME_H
#define PVPGAME_H

#include <QVector>
#include <QString>
#include "Question.h"
#include "Player.h"

class PVPGame
{
private:
    Player player1, player2;
    Player* currentPlayer;
    int currentRound;
    QVector<Question> currentQuestions;

public:
    PVPGame();

    void load_questions();
    Player* get_currentPlayer();
    void set_players(const Player& player1, const Player& player2);
    void set_currentPlayer();
    void next_round();
};

#endif // PVPGAME_H
