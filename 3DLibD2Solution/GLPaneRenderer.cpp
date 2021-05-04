#pragma once
#include "GLPaneRenderer.h"
#include <wx\image.h>
#include "Skybox.h"
#define BUFSIZE 512 

void GLPaneRenderer::init(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLfloat light1_ambient[] = { 1.0f, 1.0f, 1.0f, 0.6f };
	GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_position[] = { 1.0f, 1.0f, 1.0f, 0.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_FLAT);
	glDepthRange(0.0, 1.0);
	isAxes = true;

	defaultAngle = vec3(0, 0, 0);
	defaultScale = vec3(1, 1, 1);
	m_pick = false;
	m_mouseX = 0;
	m_mouseY = 0;

	pickMode = false;
	viewMode = true;

	loadSkybox();
}

string GLPaneRenderer::processHits(GLint hits, GLuint buffer[], bool lbotton)
{
	string res;
	unsigned int i, j;
	GLuint names, * ptr;

	res += "   hits = " + to_string(hits);
	ptr = (GLuint*)buffer;
	if (!hits) {
		for (auto i : shapes)
			i->marked = false;
	}
	for (i = 0; i < hits; i++) { /* for each hit */
		names = *ptr;
		ptr += 3;
		res += " name: ";
		for (j = 0; j < names; j++) { /* for each name */
			for (auto i : shapes)
			{
				if (i->ID == *ptr) {
					if (lbotton) i->marked = true;
					else i->marked = false;
				}
			}
			res += to_string(*ptr);
			ptr++;
		}
	}
	return res;
}

string GLPaneRenderer::pickRects(int x, int y, bool lbotton)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	glSelectBuffer(BUFSIZE, selectBuf);
	(void)glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	for (auto i : shapes)
		i->draw(defaultAngle, i->currentScale);

	hits = glRenderMode(GL_RENDER);
	return processHits(hits, selectBuf, lbotton);
}

void GLPaneRenderer::render()
{
	currRotX = currRotX + incrementRotX;
	currRotY = currRotY + incrementRotY;
	currRotZ = currRotZ + incrementRotZ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	
	skybox();

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	if (isAxes)
		axes.draw();
	if (shapes.size() == 0)
		std::cout << "No objects";

	countMarked = 0;
	vec3 angle(currRotX, currRotY, currRotZ);
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->marked) {
			vec3 lastCenter = shapes[i]->getCenter();
			lastCenter.z += m_translationZ - m_lastTranslation;
			shapes[i]->changeCenter(lastCenter);
			countMarked++;
		}

		if (m_pick)
		{
			glDisable(GL_LIGHTING);
			glColor3ub(shapes[i]->ID, 0, 0);
			shapes[i]->draw(angle, shapes[i]->currentScale);
		}
		else {
			glColor3f(shapes[i]->colour.x, shapes[i]->colour.y, shapes[i]->colour.z);
			shapes[i]->draw(angle, shapes[i]->currentScale);
		}
	}

	m_lastTranslation = m_translationZ;


	if (viewMode) {
		for (auto i : shapes)
			i->marked = false;
	}

	if (m_pick) {
		unsigned char pixel[4];
		glReadPixels(m_mouseX, windowHeight - m_mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
		for (auto i : shapes)
		{
			if (i->ID == (int)pixel[0])
			{
				i->marked = true;
			}
		}
		m_pick = false;
	}
	glFlush();

}

string GLPaneRenderer::sData()
{
	string data("");
	data.append(to_string(shapes.size()));
	data.append(" ");
	for (auto i : shapes) {
		if (i->isConus()) {
			data.append("0 ");
			data.append(to_string(i->getBotRadius()));
			data.append(" ");
			data.append(to_string(i->getTopRadius()));
			data.append(" ");
			data.append(to_string(i->getDotNumber()));
			data.append(" ");
			data.append(to_string(i->getHeight()));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().x));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().y));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().z));
			data.append(" ");
			data.append(to_string(i->getCenter().x));
			data.append(" ");
			data.append(to_string(i->getCenter().y));
			data.append(" ");
			data.append(to_string(i->getCenter().z));
			data.append(" ");
			data.append(to_string(i->getColor().x));
			data.append(" ");
			data.append(to_string(i->getColor().y));
			data.append(" ");
			data.append(to_string(i->getColor().z));
			data.append(" ");
		}
		else if (i->isPyramid()) {
			data.append("1 ");
			data.append(to_string(i->getSideLength()));
			data.append(" ");
			data.append(to_string(i->getHeight()));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().x));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().y));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().z));
			data.append(" ");
			data.append(to_string(i->getCenter().x));
			data.append(" ");
			data.append(to_string(i->getCenter().y));
			data.append(" ");
			data.append(to_string(i->getCenter().z));
			data.append(" ");
			data.append(to_string(i->getColor().x));
			data.append(" ");
			data.append(to_string(i->getColor().y));
			data.append(" ");
			data.append(to_string(i->getColor().z));
			data.append(" ");
		}
		else {
			data.append("2 ");
			data.append(to_string(i->getLength()));
			data.append(" ");
			data.append(to_string(i->getBreadth()));
			data.append(" ");
			data.append(to_string(i->getHeight()));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().x));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().y));
			data.append(" ");
			data.append(to_string(i->getAngleRotation().z));
			data.append(" ");
			data.append(to_string(i->getCenter().x));
			data.append(" ");
			data.append(to_string(i->getCenter().y));
			data.append(" ");
			data.append(to_string(i->getCenter().z));
			data.append(" ");
			data.append(to_string(i->getColor().x));
			data.append(" ");
			data.append(to_string(i->getColor().y));
			data.append(" ");
			data.append(to_string(i->getColor().z));
			data.append(" ");
		}
	}
	return data;
}

