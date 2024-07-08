#include "SurvivalGame.h"

SurvivalGame::SurvivalGame() {
    this->easy = Record("easy", 0);
    this->medium = Record("medium", 0);
    this->hard = Record("hard", 0);
    this->health = 3;
    this->roundScore = 0;
    this->currentRecord = nullptr;
    load_records();
}

void SurvivalGame::load_records() {
    std::ifstream file("database.json");
    if (file.is_open()) {
        nlohmann::json data = nlohmann::json::parse(file);
        this->easy.set_score(data["easy"]);
        this->medium.set_score(data["medium"]);
        this->hard.set_score(data["hard"]);
        file.close();
    } else {
        save_records();
    }
}

void SurvivalGame::save_records() {
    nlohmann::json data;
    data["easy"] = this->easy.get_score();
    data["medium"] = this->medium.get_score();
    data["hard"] = this->hard.get_score();
    std::ofstream file("database.json");
    if (file.is_open()) {
        file << data.dump(4);
        file.close();
    } else {
        qDebug() << "database.json can't be saved ...";
    }
}

Record SurvivalGame::get_easy_record() const {
    return easy;
}

Record SurvivalGame::get_medium_record() const {
    return medium;
}

Record SurvivalGame::get_hard_record() const {
    return hard;
}

void SurvivalGame::set_easy_record(const int& record) {
    this->easy.set_score(record);
}

void SurvivalGame::set_medium_record(const int& record) {
    this->medium.set_score(record);
}

void SurvivalGame::set_hard_record(const int& record) {
    this->hard.set_score(record);
}

void SurvivalGame::check_answer(bool check) {
    if (check) {
        this->roundScore++;
    } else {
        this->health--;
    }
}

bool SurvivalGame::is_endGame() {
    if (this->health == 0) {
        return true;
    }
    return false;
}

void SurvivalGame::set_currentRecord(const QString& mode) {
    if (mode == "easy") {
        this->currentRecord = &easy;
    } else if (mode == "medium") {
        this->currentRecord = &medium;
    } else if (mode == "hard") {
        this->currentRecord = &hard;
    }
}

Record* SurvivalGame::get_currentRecord() {
    return currentRecord;
}

int SurvivalGame::get_roundScore() const {
    return roundScore;
}

QVector<Question> SurvivalGame::get_questions() const {
    return questions;
}

bool SurvivalGame::is_newRecord() {
    if (roundScore > currentRecord->get_score()) {
        currentRecord->set_score(roundScore);
        return true;
    }
    else {
        return false;
    }
}

void SurvivalGame::reset() {
    this->roundScore = 0;
    this->health = 3;
}

void SurvivalGame::load_questions() {
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

    this->questions = questions;
}

int SurvivalGame::get_health() const {
    return health;
}
