#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "TriviaAPI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    TriviaAPI api;

    Category category = api.category_identifier("History");

    api.get_questions(category, "easy");
    w.show();
    return a.exec();
}
