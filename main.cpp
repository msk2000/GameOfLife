// SFML based implementation of Conway's Game of Life
// Author: M Safat Khan
// NOTE: This is not a finished product. It is an intermediate step
// on my way to a bigger project. As such, this code contains
// things that are meant only for testing/debugging purpose which
// would not normmaly make it to a final release.
#include <SFML/System/Time.hpp>
#include <iostream>
#include <eigen3/Eigen/Dense> // Will use this as the underlying grid
#include <utility> // for std::pair
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define DISPLAY_X 800 // Controls the Horizontal size of the window
#define DISPLAY_Y 600 // Controls the Vertical size of the window
#define CELL_SIZE 5	  //Controls the cell size (squares)
#define M (DISPLAY_Y/CELL_SIZE) // number of rows of the grid
#define N (DISPLAY_X/CELL_SIZE) // number of columns of the gridid
#define POPULATION ((DISPLAY_X*DISPLAY_Y)/20) // Controls the max number of seed population at the start
#define DELAY 600     // Used to speed up or slow down the simulation

void debug_print(Eigen::Matrix<char,Eigen::Dynamic,Eigen::Dynamic> grid);
void randPopulate(Eigen::Matrix<char,Eigen::Dynamic,Eigen::Dynamic>& grid, std::vector<std::pair<int,int>>& location);
void addTestPattern(Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid, const std::string& pattern, int x, int y);
void printLocation(const std::vector<std::pair<int,int>> location);
void drawGrid(sf::RenderWindow& window, Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid);
void updateGrid_test(Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid);




int main()
{

	// SFML Window
	sf::RenderWindow window(sf::VideoMode(DISPLAY_X,DISPLAY_Y),"Game of Life");
	//This is the main grid/universe 
	Eigen::Matrix<char,Eigen::Dynamic,Eigen::Dynamic> grid(M,N);
	grid.setConstant('D'); // All dead (D)

	//We will use this to localise all life (x,y) on grid
	std::vector<std::pair<int,int>> location;
	//Loading font
	sf::Font font;
	font.loadFromFile("./highland-gothic/HighlandGothicFLF-Bold.ttf");
	int genCount = 0;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);
	//Setting Random positions representing life (with L)
	randPopulate(grid,location); // this function should only be called once/init()
	//Printing the locations for test

	/*  USE THESE TO TRY FUN PATTERS
	addTestPattern(grid, "glider", 5, 5);
	addTestPattern(grid, "blinker", 10, 10);
	addTestPattern(grid, "block", 15, 15);
	addTestPattern(grid,"toad", 40,40);
	addTestPattern(grid,"beacon",80,80);addTestPattern(grid, "lwss", 20, 5);
	addTestPattern(grid, "pulsar", 30, 30);
	addTestPattern(grid, "pentadecathlon", 50, 10);
	addTestPattern(grid, "diehard", 60, 60);
	addTestPattern(grid, "acorn", 70, 20);
	printLocation(location); */
	//debug_print(grid);
	
	// Main program loop
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event)) // checking for any user request for closing the program every loop
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//Update the display text
		std::string generation = "Generation: " + std::to_string(genCount);
		text.setString(generation);

		window.clear(); // clear window
		drawGrid(window,grid); // draw the grid
		window.draw(text); // put the text on screen
		window.display(); // update the window with all the next content
		updateGrid_test(grid); // apply the GOL rules to the grid to generate seed for next round
		genCount++; // for display string counter
		sf::sleep(sf::milliseconds(DELAY)); // delay to control execution time
		
	}




return 0;
}

