#pragma once
#include <vector>
#include <windows.h>
#include <gl\GLU.h>
#include <glm.hpp>
#include "Shape.h"
using namespace glm;
using namespace std;


class Grid : public Shape
{
public:
	char* type() { return (char*)("Grid"); }
	void draw()
	{
		static const int gridRes = 20;
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_LIGHTING);

		glPushMatrix();
		glTranslatef(center.x, center.y, center.z);

		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		glVertex3f(0, -20000, 0);
		glVertex3f(0, 20000, 0);
		glColor3f(0.2f, 0.2f, 0.2f);

		for (int i = -gridRes; i <= gridRes; i++)
		{
			if (i == 0) {
				glColor3f(1, 0, 0);
				glVertex3f(-20000, 0, 0);
				glVertex3f(20000, 0, 0);
				glColor3f(0, 0, 1);
				glVertex3f(0, 0, -20000);
				glVertex3f(0, 0, 20000);
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else {
				glVertex3f(-gridRes, 0, i);
				glVertex3f(gridRes, 0, i);
				glVertex3f(i, 0, -gridRes);
				glVertex3f(i, 0, gridRes);
			}
		}
		glEnd();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
};