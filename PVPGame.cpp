#include "PVPGame.h"

PVPGame::PVPGame() {
    this->currentRound = 1;
    this->set_currentPlayer();
}

void PVPGame::set_players(const Player& player1, const Player& player2){
    this->player1 = player1;
    this->player2 = player2;
}

Player* PVPGame::get_currentPlayer() {
    return currentPlayer;
}

void PVPGame::next_round() {
    this->currentRound++;
    this->set_currentPlayer();
}

void PVPGame::set_currentPlayer() {
    if (currentRound % 2 == 1){
        this->currentPlayer = &player1;
    } else {
        this->currentPlayer = &player2;
    }
}
