#include <vector>
#include "SDL.h"
#include "Shape.h"
#include <random>


/*
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
	//clears renderer
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderClear(rend);
	//renders shapes in array
	for (int i = 0; i < shapes.size(); i++)
	{
		(*shapes[i]).render(rend);
	}
}

void delVector(vector<Shape*>* shapes)
{
	cout << "delVector called\n";
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
	cout << "Keybindings:\n";
	cout << " 'r' : create shape: rectangle\n";
	cout << " 't' : create shape: triangle\n";
	cout << " 'c' : create shape: circle\n";
	cout << " 'd' : draw shapes\n";
	cout << " 'x' : delete all shapes\n";
	cout << " 'l' : toggle live drawing on/off\n";
	cout << " 'q' : quit\n";
	cout << " 'h' : displays this help message\n";
}


int main(int argc, char *argv[])
{
	/*
	Rectangle rec1;
	Triangle tri1;
	Circle cir1;

	vector<Shape*> myShapes;

	myShapes.push_back(&rec1);
	myShapes.push_back(&tri1);
	myShapes.push_back(&cir1);

	testRender(myShapes);
	*/


	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	vector<Shape*> myShapes;
	myShapes.push_back(new Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
	myShapes.push_back(new Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
	myShapes.push_back(new Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));


	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	Rectangle rec1= Rectangle(Point2D(50,50),255,0,0,255,200,300);
	rec1.render(renderer);
	Triangle tri1 = Triangle(Point2D(50, 50), 0, 255, 0, 255, 200, 200);
	tri1.render(renderer);
	Circle cir1 = Circle(Point2D(50, 50), 0, 0, 255, 255, 100);
	cir1.render(renderer);

	SDL_RenderPresent(renderer);//updates screen

	helpConsole();

	// Get an event
	SDL_Event event;
	SDL_PollEvent(&event);
	// Wait a bit
	//SDL_Delay(5000);
	//SDL_Event event;
	bool gameLoop = true;
	bool liveDraw = true;
	while (gameLoop)
	{
		//SDL_WaitEvent(&event);
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			gameLoop = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_r://Yes, this is ugly, but it would be just as ugly inside a function call.
				myShapes.push_back(new Rectangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;
			case SDLK_t:
				myShapes.push_back(new Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300 + 1, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;
			case SDLK_c:
				myShapes.push_back(new Circle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 200 + 1));
				if (liveDraw)
					myShapes.back()->render(renderer);
				break;
			case SDLK_q:
				gameLoop = false;
				break;
			case SDLK_x:
				delVector(&myShapes);
				render(myShapes, renderer);
				break;
			case SDLK_d:
				render(myShapes,renderer);
				break;
			case SDLK_l:
				if (liveDraw)
					liveDraw = false;
				else
					liveDraw = true;
				break;
			case SDLK_h:
				helpConsole();
				break;
			}
			break;
		}
		SDL_RenderPresent(renderer);
	}

	// Tidy up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

