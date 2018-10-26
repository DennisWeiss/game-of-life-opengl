#include <GLFW/glfw3.h>
#include <cstdlib>
#include <stdio.h>
#include <Windows.h>


const unsigned int width = 480;
const unsigned int height = 270;
const double chance = 0.1;


bool** afterOneCycle(bool** grid, unsigned int width, unsigned int height)
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

	return newGrid;
}

bool** randomGrid(unsigned int width, unsigned int height)
{
	
	bool** grid = new bool*[width];

	for (int i = 0; i < width; i++)
	{
		grid[i] = new bool[height];
		for (int j = 0; j < height; j++)
		{
			grid[i][j] = ((double) rand() / RAND_MAX) < chance;
		}
	}

	return grid;
}

void drawGrid(bool** grid, unsigned int width, unsigned int height)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < width; i++) 
	{
		for (int j = 0; j < height; j++) 
		{
			if (grid[i][j]) 
			{
				glRectf((float)2 * i / width - 1, (float) 2 * j / height - 1, 2 * ((float) i + 1) / width - 1, 2 * ((float) j + 1) / height - 1);
			}
		}
	}
}

bool** updateGrid(bool** grid, unsigned int width, unsigned int height)
{
	drawGrid(grid, width, height);
	Sleep(50);
	return afterOneCycle(grid, width, height);
}


int main(void)
{
	GLFWwindow* window;

	bool** grid = randomGrid(width, height);

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

		grid = updateGrid(grid, width, height);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}