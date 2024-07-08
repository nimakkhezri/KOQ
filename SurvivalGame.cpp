#include "SurvivalGame.h"

SurvivalGame::SurvivalGame() {
    this->easy = 0;
    this->medium = 0;
    this->hard = 0;
    this->health = 3;
    this->score = 0;
    load_records();
}

void SurvivalGame::load_records() {
    std::ifstream file("database.json");
    if (file.is_open()) {
        nlohmann::json data = nlohmann::json::parse(file);
        this->easy = data["easy"];
        this->medium = data["medium"];
        this->hard = data["hard"];
        file.close();
    } else {
        save_records();
    }
}

void SurvivalGame::save_records() {
    nlohmann::json data;
    data["easy"] = this->easy;
    data["medium"] = this->medium;
    data["hard"] = this->hard;
    std::ofstream file("database.json");
    if (file.is_open()) {
        file << data.dump(4);
        file.close();
    } else {
        qDebug() << "database.json can't be saved ...";
    }
}

int SurvivalGame::get_easy_record() const {
    return easy;
}

int SurvivalGame::get_medium_record() const {
    return medium;
}

int SurvivalGame::get_hard_record() const {
    return hard;
}

void SurvivalGame::set_easy_record(const int& record) {
    this->easy = record;
}

void SurvivalGame::set_medium_record(const int& record) {
    this->medium = record;
}

void SurvivalGame::set_hard_record(const int& record) {
    this->hard = record;
}

void SurvivalGame::check_answer(bool check) {
    if (check) {
        this->score++;
    } else {
        this->health--;
    }
}
