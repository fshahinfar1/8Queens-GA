/*
*   Farbod Shahinfar 
*   This code is for pedagogical purposes
* ===========================================
*   
*   This file contains genetic algorithm procedures
*   for solving eight-queens problem
*/


#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "Entity.hpp"
using namespace std;


/*
*   calculates a fittness value between 1 and 0
*   1 is the best fit, meaning no threats.
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
    return 1 - (threats / (float)total_posible_threats);
}


/*
*   This function selects parents for generating the
*   next population.
*   
*   Returns an array of Entity with the same size given
*   to the function.
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


/*
*   Applies cross over operation on the population.
*   Each entity in even position will be cross overed
*   with next entity.
*   There is one cross over point.
*
*   Returns an array with length = size / 2
*/
Entity* cross_over(Entity* population, const int size) {
    if (size % 2 != 0)
        throw invalid_argument("population size is not even number!");
    Entity* result = new Entity[size / 2];
    int pop_index = 0;
    for (int i = 0; i < size; i += 2) {
        Entity* xover = new Entity();
        int xover_pnt = rand() % Entity::COUNT_COLUMN;
        for (int j = 0; j < Entity::COUNT_COLUMN; j++) {
            int val;
            if (j <= xover_pnt) {
                val = population[i].get_column(j);
            } else {
                val = population[i + 1].get_column(j);
            }
            xover->set_column_row(j, val);
        }
        result[pop_index++] = *xover;
    }
    return result;
}


Entity* generate_random_population(int size) {
    Entity* population =new Entity[size];
    Entity* e;
    for (int i = 0; i < size; i++) {
        e = Entity::generate_random_entity();
        population[i] = *e;
    }
    return population;
}


Entity* concat_population(Entity* p1, int size1, Entity* p2, int size2) {
    Entity* res = new Entity[size1 + size2];
    for (int i = 0; i < size1; i++) {
        res[i] = p1[i];
    }
    for (int i = 0; i < size2; i++) {
        res[size1 + i] = p2[i];
    }
    return res;
}


void show_population(Entity* population, const int size) {
    for (int i = 0; i < size; i++) {
        cout << population[i].to_string() << endl;
    }
    cout << "++++++++++++++" << endl;
}

int main(int argc, char* argv[]) {
    // Generate the first population
    const int population_size = 100;
    Entity* population = generate_random_population(population_size);
    // show_population(population, population_size);
    // Continue for some generations
    const int count_generations = 2000;
    for (int generation = 0; generation < count_generations; generation++) {
        Entity* selected = select_from_population(population, population_size);
        Entity* new_population = generate_random_population(population_size);
        Entity* overal_selected = concat_population(selected, population_size, new_population, population_size);
        delete selected;  // only remove pointer
        delete new_population; // only remove pointer
        Entity* xover_population = cross_over(overal_selected, 2 * population_size);
        delete[] overal_selected; // free memory allocated for all previous population
        population = xover_population; // no mutation yet
        // mutate population
        // find the best fittness value of population
        float best_f = fittness_function(population[0]);
        int best_index = 0;
        for (int i = 1; i < population_size; i++) {
            float f = fittness_function(population[i]);
            if (f > best_f) {
                best_f = f;
                best_index = i;
            }
        }
        cout << "gen: " << generation <<
        " best fittness: " << best_f <<
        " index: " << best_index << endl;
        if (best_f == 1) {
            Entity answer = population[best_index];
            cout << "Answer: \n" << answer.to_string() << endl;
            break;
        }
    }
    return 0;
}