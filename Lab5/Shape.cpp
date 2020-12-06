#include "Shape.h"
#include <math.h>

Shape::Shape(Point2D _pos, int r, int g, int b, int a)
{
	pos = _pos;
	color(r, g, b, a);
}

void Shape::color(int r, int g, int b, int a)
{
	//if color values are in the correct range, set color.
	if (0 <= r && r <= 255)
		col[0] = r;
	if (0 <= g && g <= 255)
		col[1] = g;
	if (0 <= b && b <= 255)
		col[2] = b;
	if (0 <= a && a <= 255)
		col[3] = a;
}

std::string Shape::info()
{
	//returns a string of information on position and color.
	std::string infostring = "Position: " + pos.toString() + " Color: (";
	for (int i = 0; i < 4; i++)
	{
		infostring += std::to_string(col[i]);
		if (i<3)
			infostring += ",";
	}
	infostring += ")";
	return infostring;
}

Rectangle::Rectangle(Point2D _pos, int r, int g, int b, int a, int _width, int _height)
	:Shape(_pos,r,g,b,a),width(_width),height(_height){}

void Rectangle::render(SDL_Renderer* rend)
{
	//prints info in console
	cout << "Rectangle: position: " << pos.toString() << " width: " << width << " height: " << height << endl;

	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);

	//defines corners
	Point2D cornerUL = Point2D(pos.x, pos.y);
	Point2D cornerUR = Point2D(pos.x+width, pos.y);
	Point2D cornerLR = Point2D(pos.x+width, pos.y+height);
	Point2D cornerLL = Point2D(pos.x, pos.y+height);

	//draw lines between corners
	SDL_RenderDrawLine(rend, cornerUL.x, cornerUL.y, cornerUR.x, cornerUR.y);
	SDL_RenderDrawLine(rend, cornerUR.x, cornerUR.y, cornerLR.x, cornerLR.y);
	SDL_RenderDrawLine(rend, cornerLR.x, cornerLR.y, cornerLL.x, cornerLL.y);
	SDL_RenderDrawLine(rend, cornerLL.x, cornerLL.y, cornerUL.x, cornerUL.y);
}

Triangle::Triangle(Point2D _pos, int r, int g, int b, int a, int _width, int _height)
	:Shape(_pos, r, g, b, a), base(_width), height(_height) {}

void Triangle::render(SDL_Renderer* rend)
{
	//prints info in console
	cout << "Triangle: position: " << pos.toString() << " base: " << base << " height: " << height<<endl;

	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);

	//defines corners
	Point2D cornerU = Point2D(pos.x+base/2, pos.y);
	Point2D cornerRR = Point2D(pos.x + base, pos.y+height);
	Point2D cornerLR = Point2D(pos.x, pos.y + height);

	//draw lines between corners
	SDL_RenderDrawLine(rend, cornerU.x, cornerU.y, cornerRR.x, cornerRR.y);
	SDL_RenderDrawLine(rend, cornerRR.x, cornerRR.y, cornerLR.x, cornerLR.y);
	SDL_RenderDrawLine(rend, cornerLR.x, cornerLR.y, cornerU.x, cornerU.y);
}

Circle::Circle(Point2D _pos, int r, int g, int b, int a, int _radius, int res)
	:Shape(_pos, r, g, b, a), radius(_radius)
{
	if (0 < res && res <= 100)
		resolution = res;
	else
		resolution = 10;
};

void Circle::render(SDL_Renderer* rend)
{
	//prints info in console
	cout << "Circle: position: " << pos.toString() << " radius: " << radius << endl;

	//set color
	SDL_SetRenderDrawColor(rend, col[0], col[1], col[2], col[3]);

	//declare points for drawing
	Point2D center = Point2D(pos.x + radius, pos.y + radius);
	Point2D current= Point2D(pos.x +2* radius, pos.y + radius);;
	Point2D next;

	//set points & draw lines between them for a full revolution
	//the condition: 2 times pi for a complete revolution, the increment to i is added to fill the gap. 
	for (float i = 0; i < 2 * M_PI + 1. / resolution; i+= 1. / resolution)
	{
		//sets the next point to draw to
		next.x = center.x + radius * cos(i);
		next.y = center.y + radius * sin(i);
		//draws line from current point to next point
		SDL_RenderDrawLine(rend, current.x, current.y, next.x, next.y);
		//sets current point to next point
		current = next;
	}
	

}
