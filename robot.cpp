#include "robot.h"

void Robot::move_pointer(int i) {
    this->pointer = (this->pointer + i) % (psize);
}

bool Robot::update_position(int x, int y) {
    if ((field->get(x, y) == AliveRobot) || ((field->get(x, y) == DeadRobot))) {
        return false;
    }
    if (field->get(x, y) == Plant) {
        health = 100;
        field->eaten(y, x);
    }
    field->set(pos_x, pos_y, Void);
    field->set(x, y, AliveRobot);
    pos_x = x; pos_y = y;
    return true;
}

void Robot::move() {
    int new_posx = pos_x + (int)(round(cos(pi / 2 * direction)));
    if (new_posx >= fsizex) {
        new_posx -= fsizex;
    }
    if (new_posx < 0) {
        new_posx += fsizex;
    }
    int new_posy = pos_y + (int)(round(sin(pi / 2 * direction)));
    if (new_posy >= fsizey) {
        new_posy -= fsizey;
    }
    if (new_posy < 0) {
        new_posy += fsizey;
    }
    update_position(new_posx, new_posy);
}

void Robot::turn() {
    direction = (direction + 1) % 4;
}

void Robot::ifplantelse() {
    int new_posx = pos_x + (int)(round(cos(pi / 2 * direction)));
    if (new_posx >= fsizex) {
        new_posx -= fsizex;
    }
    if (new_posx < 0) {
        new_posx += fsizex;
    }
    int new_posy = pos_y + (int)(round(sin(pi / 2 * direction)));
    if (new_posy >= fsizey) {
        new_posy -= fsizey;
    }
    if (new_posy < 0) {
        new_posy += fsizey;
    }
    if (field->get(new_posx,new_posy) == Plant) {
        pointer = program[pointer + 1];
    }
    else {
        pointer = program[pointer + 2];
    }
}

Robot::Robot(Field* field) {
    vector<int> program;
    for (int i = 0; i < psize; i++) {
        int the = rand() % 4;
        program.push_back(the);
        if (the == 3) {
            program.push_back(rand() % (psize));
            program.push_back(rand() % (psize));
            i += 2;
        }
    }
    this->health = 50;
    this->program = program;
    this->pointer = 0;
    this->pos_x = rand() % fsizex;
    this->pos_y = rand() % fsizey;
    this->direction = 0;
    this->field = field;
    field->set(pos_x, pos_y, AliveRobot);
}

Robot::Robot(Field* field, vector<int> program) {
    this->health = 50;
    this->program = program;
    this->pointer = 0;
    this->pos_x = rand() % fsizex;
    this->pos_y = rand() % fsizey;
    this->direction = 0;
    this->field = field;
    field->set(pos_x, pos_y, AliveRobot);
}

bool Robot::is_dead() {
    return health <= 0;
}

bool Robot::is_now_dead() {
    if ((health <= 0) && (!was_dead)) {
        was_dead = true;
        return true;
    } else {
        return false;
    }
}

void Robot::update() {
    if (is_dead()) {
        field->set(pos_x,pos_y,DeadRobot);
        return;
    }
    health -= 1;
    move_pointer(1);
    switch (this->program[this->pointer]) {
    case 0:
        break;
    case 1:
        move();
        break;
    case 2:
        turn();
        break;
    case 3:
        ifplantelse();
    }
    return;
}

vector<int> Robot::mutated_program(vector<int> program) {
    int i = rand() % (psize);
    if (((i > 1) && (program[i - 2] == 3)) || ((i > 0) && (program[i - 1] == 3))) {
        program[i] = rand() % (psize);
    }
    else {
        program[i] = rand() % 4;
    }
    return program;
}

vector<int> Robot::mutated_program(int size) {
    if (size == 2) {
        int times = rand() % (psize / 10);
        vector<int> program = this->program;
        for (int i = 0; i < times; i++) {
            program = mutated_program(program);
        }
        return program;
    }
    if (size == 1) {
        return mutated_program(program);
    }
    return program;
}