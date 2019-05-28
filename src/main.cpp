/*
*   Farbod Shahinfar 
*   This code is for pedagogical purposes
* ===========================================
*   
*   This file contains genetic algorithm procedures
*   for solving eight-queens problem
*/


#include <iostream>
#include <cstdlib>
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


/*
*   This function selects parents for generating the
*   next population.
*/
Entity* select_from_population(Entity* population, const int size) {
    float comulative_f[size];
    float normal_f;
    float comulative = 0;
    float total_f = 0;
    // calculate sum of f value for normalization
    for (int i = 0; i < size; i++)
        total_f += fittness_function(population[i]);
    // generate the commulative value
    for (int i = 0; i < size; i++) {
        normal_f = fittness_function(population[i]) / total_f;
        comulative += normal_f;
        comulative_f[i] = comulative;
    }
    // select parents randomly with
    // respect to fittness
    Entity* selected = new Entity[size];
    double max_rnd = (double)(RAND_MAX) + 1;
    for (int i = 0; i < size; i++) {
        double rnd = rand() / max_rnd;
        int ptr = 0;
        while (ptr < size - 1) {
            if (comulative_f[ptr] >= rnd)
                break;
            ptr++;
        }
        selected[i] = population[ptr];
    }
    return selected;
}

int main(int argc, char* argv[]) {
    // Generate the first population
    const int population_size = 10;
    Entity population[population_size];
    Entity* e;
    for (int i = 0; i < population_size; i++) {
        e = Entity::generate_random_entity();
        population[i] = *e;
        // cout << e->to_string() << endl;
    }
    // cout << "++++++++++++++" << endl;
    // Continue for some generations
    const int count_generations = 1;
    Entity* selected;
    for (int generation = 0; generation < count_generations; generation++) {
        selected = select_from_population(population, population_size);
        
    }
    
    return 0;
}