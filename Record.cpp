#include "Record.h"

Record::Record() {
    this->score = 0;
}

Record::Record(const QString& name, int score) {
    this->name = name;
    this->score = score;
}

void Record::set_name(const QString& name) {
    this->name = name;
}

void Record::set_score(const int& score) {
    this->score = score;
}

QString Record::get_name() const {
    return name;
}

int Record::get_score() const {
    return score;
}
