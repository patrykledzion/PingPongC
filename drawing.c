#include "drawing.h"

void drawTriangle(Vector3_t c1, Vector3_t c2, Vector3_t c3, Color4_t color, window* window)
{

	long offsetX = (long)window->offsetX;
	long offsetY = (long)window->offsetY;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLES);
	glVertex3f(c1.x + offsetX, c1.y + offsetY, c1.z);
	glVertex3f(c2.x + offsetX, c2.y + offsetY, c2.z);
	glVertex3f(c3.x + offsetX, c3.y + offsetY, c3.z);
	glEnd();
}

void drawRect(long x, long y, long width, long height, Color4_t color, long depth, window* window)
{
	long offsetX = (long)window->offsetX;
	long offsetY = (long)window->offsetY;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_QUADS);
	glVertex3f(x + offsetX, y + offsetY, depth);
	glVertex3f(x + width + offsetX, y + offsetY, depth);
	glVertex3f(x + width + offsetX,y + height + offsetY, depth);
	glVertex3f(x + offsetX, y + height + offsetY, depth);
	glEnd();
}

void drawCircle(long x, long y, long r, int vCount, Color4_t color, long depth, window* window)
{
	long offsetX = (long)window->offsetX;
	long offsetY = (long)window->offsetY;

	float angle = 360.0 / (float)vCount;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_FAN); 
	for (int i = 0; i < vCount; i++)
	{
		float curr_angle = i * angle;
		long _x = r * cosf(i * 2.0*3.14 / vCount) + x;
		long _y = r * sinf(i * 2.0 * 3.14 / vCount) + y;
		long _z = depth; 
		glVertex3f(_x + offsetX, _y + offsetY, depth);
	}
  
	glEnd();

}

 