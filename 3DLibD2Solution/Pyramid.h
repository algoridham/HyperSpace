#pragma once
#include <vector>
#include <gl\GLU.h>
#include <glm.hpp>
#include "Shape.h"
using namespace glm;
using namespace std;


class Pyramid : public Shape {
private:
	float _height;
	float _sideLength;
public:
	Pyramid(float a, float h, vec3 color, vec3 angle, vec3 center) :_height(h), _sideLength(a) {
		this->colour = color;
		this->shapeType = ePyramid;
		this->angleRotation = angle;
		this->center = center;
		verteces.resize(5);  // calculating verteces
		verteces[0] = vec3(0, h, 0);
		verteces[1] = vec3(a / 2, 0, a / 2);
		verteces[2] = vec3(-a / 2, 0, a / 2);
		verteces[3] = vec3(-a / 2, 0, -a / 2);
		verteces[4] = vec3(a / 2, 0, -a / 2);

		vertecesTriangles.push_back(verteces[0]);
		vertecesTriangles.push_back(verteces[1]);
		vertecesTriangles.push_back(verteces[2]);
		normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[1], verteces[2]));

		vertecesTriangles.push_back(verteces[0]);
		vertecesTriangles.push_back(verteces[2]);
		vertecesTriangles.push_back(verteces[3]);
		normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[2], verteces[3]));

		vertecesTriangles.push_back(verteces[0]);
		vertecesTriangles.push_back(verteces[3]);
		vertecesTriangles.push_back(verteces[4]);
		normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[3], verteces[4]));

		vertecesTriangles.push_back(verteces[0]);
		vertecesTriangles.push_back(verteces[4]);
		vertecesTriangles.push_back(verteces[1]);
		normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[4], verteces[1]));

		vertecesQuads.push_back(verteces[1]);
		vertecesQuads.push_back(verteces[2]);
		vertecesQuads.push_back(verteces[3]);
		vertecesQuads.push_back(verteces[4]);
		normalsQuads.push_back(vec3(0, -1, 0));
	}

	float getHeight() {
		return _height;
	}

	float getSideLength() {
		return _sideLength;
	}

	void draw(vec3 angle, vec3 newShape) {
		drawTriangles(angle, newShape);
		drawRect(angle, newShape);
	}

	char* type() { return (char*)("Pyramid"); }
};