void GLPaneRenderer::loadData(string data)
{
	cout << data << endl;
	vector<string> snip;
	init();
	shapes.clear();
	newAdded = true;
	render();
	size_t pos = 0;
	string token;
	string delimeter = " ";

	while ((pos = data.find(" ")) != std::string::npos) {
		token = data.substr(0, pos);
		snip.push_back(token);
		data.erase(0, pos + delimeter.size());
	}
	cout << "length => " << snip.size() << endl;
	int ctr = 1;
	for (int i = 1; i < snip.size(); i++) {
		cout << i << " || " << snip[i] << endl;
		if (atoi(snip[i].c_str()) == 0) {
			float botR = atof(snip[++i].c_str());
			float topR = atof(snip[++i].c_str());
			int dotNumber = atoi(snip[++i].c_str());
			float height = atof(snip[++i].c_str());
			vec3 angle = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i+=3;
			vec3 center = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i+=3;
			vec3 color = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i+=3;
			shapes.push_back(new Conus(height, topR, botR, dotNumber, color, angle, center));
			cout << "color => " << color.x << " - " << color.y << " - " << color.z << endl;
			cout << "Cone Added" << endl;
		}
		else if (atoi(snip[i].c_str()) == 1) {
			float sideLength = atof(snip[++i].c_str());
			float height = atof(snip[++i].c_str());
			vec3 angle = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			vec3 center = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			vec3 color = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			cout << "color => " << color.x << " - " << color.y << " - " << color.z << endl;
			shapes.push_back(new Pyramid(sideLength, height, color, angle, center));
			cout << "Pyramid Added" << endl;
		}
		else if (atoi(snip[i].c_str()) == 2){
			float length = atof(snip[++i].c_str());
			float breadth = atof(snip[++i].c_str());
			float height = atof(snip[++i].c_str());
			vec3 angle = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			vec3 center = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			vec3 color = vec3(atof(snip[i+1].c_str()), atof(snip[i+2].c_str()), atof(snip[i+3].c_str())); i += 3;
			cout << "color => " << color.x << " - " << color.y << " - " << color.z << endl;
			shapes.push_back(new Cuboid(length, breadth, height, color, angle, center));
			cout << "Cuboid Added" << endl;
		}
		else {
			i++;
		}
		newAdded = true;
		render();
	}
}

void GLPaneRenderer::deleteData()
{
}

void GLPaneRenderer::clearSelection()
{
	for (auto i : shapes)
	{
		i->marked = false;
	}
}

//void GLPaneRenderer::savedata()
//{
//	datatable.open();
//	datatable.canappend();
//	for (auto i : shapes) {
//		datatable.addnew();
//		if (i->isconus()) {
//			datatable.m_botradius = i->getbotradius();
//			datatable.m_topradius = i->gettopradius();
//			datatable.m_dotnumber = i->getdotnumber();
//			datatable.m_typeshape = 1;
//
//		}
//		else if (i->ispyramid()) {
//			datatable.m_side = i->getsidelength();
//			datatable.m_typeshape = 2;
//		}
//		datatable.m_height = i->getheight();
//		datatable.m_centerx = i->getcenter().x;
//		datatable.m_centery = i->getcenter().y;
//		datatable.m_centerz = i->getcenter().z;
//		datatable.m_colorb = i->getcolor().b;
//		datatable.m_colorr = i->getcolor().r;
//		datatable.m_colorg = i->getcolor().g;
//		datatable.m_anglex = i->getanglerotation().x;
//		datatable.m_angley = i->getanglerotation().y;
//		datatable.m_anglez = i->getanglerotation().z;
//		datatable.m_id++;
//		datatable.update();
//	}
//	datatable.close();
//}
//
//void GLPaneRenderer::loaddata()
//{
//	datatable.open();
//	while (!datatable.iseof()) {
//		if (datatable.m_typeshape == 1) {
//			shape* conus = new conus(datatable.m_height,
//				datatable.m_topradius,
//				datatable.m_botradius,
//				datatable.m_dotnumber,
//				vec3(datatable.m_colorr, datatable.m_colorg, datatable.m_colorb),
//				vec3(datatable.m_anglex, datatable.m_angley, datatable.m_anglez),
//				vec3(datatable.m_centerx, datatable.m_centery, datatable.m_centerz));
//			shapes.push_back(conus);
//		}
//		else if (datatable.m_typeshape == 2) {
//			shape* pyr = new pyramid(datatable.m_side,
//				datatable.m_height,
//				vec3(datatable.m_colorr, datatable.m_colorg, datatable.m_colorb),
//				vec3(datatable.m_anglex, datatable.m_angley, datatable.m_anglez),
//				vec3(datatable.m_centerx, datatable.m_centery, datatable.m_centerz));
//			shapes.push_back(pyr);
//		}
//		datatable.movenext();
//	}
//	datatable.close();
//}
//
//void GLPaneRenderer::deletedata()
//{
//	datatable.open();
//	while (!datatable.iseof()) {
//		datatable.delete();
//		datatable.movenext();
//	}
//	datatable.close();
//}

