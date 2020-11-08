class Field {
private:
    vector<vector<Cell> > cells;
public:
    Field();
    void clear();
    void eaten(int, int);
    void set(int, int, Cell);
    Cell get(int, int);
    void display();
};