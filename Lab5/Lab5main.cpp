#include <vector>
#include "SDL.h"
#include "Shape.h"
#include <random>


/* task 1 bullcrap. no longer valid
void testRender(vector<Shape*> shapes)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		(*shapes[i]).render();
	}
}
*/


void render(vector<Shape*> shapes, SDL_Renderer* rend)
{
	cout << "render function called\n";
	//clears renderer, color black
	SDL_RenderClear(rend);
	//renders shapes in array
	for (int i = 0; i < shapes.size(); i++)
	{
		(*shapes[i]).render(rend);
	}
}

void delVector(vector<Shape*>* shapes)
//Takes a pointer to a vector of pointers, this so it can clear the pointers from the vector after the shapes are deleted.
{
	cout << "delVector function called\n";
	//deletes all shapes corresponding to the pointers in the vector
	for (int i = 0; i < (*shapes).size(); i++)
	{
		delete (*shapes)[i];
	}
	//clears the array of all the pointers
	(*shapes).clear();
}

void helpConsole()
{
	cout << "helpConsole function called\n";
	cout << "\nKeybindings:\n";
	cout << " 'r' : create shape: rectangle\n";
	cout << " 't' : create shape: triangle\n";
	cout << " 'c' : create shape: circle\n";
	cout << " 'd' : draw shapes\n";
	cout << " 'x' : delete all shapes\n";
	cout << " 'b' : randomize background color\n";
	cout << " 'l' : toggle live drawing on/off\n";
	cout << " 'h' : displays this help message\n";
	cout << " 'q' : quit\n";
}


int main(int argc, char *argv[])
{
	/*task 1 bullcrap. no longer valid
	Rectangle rec1;
	Triangle tri1;
	Circle cir1;

	vector<Shape*> myShapes;

	myShapes.push_back(&rec1);
	myShapes.push_back(&tri1);
	myShapes.push_back(&cir1);

	testRender(myShapes);
	*/

	//SDL subsystem initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	//Creates window
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	//inizialize an SDL_Renderer, and set a pointer to it.
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//enables blending by alpha
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	//declare a vector of shape pointers
	vector<Shape*> myShapes;

	//prints available keycommands in console
	helpConsole();

	// declares an event
	SDL_Event event;

	//rgb values for the background, default black.
	int bgr=0, bgg=0, bgb=0;
	//sets the draw color for background
	SDL_SetRenderDrawColor(renderer, bgr, bgg, bgb, 255);
	//renders the background color in the case it´s not black.
	SDL_RenderClear(renderer);

	bool gameLoop = true;
	//if liveDraw, shapes are drawn as soon as they are created.
	bool liveDraw = true;
	while (gameLoop)
	{
		//fetch event from the event queue 
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT://on event application quit.
			gameLoop = false;
			break;
		case SDL_KEYDOWN://on event keydown.
			switch (event.key.keysym.sym)
			{
			case SDLK_r://keycode 'r' create a rectangle
				myShapes.push_back(new Rectangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;

			case SDLK_t://keycode 't' create a triangle
				myShapes.push_back(new Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;

			case SDLK_c://keycode 'c' create a circle
				myShapes.push_back(new Circle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;

			case SDLK_q://keycode 'q' quit gameloop
				gameLoop = false;
				break;

			case SDLK_x://keycode 'x' deletes all shapes in vector and clears screen
				SDL_SetRenderDrawColor(renderer, bgr, bgg, bgb, 255);
				delVector(&myShapes);
				render(myShapes, renderer);
				break;

			case SDLK_d://keycode 'd' draw shapes in vector
				SDL_SetRenderDrawColor(renderer, bgr, bgg, bgb, 255);
				render(myShapes,renderer);
				break;

			case SDLK_l://keycode 'l' toggles livedraw on/off
				if (liveDraw)
				{
					liveDraw = false;
					cout << "liveDraw: OFF\n";
				}
				else
				{
					liveDraw = true;
					cout << "liveDraw: ON\n";
				}
				break;

			case SDLK_h://keycode 'h' prints help message in console
				helpConsole();
				break;

			case SDLK_b://keycode 'b' randomize background color.
				bgr = rand() % 256;
				bgg = rand() % 256;
				bgb = rand() % 256;
				SDL_SetRenderDrawColor(renderer, bgr, bgg, bgb, 255);
				render(myShapes, renderer);
				break;
			}
			break;
		}
		SDL_RenderPresent(renderer);//updates screen
	}

	// Tidy up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//cleans up initialized subsystems
	SDL_Quit();

	return 0;
}

