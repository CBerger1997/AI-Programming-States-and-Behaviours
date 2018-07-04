//  Main.cpp
//  Holds all code for the main aspects of the program, linking all classes and instantiating them

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Nodes.h"
#include "BFS.h"
#include "Enemy.h"
#include "Player.h"
#include "States.h"
#include "PowerUp.h"

bool Initialise(const char*, int, int, int, int, int);
void Render(SDL_Rect, BreadthFirstSystem, Enemy*, Player, PowerUp*);
void ReadingFile(std::ifstream &File, BreadthFirstSystem);
void SetAdjacentEdges(BreadthFirstSystem);
void Update(bool, SDL_Rect, BreadthFirstSystem, Enemy*, Player, States, PowerUp*);

struct SDLStruct
{

	SDL_Window* aiWindow;
	SDL_Renderer* aiRenderer;

}creator;

// Function main
int main(int argc, char* argv[])
{

	creator.aiWindow = 0;
	creator.aiRenderer = 0;

	bool aiRunLoop = false;

	BreadthFirstSystem grid;

	//If statement used to check that initialisation has worked correctly, ending the program if something was incorrect
	if (Initialise("AI Path Planner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, grid.GetGrid_x() * 20, grid.GetGrid_y() * 20, SDL_WINDOW_SHOWN))
	
	{

		aiRunLoop = true;

	}

	else

	{

		return 1;

	}

	SDL_Rect tile;

	std::ifstream file("NodesFile.txt", std::ios::in);

	ReadingFile(file, grid);

	tile.h = 20;
	tile.w = 20;

	SetAdjacentEdges(grid);

	Enemy e[4];

	for (int i = 0; i < 4; i++)

	{

		e[i] = e[i].SetInitialPositions(e[i], i);
		e[i] = e[i].SetEnemyPositions(e[i], i);

	}

	PowerUp power[4];

	power[1].SetXPos(820);
	power[1].SetYPos(80);

	power[2].SetXPos(100);
	power[2].SetYPos(620);

	power[3].SetXPos(820);
	power[3].SetYPos(620);


	Player p;

	States state;

	Render(tile, grid, e, p, power);

	Update(aiRunLoop, tile, grid, e, p, state, power);

	SDL_Quit();
	return 0;

};

// Function used to initialise SDL2
bool Initialise(const char* header, int x, int y, int h, int w, int flags)
{

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)

	{

		// if SDL initialises, the if statement is run and sets the variables for aiWindow
		creator.aiWindow = SDL_CreateWindow(header, x, y,
			h, w, flags);

		// if the window creation succeeded create our renderer
		if (creator.aiWindow != 0)

		{

			creator.aiRenderer = SDL_CreateRenderer(creator.aiWindow, -1, 0);

		}

	}

	else

	{

		//means SDL failed to initialise
		return false;

	}

	//means SDL initialised correctly
	return true;

};

// Function used to render the window
void Render(SDL_Rect tile, BreadthFirstSystem grid, Enemy e[], Player p1, PowerUp power[])
{

	tile.x = 0;
	tile.y = 0;

	// Clear the window to set Colour
	SDL_RenderClear(creator.aiRenderer);

	for (int i = 0; i < grid.GetTotalNodes(); i++)

	{

		grid.SetNode_x(tile.x, i);
		grid.SetNode_y(tile.y, i);

		if (grid.GetNodeValues(i) == 1)

		{

			// Set Render Colour to Black
			SDL_SetRenderDrawColor(creator.aiRenderer, 0, 0, 0, 0);
			grid.SetClosedNodes(true, i);

		}

		else if (grid.GetNodeValues(i) == 0)

		{

			// Set Render Colour to White
			SDL_SetRenderDrawColor(creator.aiRenderer, 255, 255, 255, 255);
			grid.SetClosedNodes(false, i);

		}

		for (int i = 0; i < 4; i++)

		{

			if (tile.x == e[i].GetXPos() && tile.y == e[i].GetYPos())

			{

				// Set Render Colour for Enemy
				if (e[i].GetState() != 3)

				{

					SDL_SetRenderDrawColor(creator.aiRenderer, 255, 0, 0, 255);
				
				}
				
				else
				
				{

					SDL_SetRenderDrawColor(creator.aiRenderer, 255, 255, 0, 255);
				
				}

			}

		}

		for (int i = 0; i < 4; i++)

		{

			if (tile.x == power[i].GetXPos() && tile.y == power[i].GetYPos())

			{

				// Set Render Colour for Power
					SDL_SetRenderDrawColor(creator.aiRenderer, 255, 0, 255, 255);

			}

		}

		if (tile.x == p1.GetXPos() && tile.y == p1.GetYPos())

		{

			// Set Render Colour for Player
			SDL_SetRenderDrawColor(creator.aiRenderer, 0, 0, 255, 255);

		}

		// Render the Tile 
		SDL_RenderFillRect(creator.aiRenderer, &tile);

		tile.x += 20;

		if (tile.x >= grid.GetGrid_x() * 20)

		{

			tile.x = 0;
			tile.y += 20;

		};

	};

	// Display the Window
	SDL_RenderPresent(creator.aiRenderer);

};

// Function used to read numbers from the file NodesFile.txt
void ReadingFile(std::ifstream &file, BreadthFirstSystem grid)
{

	int fileNums;
	std::vector<int> nodeNums;

	while (file >> fileNums) 

	{

		nodeNums.push_back(fileNums);

	};

	for (int i = 0; i < nodeNums.size(); i++)

	{

		grid.SetNodeValues(nodeNums[i], i);

	};

	file.close();

};

// Funcion used to connect all nodes that are adjacent to each other
void SetAdjacentEdges(BreadthFirstSystem grid)

{

	int count;

	for (int y = 0; y < grid.GetGrid_y(); y++)

	{

		for (int x = 0; x < grid.GetGrid_x(); x++)

		{
			count = x;

			if (y > 0)

			{

				count = count + grid.GetGrid_x() * (y);

			}

			if (count - grid.GetGrid_x() >= 0)

			{
				grid.NodeEdge(count, count - grid.GetGrid_x());

			}

			if ((count + 1) % grid.GetGrid_x() != 0)

			{

				grid.NodeEdge(count, count + 1);

			}

			if (count + grid.GetGrid_x() < grid.GetTotalNodes())

			{
				grid.NodeEdge(count, count + grid.GetGrid_x());

			}

			if (((count - 1) % grid.GetGrid_x() != grid.GetGrid_x() - 1) && (count != 0))

			{

				grid.NodeEdge(count, count - 1);

			}

			//std::cout << (Grid.GetAdjacent(count)) << std::endl;
		}

	}

}

// Function used to Update the program through a loop
void Update(bool aiRunLoop, SDL_Rect tile, BreadthFirstSystem grid, Enemy e[], Player p1, States state, PowerUp power[])
{

	bool playerMove;
	int playerDistance = 11;
	int displaycount = 0;

	while (aiRunLoop && p1.GetLives() > 0)

	{

		p1.SetScore(p1.GetScore() + 1);

		SDL_Event event;

		for (int i = 0; i < 4; i++)

		{

			switch (e[i].GetState())

			{

			case 1:

				e[i].SetEnemyDirection(state.ChooseDirection(e[i], grid));
				e[i] = state.MoveRoamingEnemy(e[i], grid, e[i].GetEnemyDirection());
				state.EnemyToPlayerSearch(grid, e[i], p1);
				playerDistance = state.ShortestSearchPath(grid, e[i], p1);

				if (playerDistance < 10)

				{

					e[i].SetState(2);
					displaycount = 0;
					system("CLS");

				}

				break;

			case 2:

				state.EnemyToPlayerSearch(grid, e[i], p1);
				playerDistance = state.ShortestSearchPath(grid, e[i], p1);
				e[i] = state.ChasePlayer(grid, e[i], playerDistance);

				break;

			case 3:

				e[i].SetEnemyDirection(state.ChooseDirection(e[i], grid));
				e[i] = state.MoveRoamingEnemy(e[i], grid, e[i].GetEnemyDirection());
				
				if (state.GetFleeingcount() == 150)

				{

					for (int i = 0; i < 4; i++)

					{

						if (e[i].GetState() != 4)

						{

							e[i].SetState(1);
							displaycount = 0;
							system("CLS");

						}

					}

				}

				else

				{

					state.IncrementFleeingCount();

				}	

				break;

			case 4:

				if (state.GetFleeingcount() == 150)

				{

					e[i].SetState(1);
					displaycount = 0;
					system("CLS");
					e[i] = e[i].SetEnemyPositions(e[i], i);

				}

				else

				{

					state.IncrementFleeingCount();

				}

				break;

			}

			if (displaycount < 5)

			{

				if (displaycount < 4)

				{

					std::cout << "Enemy " << i + 1 << " is in State: " << e[i].GetState();

					if (e[i].GetState() == 1)

					{

						std::cout << " : Roaming State\n\n";

					}

					else if (e[i].GetState() == 2)

					{

						std::cout << " : Chasing State\n\n";

					}

					else if (e[i].GetState() == 3)

					{

						std::cout << " : Fleeing State\n\n";

					}

					else if (e[i].GetState() == 4)

					{

						std::cout << " : Dead State\n\n";

					}

				}

				else

				{

					std::cout << "Player lives left: " << p1.GetLives() << "\n\n";

				}

				displaycount++;

			}
			
		}

			Sleep(200);
		
		while (SDL_PollEvent(&event))

		{

			if (event.type == SDL_QUIT)

			{

				aiRunLoop = false;

			};

			if (event.type == SDL_KEYDOWN)

			{

				if (event.key.keysym.sym == SDLK_UP)

				{

					playerMove = p1.PlayerLocalCollisionCheck(grid, p1, 1);

					if (playerMove == true)

					{

						p1.SetYPos(p1.GetYPos() - 20);

					}

				}

				else if (event.key.keysym.sym == SDLK_DOWN)

				{

					playerMove = p1.PlayerLocalCollisionCheck(grid, p1, 3);

					if (playerMove == true)

					{

						p1.SetYPos(p1.GetYPos() + 20);

					}

				}

				else if (event.key.keysym.sym == SDLK_LEFT)

				{

					playerMove = p1.PlayerLocalCollisionCheck(grid, p1, 4);

					if (playerMove == true)

					{

						p1.SetXPos(p1.GetXPos() - 20);

					}

				}

				else if (event.key.keysym.sym == SDLK_RIGHT)

				{

					playerMove = p1.PlayerLocalCollisionCheck(grid, p1, 2);

					if (playerMove == true)

					{

						p1.SetXPos(p1.GetXPos() + 20);

					}

				}

				else if (event.key.keysym.sym == SDLK_ESCAPE)

				{

					aiRunLoop = false;

				};

			};

		};

		Render(tile, grid, e, p1, power);

		for (int i = 0; i < 4; i++)

		{

			if (e[i].GetXPos() == p1.GetXPos() && e[i].GetYPos() == p1.GetYPos() && e[i].GetState() == 2)

			{

				p1.SetLives(p1.GetLives() - 1);
				p1 = p1.SetPlayerPosition(p1);

				for (int i = 0; i < 4; i++)

				{

					e[i] = e[i].SetEnemyPositions(e[i], i);
					e[i].SetState(1);
					displaycount = 0;
					system("CLS");

				}

			}

			else if (e[i].GetXPos() == p1.GetXPos() && e[i].GetYPos() == p1.GetYPos() && e[i].GetState() == 3)

			{

				e[i].SetState(4);
				e[i].SetXPos(1000);
				e[i].SetYPos(1000);
				p1.SetScore(p1.GetScore() + 100);
				displaycount = 0;
				system("CLS");

			}

			if (power[i].GetXPos() == p1.GetXPos() && power[i].GetYPos() == p1.GetYPos())

			{

				power[i].SetXPos(1000);
				power[i].SetYPos(1000);

				for (int i = 0; i < 4; i++)

				{

					e[i].SetState(3);

				}

				state.ResetFleeingCount();
				displaycount = 0;
				system("CLS");

			}

		}

	};

	std::cout << "Score: " << p1.GetScore() << "\n\n";
	std::cin.get();

};