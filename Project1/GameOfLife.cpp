#include "GameOfLife.h"
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <stdio.h>


GameOfLife::GameOfLife(int width, int height)
{
    this->width = width;
    this->height = height;
    grid = new bool*[width];

    for (int i = 0; i < width; i++)
    {
        bool* row = new bool[height];
        for (int j = 0; j < height; j++)
        {
            row[j] = false;
        }
        grid[i] = row;
    }
}

void GameOfLife::randomize(float chance)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            bool value = ((float)rand() / RAND_MAX) < chance;
            grid[i][j] = value;
        }
    }
}

void GameOfLife::update()
{
    bool** newGrid = new bool*[width];

    for (int i = 0; i < width; i++)
    {
        newGrid[i] = new bool[height];
        for (int j = 0; j < height; j++)
        {
            int neighborCount = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if ((k != i || l != j) && k >= 0 && k < width && l >= 0 && l < height && grid[k][l])
                    {
                        neighborCount++;
                    }
                }
            }
            newGrid[i][j] = grid[i][j] && neighborCount >= 2 && neighborCount <= 3 || !grid[i][j] && neighborCount == 3;
        }
    }

    for (int i = 0; i < width; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    grid = newGrid;
}

void GameOfLife::drawGrid()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (grid[i][j])
            {
                glRectf((float)2 * i / width - 1, (float)2 * j / height - 1, 2 * ((float)i + 1) / width - 1, 2 * ((float)j + 1) / height - 1);
            }
        }
    }
}
