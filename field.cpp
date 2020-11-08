#include "field.h"

Field::Field() {
	for (int i = 0; i < fsizey; i++) {
		cells.push_back(vector<Cell>());
        for (int j = 0; j < fsizex; j++) {
            switch (rand() % variety) {
            case 1:
                cells[i].push_back(Plant);
                break;
            default:
                cells[i].push_back(Void);
			}
		}
	}
}

void Field::clear() {
    for (int i = 0; i < fsizey; i++) {
        for (int j = 0; j < fsizex; j++) {
            switch (rand() % variety) {
            case 1:
                cells[i][j] = Plant;
                break;
            default:
                cells[i][j] = Void;
            }
        }
    }
}

void Field::eaten(int x, int y) {
    cells[x][y] = Void;
    while (true) {
        int new_posx = rand() % fsizex;
        int new_posy = rand() % fsizey;
        if (get(new_posx, new_posy) == Void) {
            set(new_posx, new_posy, Plant);
            return;
        }
    }
}

void Field::set(int i, int j, Cell x) {
    cells[j][i] = x;
}

Cell Field::get(int i, int j) {
    return cells[j][i];
}

void Field::display() {
    for (int i = 0; i < fsizey; i++) {
        for (int j = 0; j < fsizex; j++) {
            switch (cells[i][j]) {
            case Void:
                cout << " ";
                break;
            case Plant:
                cout << "#";
                break;
            case AliveRobot:
                cout << "x";
                break;
            case DeadRobot:
                cout << "*";
                break;
            }
        }
        cout << endl;
    }
}