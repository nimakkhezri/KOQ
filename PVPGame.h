#ifndef PVPGAME_H
#define PVPGAME_H

#include <QVector>
#include <QString>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TriviaAPI.h"
#include "Question.h"
#include "Player.h"

class PVPGame
{
private:
    Player player1, player2;
    Player* currentPlayer;
    int currentRound;
    int currentTurn;
    QVector<Question> currentQuestions;

public:
    PVPGame();

    TriviaAPI api;
    void load_questions();
    Player* get_currentPlayer();
    void set_players(const Player& player1, const Player& player2);
    void set_currentPlayer();
    void next_round();
    void switch_players();
    bool is_endRound();
    void next_turn();
    bool is_goldenRound();
    void turn_score_calculator(bool right_answer);
    Player get_round_winner();
    Player get_game_winner();
    QVector<Question> get_currentQuestions() const;
    bool is_endGame();
    void reset();

    Player get_player1() const;
    Player get_player2() const;
};

#endif // PVPGAME_H
