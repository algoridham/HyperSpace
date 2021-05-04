#pragma once
#include <vector>
#include <gl\GLU.h>
#include <glm.hpp>
#include "Shape.h"
const float PI = 3.141592654f;
using namespace glm;
using namespace std;

class Disk : public Shape {
private:
	float _radius;
	int _numDots;
public:
	Disk(float r, int numDots, vec3 move, vec3 color) : _radius(r), _numDots(numDots) {
		this->colour = color;
		verteces.push_back(vec3(0 + move.x, 0 + move.y, 0 + move.z));
		for (int i(0); i < numDots; i++) {
			verteces.push_back(vec3(cos(i * 2 * PI / numDots) * r + move.x, 0 + move.y, sin(i * 2 * PI / numDots) * r + move.z));
		}

		for (int i(1); i < numDots + 1; i++) {
			vertecesTriangles.push_back(verteces[0]);
			vertecesTriangles.push_back(verteces[i]);
			if (i + 1 < numDots + 1) {
				vertecesTriangles.push_back(verteces[(i + 1)]);
				normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[i], verteces[(i + 1)]));
			}
			else {
				vertecesTriangles.push_back(verteces[1]);
				normalsTriangles.push_back(calculateTriangleNormal(verteces[0], verteces[i], verteces[1]));
			}
		}
	}

	void draw(vec3 angle, vec3 newScale) {
		drawTriangles(angle, newScale);
	}

	char* type() { return (char*)("Disk"); }
};
