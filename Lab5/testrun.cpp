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

	// Get an event
	SDL_Event event;
	SDL_PollEvent(&event);
	// Wait a bit
	//SDL_Delay(5000);
	//SDL_Event event;
	bool gameloop = true;
	while (gameloop)
	{
		//SDL_WaitEvent(&event);
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			gameloop = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_r://Yes, this is ugly, but it would be just as ugly inside a function call.
				rec1 = Rectangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300+1, rand() % 200+1);
				rec1.render(renderer);
				break;
			case SDLK_t:
				tri1 = Triangle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 300+1, rand() % 200+1);
				tri1.render(renderer);
				break;
			case SDLK_c:
				cir1 = Circle(Point2D(rand() % 600, rand() % 400), rand() % 256, rand() % 256, rand() % 256, 255, rand() % 200 + 1);
				cir1.render(renderer);
				break;
			case SDLK_q:
				gameloop = false;
				break;
			}
			break;
		//default:
			//break;
		}
		/*
		// Get the next event
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				// Break out of the loop on quit
				break;
			}
		}
		Uint8 red = rand() % 255;
		Uint8 green = rand() % 255;
		Uint8 blue = rand() % 255;
		SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
		SDL_RenderClear(renderer);
		*/
		SDL_RenderPresent(renderer);
	}

	// Tidy up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}

