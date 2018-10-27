#include <GLFW/glfw3.h>
#include <cstdlib>
#include <stdio.h>
#include <Windows.h>
#include "GameOfLife.h"


const unsigned int width = 480;
const unsigned int height = 270;
const double chance = 0.1;


int main(void)
{
    GLFWwindow* window;

    GameOfLife gameOfLife(width, height);
    gameOfLife.randomize(chance);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        gameOfLife.drawGrid();

        Sleep(50);

        gameOfLife.update();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}