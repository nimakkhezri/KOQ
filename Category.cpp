#include "Category.h"

Category::Category() {}

Category::Category(QString name, int id){
    this->name = name;
    this->id = id;
}

QString Category::get_name() const{
    return name;
}

int Category::get_id() const{
    return id;
}
