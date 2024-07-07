#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QVector>
#include <QMap>

class Category
{
private:
    QString name;
    int id;

public:
    Category();
    Category(QString name, int id);

    QString get_name() const;
    int get_id() const;

};

#endif // CATEGORY_H
