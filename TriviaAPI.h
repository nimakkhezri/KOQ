#ifndef TRIVIAAPI_H
#define TRIVIAAPI_H

#include <QString>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <QDebug>
#include "Category.h"
#include "Question.h"

class TriviaAPI
{
private:
    std::string base_url;
    QVector<Category> categories;

public:
    TriviaAPI();

    void download_categories();
    Category category_identifier(QString name);

    void get_questions(const Category& category,const QString& difficulty);
    void get_questions();
    void get_questions(const QString& difficulty);
};

#endif // TRIVIAAPI_H
