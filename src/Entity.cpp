/*
*   Farbod Shahinfar 
*   This code is for pedagogical purposes
*/


#include "Entity.hpp"
#include <stdexcept>

// statics

default_random_engine Entity::generator;
uniform_int_distribution<int> Entity::distribution(0, COUNT_ROW-1);

/*
* This function generates a new Entity object
*/
Entity* Entity::generate_random_entity() {
    Entity *entity = new Entity();
    for (int col = 0; col < COUNT_COLUMN; col++) {
        int row =  distribution(generator);
        entity->set_column_row(col, row);
    }
    return entity;
}


// non-statics

Entity::Entity() {
    data = new int[COUNT_COLUMN];
    for (int col = 0; col < COUNT_COLUMN; col++)
        data[col] = 0;
}

void Entity::set_column_row(int col, int row) {
    if (col >= COUNT_COLUMN || col < 0) {
        throw invalid_argument("col argumnet out of range!");
    }
    if (row >= COUNT_COLUMN || row < 0) {
        throw invalid_argument("row argument out of range!");
    }
    data[col] = row;
}

int Entity::get_column(int col) {
    return data[col];
}

string Entity::to_string() {
    string repr = "[";
    for (int col = 0; col < COUNT_COLUMN; col++) {
        if (col == 0) {
            repr += std::to_string(data[col]);
        } else {
            repr += ", " + std::to_string(data[col]);
        }
    }
    repr += "]";
    return repr;
}
