#include "Player.h"

Player::Player() {
    this->score = 0;
}

Player::Player(const QString& name) {
    this->name = name;
    this->score = 0;
}

QString Player::get_name() const {
    return name;
}

int Player::get_score() const {
    return score;
}

void Player::set_name(const QString& name) {
    this->name = name;
}

void Player::set_score(const int& score) {
    this->score = score;
}

void Player::score_up() {
    this->score++;
}
