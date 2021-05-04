#pragma once
#include <vector>
#include <gl\GLU.h>
#include <glm.hpp>
#include "Shape.h"
using namespace glm;
using namespace std;


class Cuboid : public Shape {
private:
	float _length;
	float _breadth;
	float _height;
public:
	Cuboid(float l, float b, float h, vec3 color, vec3 angle, vec3 center) : _length(l), _breadth(b), _height(h) {
		this->colour = color;
		this->shapeType = eCuboid;
		this->angleRotation = angle;
		this->center = center;
		verteces.resize(8);  // calculating verteces
		verteces[0] = vec3(-l / 2, h, -b / 2);
		verteces[1] = vec3(-l / 2, h, b / 2);
		verteces[2] = vec3(l / 2, h, -b / 2);
		verteces[3] = vec3(l / 2, h, b / 2);
		verteces[4] = vec3(-l / 2, 0, -b / 2);
		verteces[5] = vec3(-l / 2, 0, b / 2);
		verteces[6] = vec3(l / 2, 0, -b / 2);
		verteces[7] = vec3(l / 2, 0, b / 2);

		vertecesQuads.push_back(verteces[0]);
		vertecesQuads.push_back(verteces[1]);
		vertecesQuads.push_back(verteces[3]);
		vertecesQuads.push_back(verteces[2]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[0], verteces[1], verteces[2]));


		vertecesQuads.push_back(verteces[4]);
		vertecesQuads.push_back(verteces[5]);
		vertecesQuads.push_back(verteces[7]);
		vertecesQuads.push_back(verteces[6]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[4], verteces[5], verteces[6]));


		vertecesQuads.push_back(verteces[0]);
		vertecesQuads.push_back(verteces[1]);
		vertecesQuads.push_back(verteces[5]);
		vertecesQuads.push_back(verteces[4]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[0], verteces[1], verteces[4]));


		vertecesQuads.push_back(verteces[2]);
		vertecesQuads.push_back(verteces[3]);
		vertecesQuads.push_back(verteces[7]);
		vertecesQuads.push_back(verteces[6]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[2], verteces[3], verteces[7]));


		vertecesQuads.push_back(verteces[0]);
		vertecesQuads.push_back(verteces[2]);
		vertecesQuads.push_back(verteces[6]);
		vertecesQuads.push_back(verteces[4]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[0], verteces[2], verteces[4]));


		vertecesQuads.push_back(verteces[1]);
		vertecesQuads.push_back(verteces[3]);
		vertecesQuads.push_back(verteces[7]);
		vertecesQuads.push_back(verteces[5]);
		normalsQuads.push_back(calculateTriangleNormal(verteces[1], verteces[3], verteces[5]));
	}

	float getHeight() {
		return _height;
	}

	float getBreadth() {
		return _breadth;
	}

	float getLength() {
		return _length;
	}

	void draw(vec3 angle, vec3 newShape) {
		drawTriangles(angle, newShape);
		drawRect(angle, newShape);
	}

	char* type() { return (char*)("Cuboid"); }
};

