/*
*   Farbod Shahinfar 
*   This code is for pedagogical purposes
* ===========================================
*   
*   This file contains genetic algorithm procedures
*   for solving eight-queens problem
*/


#include <iostream>
#include "Entity.hpp"
using namespace std;



/*
*   calculates a fittness value between 1 and 0
*   0 is the best fit, meaning no threats.
*/
float  fittness_function(Entity &e) {
    int threats = 0;
    // total possible threats = C(2, 8) = 28
    // this value is for 8 queens
    const int total_posible_threats = 28;
    for (int col = 0; col < Entity::COUNT_COLUMN; col++) {
        int col_val = e.get_column(col);
        for (int ptr = col + 1; ptr < Entity::COUNT_COLUMN; ptr++) {
            int ptr_val = e.get_column(ptr);
            if (col_val == ptr_val) {
                // in same row
                threats++;
            } else if (ptr - col == ptr_val - col_val) {
                // diagonal  `/`
                threats++;
            } else if (ptr - col == col_val - ptr_val) {
                // diagonal `\`
                threats++;
            }
        }
    }
    return threats / (float)total_posible_threats;
}


int main(int argc, char* argv[]) {
    // Generate the first population
    const int population_size = 50;
    Entity population[population_size];
    Entity* e;
    for (int i = 0; i < 10; i++) {
        e = Entity::generate_random_entity();
        population[i] = *e;
    }
    
    // Continue for some generations
    const int count_generations = 100;
    for (int generation = 0; generation < count_generations; generation++) {
        //...        
    }
    cout << "Hello\n";
    
    
    return 0;
}