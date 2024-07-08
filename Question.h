#ifndef QUESTION_H
#define QUESTION_H

#include <QtAlgorithms>>
#include <QString>
#include <QVector>
#include "Category.h"

class Question
{
private:
    QString type, difficulty, question, correct_answer;
    QVector<QString> incorrect_answers, random_answers;
    Category category;

public:
    Question();
    Question(QString type, QString difficulty, QString question, QString correct_answer, const Category& category, QVector<QString> incorrect_answers);

    void random_answers_gen();
    QVector<QString> get_random_answers() const;
    QString get_type() const;
    Category get_category() const;
    QString get_difficulty() const;
    QString get_question() const;
    QString get_correct_answer() const;
    QVector<QString> get_incorrect_answers() const;

    void set_type(const std::string& type);
    void set_category(const Category& category);
    void set_difficulty(const std::string& difficulty);
    void set_question(const std::string& question);
    void set_correct_answer(const std::string& correct_answer);

    void set_type(const QString& type);
    void set_difficulty(const QString& difficulty);
    void set_question(const QString& question);
    void set_correct_answer(const QString& correct_answer);

    void set_incorrect_answers(const QVector<QString>& incorrect_answers);
};

#endif // QUESTION_H