//Function used to verify correct patterns on grid
void debug_print(Eigen::Matrix<char,Eigen::Dynamic,Eigen::Dynamic> grid)
{
	for (int i = 0; i < grid.rows(); ++i)
	{
    		for (int j = 0; j < grid.cols(); ++j)
			{
        		std::cout << grid(i, j);  // prints the char directly
    		}
    		std::cout << std::endl;
	}
}
//Function used to populate the board patters in randomised locations
void randPopulate(Eigen::Matrix<char,Eigen::Dynamic,Eigen::Dynamic>& grid, std::vector<std::pair<int,int>>& location)
{
	for (int i = 0; i < POPULATION; ++i)
	{
    		int x = rand() % grid.rows();
			int y = rand() % grid.cols();
    		grid(x, y) = 'L';
		location.emplace_back(std::make_pair(x,y)); // This is just for program testing and debugging
	}

}
//Function to try out typical interesting patterns
void addTestPattern(Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid, const std::string& pattern, int x, int y)
{
	// Collection of test patters you can find and keep adding here. :D
	// You can find all sorts of these patterns discovered by people.
	// Just cloning some of them here for our amusement
    if (pattern == "glider")
	{
        grid(x, y + 1) = 'L';
        grid(x + 1, y + 2) = 'L';
        grid(x + 2, y) = 'L';
        grid(x + 2, y + 1) = 'L';
        grid(x + 2, y + 2) = 'L';
    }
    else if (pattern == "blinker")
	{
        grid(x, y) = 'L';
        grid(x, y + 1) = 'L';
        grid(x, y + 2) = 'L';
    }
    else if (pattern == "block")
	{
        grid(x, y) = 'L';
        grid(x, y + 1) = 'L';
        grid(x + 1, y) = 'L';
        grid(x + 1, y + 1) = 'L';
    }
    else if (pattern == "toad")
    {
        grid(x + 1, y) = 'L';
        grid(x + 1, y + 1) = 'L';
        grid(x + 1, y + 2) = 'L';
        grid(x, y + 1) = 'L';
        grid(x, y + 2) = 'L';
        grid(x, y + 3) = 'L';
    }
    else if (pattern == "beacon")
    {
        grid(x, y) = 'L';
        grid(x, y + 1) = 'L';
        grid(x + 1, y) = 'L';
        grid(x + 1, y + 1) = 'L';

        grid(x + 2, y + 2) = 'L';
        grid(x + 2, y + 3) = 'L';
        grid(x + 3, y + 2) = 'L';
        grid(x + 3, y + 3) = 'L';
    }
	else if (pattern == "lwss") // Lightweight Spaceship
	{
	    grid(x, y + 1) = 'L';
	    grid(x, y + 4) = 'L';
	    grid(x + 1, y) = 'L';
	    grid(x + 2, y) = 'L';
	    grid(x + 3, y) = 'L';
	    grid(x + 3, y + 3) = 'L';
	    grid(x + 3, y + 4) = 'L';
	    grid(x + 1, y + 4) = 'L';
	}
	else if (pattern == "pulsar")
	{
	    int dx[] = {2,3,4,8,9,10};
	    int dy[] = {0,5,7,12};

	    for (int i : dx) {
		for (int j : dy) {
		    grid(x+i, y+j) = 'L';
		    grid(x+j, y+i) = 'L'; // symmetry
		}
	    }
	}
	else if (pattern == "pentadecathlon")
	{
	    for (int i = 0; i < 10; i++)
	    {
		grid(x + i, y) = 'L';
		if (i != 0 && i != 9)
		    grid(x + i, y - 1) = 'L', grid(x + i, y + 1) = 'L';
	    }
	}
	else if (pattern == "diehard")
	{
	    grid(x, y + 6) = 'L';
	    grid(x + 1, y) = 'L';
	    grid(x + 1, y + 1) = 'L';
	    grid(x + 2, y + 1) = 'L';
	    grid(x + 2, y + 5) = 'L';
	    grid(x + 2, y + 6) = 'L';
	    grid(x + 2, y + 7) = 'L';
	}
	else if (pattern == "acorn")
	{
	    grid(x, y + 1) = 'L';
	    grid(x + 1, y + 3) = 'L';
	    grid(x + 2, y) = 'L';
	    grid(x + 2, y + 1) = 'L';
	    grid(x + 2, y + 4) = 'L';
	    grid(x + 2, y + 5) = 'L';
	    grid(x + 2, y + 6) = 'L';
	}
}

// Function used to look at the locations of the live cells on console
void printLocation(const std::vector<std::pair<int,int>> location)
{
	std::cout << "Life Coordinates:\n";
    	for (const auto& [x, y] : location)
	{
        	std::cout << "(" << x << ", " << y << ")\n";
	}
}
// Function used to generate the underlying 2d grid/world
void drawGrid(sf::RenderWindow& window, Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid)
{
    for (int i = 0; i < grid.rows(); ++i)
    {
        for (int j = 0; j < grid.cols(); ++j)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));  // Each cell is a square
            cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);  // Position it on the screen
            if (grid(i, j) == 'L')
            {
                cell.setFillColor(sf::Color::Green);  // Represent 'L' with green
            }
            else
            {
                cell.setFillColor(sf::Color::Black);  // Blank cells are white
            }

            window.draw(cell);
        }
    }
}

//Function used to update the grid based on the rules of GOL
void updateGrid_test(Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic>& grid)
{
    Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic> updated_grid(M, N);
    updated_grid.setConstant('D');

    for (int i = 0; i < M; i++) // every row
    {
	for (int j = 0; j < N; j++) // every column
	 {
            int count = 0;

            for (int k = -1; k <= 1; k++) // neighbor rows
            {
                for (int l = -1; l <= 1; l++) // neighbor cols
                {
                    if (k == 0 && l == 0) continue; // skip self

                    int neighbor_i = i + k;
                    int neighbor_j = j + l;

                    if (neighbor_i >= 0 && neighbor_i < M && neighbor_j >= 0 && neighbor_j < N)
                    {
                        if (grid(neighbor_i, neighbor_j) == 'L') // neighbor is alive
	 		{
	 			count++;
	 		}
                    }
                }
            }

            if (grid(i, j) == 'L')
            {
                // the rules for live cells
                if (count == 2 || count == 3)
	     	{
	 		updated_grid(i, j) = 'L'; // survives
		}
		else
	 	{
                    updated_grid(i, j) = 'D'; // dies
            	}
	    }
	    else
            {
                // Otherwise if es ist tot
                if (count == 3)
	     	{
			updated_grid(i, j) = 'L'; // ressurected
		}
		else
		{
                    updated_grid(i, j) = 'D'; // remains dead
            	}
           }
	}
    }

    grid = updated_grid;
}

