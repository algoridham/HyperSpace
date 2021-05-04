GLuint textureId;  //texture ID
#include "loadTGA.h"

void loadSkybox()
{
    glGenTextures(1, &textureId); 				// Create a Texture object
    glBindTexture(GL_TEXTURE_2D, textureId);		//Use the texture
    loadTGA("Sky2/skyrender0001.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void skybox()
{
    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0); //bottom floor
    glTexCoord2f(0.25, 0); glVertex3f(-10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.5, 0); glVertex3f(10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.5, 0.33); glVertex3f(10000.0, -10000.0, -10000.0);
    glTexCoord2f(0.25, 0.33); glVertex3f(-10000.0, -10000.0, -10000.0);

    glNormal3f(0.0, -1.0, 0.0); //top wall
    glTexCoord2f(0.25, 1); glVertex3f(-10000.0, 10000.0, 10000.0);
    glTexCoord2f(0.5, 1); glVertex3f(10000.0, 10000.0, 10000.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(10000.0, 10000.0, -10000.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-10000.0, 10000.0, -10000.0);

    glNormal3f(0.0, 0.0, 1.0); //front wall
    glTexCoord2f(0.25, 0.5); glVertex3f(-10000.0, -10000.0, -10000.0);
    glTexCoord2f(0.5, 0.5); glVertex3f(10000.0, -10000.0, -10000.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(10000.0, 10000.0, -10000.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-10000.0, 10000.0, -10000.0);

    glNormal3f(1.0, 0.0, 0.0); //left wall
    glTexCoord2f(0, 0.5); glVertex3f(-10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.25, 0.5); glVertex3f(-10000.0, -10000.0, -10000.0);
    glTexCoord2f(0.25, 0.66); glVertex3f(-10000.0, 10000.0, -10000.0);
    glTexCoord2f(0, 0.66); glVertex3f(-10000.0, 10000.0, 10000.0);

    glNormal3f(-1.0, 0.0, 0.0); //right wall
    glTexCoord2f(0.75, 0.5); glVertex3f(10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.5, 0.5); glVertex3f(10000.0, -10000.0, -10000.0);
    glTexCoord2f(0.5, 0.66); glVertex3f(10000.0, 10000.0, -10000.0);
    glTexCoord2f(0.75, 0.66); glVertex3f(10000.0, 10000.0, 10000.0);

    glNormal3f(0.0, 0.0, -1.0); //back wall
    glTexCoord2f(1, 0.5); glVertex3f(-10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.75, 0.5); glVertex3f(10000.0, -10000.0, 10000.0);
    glTexCoord2f(0.75, 0.66); glVertex3f(10000.0, 10000.0, 10000.0);
    glTexCoord2f(1, 0.66); glVertex3f(-10000.0, 10000.0, 10000.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}
