#pragma once

class GameOfLife 
{
private:
    int width;
    int height;
    bool** grid;

public:
    GameOfLife(int width, int height);
    void randomize(float chance);
    void update();
    void drawGrid();
};