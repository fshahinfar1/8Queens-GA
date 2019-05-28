#include <iostream>
#include "Entity.hpp"
using namespace std;


int main(int argc, char* argv[]) {
    cout << "Hello\n";
    Entity* e;
    for (int i = 0; i < 10; i++) {
        e = Entity::generate_random_entity();
        cout << e->to_string() << endl;
    }
    return 0;
}