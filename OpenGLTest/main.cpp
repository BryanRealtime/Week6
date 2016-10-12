#include "draw.h"
#define ONE_OBJ 50
#define START_COORDINATES 100
using namespace std;

//predefinition of Methods
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawOnPixelBuffer();
void drawCircle(const int x, const int y, const int r, const int w, const float red, const float green, const float blue);



template<class T>
void print(T input)
{
	cout << input << endl;
}

template<class Vec>
class Vector2D
{
	Vec x_, y_;
};


class GeometricObjectInterface
{
public:
	virtual void setElements(int x, int y, int r, int w) {}
	virtual void draw() {}
};

template<class Shape>
class GeometricObject : public GeometricObjectInterface
{
	Shape object;
public:
	
	void setElements(int x, int y, int r, int w)
	{
		object.setElements(x,y,r,w);
	}

	void draw()
	{
		object.draw();
	}
};


class Box
{
private:
	int o_x, o_y, o_r, o_w;

public:
	void setElements(int x, int y, int r, int w)
	{
		o_x = x;
		o_y = y;
		o_r = r;
		o_w = w;
	}

	void draw()
	{
		setElements(100, 100, 150, 3);

		drawLine((o_x - (o_r / 2)), (o_y - (o_r / 2)), (o_x - (o_r / 2)), (o_y + (o_r / 2)), 1.0f, 0.0f, 0.0f);
		drawLine((o_x - (o_r / 2)), (o_y - (o_r / 2)), (o_x + (o_r / 2)), (o_y - (o_r / 2)), 1.0f, 0.0f, 0.0f);
		drawLine((o_x - (o_r / 2)), (o_y + (o_r / 2)), (o_x + (o_r / 2)), (o_y + (o_r / 2)), 1.0f, 0.0f, 0.0f);
		drawLine((o_x + (o_r / 2)), (o_y - (o_r / 2)), (o_x + (o_r / 2)), (o_y + (o_r / 2)), 1.0f, 0.0f, 0.0f);
	}

};

class Circle
{
private:
	int o_x, o_y, o_r, o_w;

public:
	void setElements(int x, int y, int r, int w)
	{
		o_x = x;
		o_y = y;
		o_r = r;
		o_w = w;
	}

	void draw()
	{
		setElements(400, 400, 60, 4);
		drawCircle(o_x, o_y, o_r, o_w, 0.0f, 0.0f, 1.0f);
	}
};



int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Week6 Templates", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	//Question 1 Part
	print(1);
	print(2.345f);
	print("Hello World");



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		drawOnPixelBuffer();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}



void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i1 == i0) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
	for (int i = i0; i <= i1; i++) {
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	fill_n(pixels, width*height * 3, 1.0f);	// white background

	//Question 3 Part
	vector<GeometricObjectInterface*> obj_list;
	obj_list.push_back(new GeometricObject<Circle>);
	obj_list.push_back(new GeometricObject<Box>);
	for (auto itr : obj_list)
	{
		itr->draw();
		/*for (int i = START_COORDINATES; i < START_COORDINATES+(12*ONE_OBJ); i += ONE_OBJ) 
		{
			itr->setElements(i,i,40,5);
			itr->draw();
		}*///This is used When you don't set the info(ex:x,y coordinates) of the Shape in each classes
	}
}

//w is the width of the circle'outer shell
void drawCircle(const int x, const int y, const int r, const int w, const float red, const float green, const float blue)
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{

			if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) <= r)
			{
				if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) >= r - w)
					drawPixel(a, b, red, green, blue);
			}
		}
	}
}
