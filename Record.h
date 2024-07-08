#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{
private:
    QString name;
    int score;

public:
    Record();
    Record(const QString& name, int score);

    QString get_name() const;
    int get_score() const;

    void set_name(const QString& name);
    void set_score(const int& score);
};

#endif // RECORD_H
