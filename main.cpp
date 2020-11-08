using namespace std;

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "main.h"
#include "field.cpp"
#include "robot.cpp"

int main()
{
	Field* field = new Field();
	vector<Robot> robots;
    int gen = 1;
    int frame = 1;
	for (int i = 0; i < n; i++) {
		robots.push_back(Robot(field));
	}
	while (true) {
        for (int i = 0; i < 10000000; i++) ;
		system("cls");
        cout << "Generation " << gen  << "\tFrame " << frame << endl;
        frame++;
		field->display();
		int num_alive = n;
		for (int i = 0; i < n; i++) {
			robots[i].update();
			num_alive -= (int) robots[i].is_dead();
            if (num_alive == 8) {
                // Starting the evolution!
                field->clear();
                vector<Robot> new_robots;
                for (int r = 0; r < n; r++) {
                    if (robots[r].is_dead()) {
                        continue;
                    }
                    for (int i = 0; i < mutate_algorithm_s; i++) {
                        new_robots.push_back(Robot(field,robots[r].mutated_program(mutate_algorithm[i])));
                    }
                }
                robots = new_robots;
                gen++;
                break;
            }
		}
		cout << "Alive: " << num_alive;
	}
}


