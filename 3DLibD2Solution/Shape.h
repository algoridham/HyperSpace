#pragma once
#include <vector>
#include <glew.h>
#include <glm.hpp>
#include <windows.h>
#include <gl/GLU.h>

using namespace glm;
using namespace std;

class Shape
{
protected:
	vec3 center;

	enum types { eConus, ePyramid, eCuboid};
	vector<vec3> verteces;
	vector<vec3> vertecesTriangles;
	vector<vec3> vertecesQuads;
	vector<vec3> normalsTriangles;
	vector<vec3> normalsQuads;

	GLuint getID() {
		static GLuint curID = -1;
		curID++;
		return curID;
	}
public:
	GLuint ID;
	vec3 colour;
	bool marked;
	vec3 angleRotation;
	vec3 currentScale;
	vec3 minScale;
	vec3 spawnScale;
	types shapeType;

	bool isConus() {
		if (shapeType == eConus)
			return true;
		return false;
	}

	bool isPyramid() {
		if (shapeType == ePyramid)
			return true;
		return false;
	}

	bool isCuboid() {
		if (shapeType == eCuboid)
			return true;
		return false;
	}

	vec3 getCenter() {
		return center;
	}

	vec3 getAngleRotation() {
		return angleRotation;
	}

	vector<vec3> getVerteces() {
		return verteces;
	}

	void changeCenter(vec3 c) {
		center = c;
	}

	vector<vec3> getVTriangles() {
		return vertecesTriangles;
	}

	vector<vec3> getVQuads() {
		return vertecesQuads;
	}

	vector<vec3> getNormalsTriangles() {
		return normalsTriangles;
	}

	vector<vec3> getNormalsQuads() {
		return normalsQuads;
	}

	vec3 getColor() {
		return colour;
	}

	virtual float getTopRadius() { return 0; }
	virtual float getBotRadius() { return 0; }
	virtual float getHeight() { return 0; }
	virtual int getNumber() { return 0; }
	virtual int getDotNumber() { return 0; }
	virtual float getSideLength() { return 0; }
	virtual float getLength() { return 0; }
	virtual float getBreadth() { return 0;  }

	Shape()
		: center(0, 0, 0),
		//colour(0.3, 0.3, 0.3),
		colour(0.0, 0.0, 0.5),
		currentScale(1, 1, 1),
		minScale(1, 1, 1),
		marked(false)
	{
		ID = getID();
	}
	virtual ~Shape() {};

	virtual char* type() = 0;

	virtual void drawTriangles(vec3 angle, vec3 newScale)
	{
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glTranslatef(center.x, center.y, center.z);

		glBegin(GL_TRIANGLES);

		for (auto i(0), j(0); i < vertecesTriangles.size(); i += 3, j++)
		{
			vec3 support = normalsTriangles[j];
			support = rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glNormal3f(support.x, support.y, support.z);

			support = vertecesTriangles[i];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);

			support = vertecesTriangles[i + 1];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);

			support = vertecesTriangles[i + 2];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);
		}
		glEnd();
		glPopMatrix();

		if (marked) {
			//glLineWidth(2);
			glPushMatrix();
			glTranslatef(center.x, center.y, center.z);
			glBegin(GL_LINE_STRIP);
			glColor3f(1, 0, 0);
			vec3 markScale = newScale + vec3(0.1, 0.1, 0.1);
			for (auto i(0), j(0); i < vertecesTriangles.size(); i += 3, j++)
			{
				vec3 support = normalsTriangles[j];
				support = rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glNormal3f(support.x, support.y, support.z);

				support = vertecesTriangles[i];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);

				support = vertecesTriangles[i + 1];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);

				support = vertecesTriangles[i + 2];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);
			}
			glEnd();
			glPopMatrix();
		}
	}

	virtual void draw(vec3 angle, vec3 scale) {

	}

	virtual void drawRect(vec3 angle, vec3 newScale) {
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glTranslatef(center.x, center.y, center.z);
		if (marked)
			glColor4f(colour.x, colour.y, colour.z, 1.0f);


		glBegin(GL_QUADS);
		for (auto i(0), j(0); i < vertecesQuads.size(); i += 4, j++)
		{
			vec3 support = normalsQuads[j];
			support = rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glNormal3f(support.x, support.y, support.z);

			support = vertecesQuads[i];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);

			support = vertecesQuads[i + 1];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);

			support = vertecesQuads[i + 2];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);

			support = vertecesQuads[i + 3];
			support = scale(newScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
			glVertex3f(support.x, support.y, support.z);
		}
		glEnd();
		glPopMatrix();

		if (marked) {
			//glLineWidth(2);
			glPushMatrix();
			glTranslatef(center.x, center.y, center.z);
			glColor3f(1, 0, 0);
			vec3 markScale = newScale + vec3(0.1, 0.1, 0.1);
			glBegin(GL_LINE_STRIP);
			for (auto i(0), j(0); i < vertecesQuads.size(); i += 4, j++)
			{

				vec3 support = normalsQuads[j];
				support = rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glNormal3f(support.x, support.y, support.z);

				support = vertecesQuads[i];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);

				support = vertecesQuads[i + 1];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);

				support = vertecesQuads[i + 2];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);

				support = vertecesQuads[i + 3];
				support = scale(markScale) * rotateX(angle.x) * rotateY(angle.y) * rotateZ(angle.z) * support;
				glVertex3f(support.x, support.y, support.z);
			}
			glEnd();
			glPopMatrix();
		}
	}


	mat3 rotateX(float angle)
	{
		mat3 rotate(1, 0, 0,
			0, cos(angle), -sin(angle),
			0, sin(angle), cos(angle));
		return rotate;
	}

	mat3 rotateY(float angle)
	{
		mat3 rotate(cos(angle), 0, sin(angle),
			0, 1, 0,
			-sin(angle), 0, cos(angle));
		return rotate;

	}

	mat3 rotateZ(float angle)
	{
		mat3 rotate(cos(angle), -sin(angle), 0,
			sin(angle), cos(angle), 0,
			0, 0, 1);
		return rotate;
	}


	mat3 scale(vec3 nscale)
	{
		mat3 scale(nscale.x, 0, 0,
			0, nscale.y, 0,
			0, 0, nscale.z);

		return scale;
	}


	void move(float x, float y, float z)
	{
		center.x += x;
		center.y += y;
		center.z += z;
	}

	vec3 calculateTriangleNormal(vec3 a, vec3 b, vec3 c) {
		vec3 first(b.x - a.x, b.y - a.y, b.z - a.z);
		vec3 second(c.x - a.x, c.y - a.y, c.z - a.z);
		vec3 normal((first.y * second.z) - (first.z * second.y),
			(first.z * second.x) - (first.x * second.z),
			(first.x * second.y) - (first.y * second.x));
		float l = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= l;
		normal.y /= l;
		normal.z /= l;
		return normal;
	}

};

