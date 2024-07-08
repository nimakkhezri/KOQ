#include "Question.h"
#include <QDebug>

Question::Question() {}

Question::Question(QString type, QString difficulty, QString question, QString correct_answer, const Category& category, QVector<QString> incorrect_answers){
    this->type = type;
    this->category = category;
    this->difficulty = difficulty;
    this->question = question;
    this->correct_answer = correct_answer;
    this->incorrect_answers = incorrect_answers;
}

QString Question::get_type() const{
    return type;
}

Category Question::get_category() const{
    return category;
}

QString Question::get_difficulty() const{
    return difficulty;
}

QString Question::get_question() const{
    return question;
}

QString Question::get_correct_answer() const{
    return correct_answer;
}

QVector<QString> Question::get_incorrect_answers() const{
    return incorrect_answers;
}

void Question::set_type(const std::string& type){
    QString q_type = QString::fromStdString(type);
    this->type = q_type;
}

void Question::set_category(const Category& category){
    this->category = category;
}

void Question::set_difficulty(const std::string& difficulty){
    QString q_difficulty = QString::fromStdString(difficulty);
    this->difficulty = q_difficulty;
}

void Question::set_question(const std::string& question){
    QString q_question = QString::fromStdString(question);
    this->question = q_question;
}

void Question::set_correct_answer(const std::string& correct_answer){
    QString q_correct_answer = QString::fromStdString(correct_answer);
    this->correct_answer = q_correct_answer;
}

void Question::set_type(const QString& type){
    this->type = type;
}

void Question::set_difficulty(const QString& difficulty){
    this->difficulty = difficulty;
}

void Question::set_question(const QString& question){
    this->question = question;
}

void Question::set_correct_answer(const QString& correct_answer){
    this->correct_answer = correct_answer;
}

void Question::set_incorrect_answers(const QVector<QString>& incorrect_answers){
    this->incorrect_answers = incorrect_answers;
}

QVector<QString> Question::get_random_answers() const {
    QVector<QString> random_options;
    random_options.push_back(correct_answer);
    for(const QString& incorrect_answer : incorrect_answers){
        random_options.push_back(incorrect_answer);
    }
    std::random_shuffle(random_options.begin(), random_options.end());
    return random_options;
}
