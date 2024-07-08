#include "PVPGame.h"

PVPGame::PVPGame() {
    this->currentRound = 1;
    this->currentTurn = 1;
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
    this->currentTurn = 1;
    this->set_currentPlayer();
}

void PVPGame::set_currentPlayer() {
    if (currentRound % 2 == 1){
        this->currentPlayer = &player1;
    } else {
        this->currentPlayer = &player2;
    }
}

void PVPGame::load_questions() {
    QVector<Question> questions;
    std::ifstream file("questions.json");

    if (file.is_open()){
        nlohmann::json data = nlohmann::json::parse(file);

        const auto& results = data["results"];
        for (const auto& result : results) {
            Question question;
            question.set_type(result["type"]);
            QString q_category = QString::fromStdString(result["category"]);
            Category category = this->api.category_identifier(q_category);
            question.set_category(category);
            question.set_difficulty(result["difficulty"]);
            question.set_question(result["question"]);
            question.set_correct_answer(result["correct_answer"]);

            QVector<QString> q_incorrect_answers;
            for (const auto& incorrect_answer : result["incorrect_answers"]){
                QString q_incorrect_answer = QString::fromStdString(incorrect_answer);
                q_incorrect_answers.push_back(q_incorrect_answer);
            }
            question.set_incorrect_answers(q_incorrect_answers);

            questions.push_back(question);
        }
        file.close();
    } else {
        qDebug() << "Can't read questions.json file ...";
    }

    this->currentQuestions = questions;
}

QVector<Question> PVPGame::get_currentQuestions() const {
    return currentQuestions;
}

void PVPGame::switch_players() {
    if (currentPlayer == &player1) {
        this->currentPlayer = &player2;
    } else if (currentPlayer == &player2) {
        this->currentPlayer = &player1;
    }
}

bool PVPGame::is_endRound() {
    if (currentTurn == 1){
        next_turn();
        return false;
    } else {
        next_round();
        return true;
    }
}

void PVPGame::next_turn() {
    this->currentTurn++;
    switch_players();
}

bool PVPGame::is_goldenRound() {
    if ((currentRound > 4) && (player1.get_score() == player2.get_score())) {
        return true;
    }
    else {
        return false;
    }
}

void PVPGame::turn_score_calculator(bool right_answer) {
    if (right_answer) {
        currentPlayer->turnScore_up();
    }
}

Player PVPGame::get_round_winner() {
    if (player1.get_turnScore() > player2.get_turnScore()) {
        player1.score_up();
        player1.set_turnScore(0);
        player2.set_turnScore(0);
        return player1;
    } else if (player1.get_turnScore() < player2.get_turnScore()){
        player2.score_up();
        player1.set_turnScore(0);
        player2.set_turnScore(0);
        return player2;
    }
    else {
        player1.score_up();
        player2.score_up();
        player1.set_turnScore(0);
        player2.set_turnScore(0);
        return Player("Both");
    }
}

Player PVPGame::get_game_winner() {
    if (player1.get_score() > player2.get_score()) {
        return player1;
    }
    else {
        return player2;
    }
}

Player PVPGame::get_player1() const {
    return player1;
}

Player PVPGame::get_player2() const {
    return player2;
}

bool PVPGame::is_endGame() {
    if (currentRound > 4 && !is_goldenRound()) {
        return true;
    }
    else {
        return false;
    }
}
