class Robot {
private:
    int health;
	int pointer;
	int pos_x, pos_y;
	int direction;
    bool was_dead;
	Field* field;
	vector<int> program;
	void move_pointer(int);
    bool update_position(int, int);
    void move();
    void turn();
    void ifplantelse();
    vector<int> mutated_program(vector<int>);
public:
    Robot(Field*);
    Robot(Field*, vector<int>);
    bool is_dead();
    bool is_now_dead();
    void update();
    vector<int> mutated_program(int);
};