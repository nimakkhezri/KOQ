#ifndef SURVIVALGAME_H
#define SURVIVALGAME_H

#include "TriviaAPI.h"
#include <nlohmann/json.hpp>

class SurvivalGame
{
private:
    int easy, medium, hard, health, score;
public:
    TriviaAPI api;
    SurvivalGame();

    void load_records();
    void save_records();

    void set_easy_record(const int& record);
    void set_medium_record(const int& record);
    void set_hard_record(const int& record);

    int get_easy_record() const;
    int get_medium_record() const;
    int get_hard_record() const;

    void check_answer(bool check);
    bool is_endGame();
};

#endif // SURVIVALGAME_H
