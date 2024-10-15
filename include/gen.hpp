#pragma once

enum Type{
    EMPTY,
    VER1,
    VER2
};

struct Vector2{
    int x;
    int y;
};

class gen{
    private:
        int grid_size;
        Type grid_type;
    public:
        gen(Type grid_type);
        gen();
        Type get_type();
        int get_size();
};
