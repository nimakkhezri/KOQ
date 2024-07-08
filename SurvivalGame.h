#ifndef SURVIVALGAME_H
#define SURVIVALGAME_H

#include "TriviaAPI.h"
#include "Record.h"
#include <nlohmann/json.hpp>

class SurvivalGame
{
private:
    Record easy, medium, hard;
    Record *currentRecord;
    int health, roundScore;
    QVector<Question> questions;
public:
    TriviaAPI api;
    SurvivalGame();
    void set_currentRecord(const QString& mode);
    Record* get_currentRecord();

    int get_roundScore() const;
    int get_health() const;

    void load_records();
    void save_records();

    void set_easy_record(const int& record);
    void set_medium_record(const int& record);
    void set_hard_record(const int& record);

    Record get_easy_record() const;
    Record get_medium_record() const;
    Record get_hard_record() const;

    QVector<Question> get_questions() const;

    void load_questions();

    void check_answer(bool check);
    bool is_endGame();
    bool is_newRecord();
    void reset();
};

#endif // SURVIVALGAME_H
