/*
*   Farbod Shahinfar 
*   This code is for pedagogical purposes
*/


#include <random>
#include <string>
using namespace std;


class Entity {
private:
// statics
static default_random_engine generator;
static uniform_int_distribution<int> distribution;
const static int COUNT_COLUMN = 8;
const static int COUNT_ROW = 8;
// non-statics
int * data;
public:
//statics
    static Entity* generate_random_entity();
// non-statics
    Entity();
    void set_column_row(int col, int row);
    int get_column(int col);
    string to_string();
};