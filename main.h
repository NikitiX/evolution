#define pi 3.14159265

enum Cell { Void, Plant, AliveRobot, DeadRobot };
enum Action { Nothing, Move, Turn, If };

const int fsizex = 64;
const int fsizey = 20;
const int psize = 128;
const int variety = 100;
const int mutate_algorithm_s = 5;
const int mutate_algorithm[] = {0,1,1,2,2};
const int n = 40;
