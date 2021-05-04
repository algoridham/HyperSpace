#pragma once
#include <vector>
#include <gl\GLU.h>
#include <glm.hpp>
#include "Shape.h"
#include "Disk.h"
using namespace glm;
using namespace std;

class Conus : public Shape {
private:
	float _height;
	float _topRadius;
	float _botRadius;
	int _dotNumber;
	Shape* top;
	Shape* bot;
public:
	Conus(float h, float topR, float botR, int dotNumber, vec3 color, vec3 angle, vec3 center) :_height(h), _topRadius(topR), _botRadius(botR), _dotNumber(dotNumber) {
		this->colour = color;
		this->shapeType = eConus;
		this->angleRotation = angle;
		this->center = center;
		top = new Disk(topR, dotNumber, vec3(0, h, 0), color);
		bot = new Disk(botR, dotNumber, vec3(0, 0, 0), color);


		verteces.reserve(top->getVerteces().size() + bot->getVerteces().size());
		for (int i(0); i < top->getVerteces().size(); i++) {
			verteces.push_back(top->getVerteces()[i]);
		}
		for (int i(0); i < bot->getVerteces().size(); i++) {
			verteces.push_back(bot->getVerteces()[i]);
		}
		vertecesTriangles.reserve(top->getVTriangles().size() + bot->getVTriangles().size());
		for (int i(0); i < top->getVTriangles().size(); i++) {
			vertecesTriangles.push_back(top->getVTriangles()[i]);
		}
		for (int i(0); i < bot->getVTriangles().size(); i++) {
			vertecesTriangles.push_back(bot->getVTriangles()[i]);
		}

		normalsTriangles.reserve(top->getNormalsTriangles().size() + bot->getNormalsTriangles().size());
		for (int i(0); i < top->getNormalsTriangles().size(); i++) {
			normalsTriangles.push_back(top->getNormalsTriangles()[i]);
		}
		for (int i(0); i < bot->getNormalsTriangles().size(); i++) {
			normalsTriangles.push_back(bot->getNormalsTriangles()[i]);
		}

		for (int i(2); i < _dotNumber + 2; i++) {
			if (i + 1 < _dotNumber + 2) {
				vertecesQuads.push_back(verteces[i - 1]);
				vertecesQuads.push_back(verteces[i]);
				vertecesQuads.push_back(verteces[_dotNumber + 1 + i]);
				vertecesQuads.push_back(verteces[_dotNumber + i]);
				normalsQuads.push_back(calculateTriangleNormal(verteces[i - 1], verteces[i], verteces[_dotNumber + i]));
			}
			else {
				vertecesQuads.push_back(verteces[i - 1]);
				vertecesQuads.push_back(verteces[1]);
				vertecesQuads.push_back(verteces[_dotNumber + 2]);
				vertecesQuads.push_back(verteces[_dotNumber + i]);
				normalsQuads.push_back(calculateTriangleNormal(verteces[i - 1], verteces[1], verteces[_dotNumber + i]));
			}
		}



		/*verteces.insert(verteces.end(), top->getVerteces().begin(), top->getVerteces().end());
		verteces.insert(verteces.end(), bot->getVerteces().begin(), bot->getVerteces().end());
		vertecesTriangles.insert(vertecesTriangles.end(), top->getVTriangles().begin(), top->getVTriangles().end());
		vertecesTriangles.insert(vertecesTriangles.end(), bot->getVTriangles().begin(), bot->getVTriangles().end());
		normalsTriangles.insert(normalsTriangles.end(), top->getNormalsTriangles().begin(), top->getNormalsTriangles().end());
		normalsTriangles.insert(normalsTriangles.end(), bot->getNormalsTriangles().begin(), bot->getNormalsTriangles().end());
		*/
	}

	float getTopRadius() {
		return _topRadius;
	}

	float getBotRadius() {
		return _botRadius;
	}

	float getHeight() {
		return _height;
	}

	int getDotNumber() {
		return _dotNumber;
	}

	void draw(vec3 angle, vec3 newScale) {
		drawTriangles(angle, newScale);
		drawRect(angle, newScale);
	}

	char* type() { return (char*)("Conus"); }
};