#pragma once

#ifndef GL_PANE_CONTROL_H
#define GL_PANE_CONTROL_H

#include "GLPaneRenderer.h"

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <glm.hpp>
#include <chrono>

class GLPaneControl : public wxGLCanvas
{

public:
    float	 m_fLastX;
    float	 m_fLastY;
    float	 m_fPosX;
    float	 m_fPosY;
    float	 m_fZoom;
    float	 m_fRotX;
    float	 m_fRotY;
    bool	 m_bIsMaximized;

private:
    wxGLContext* m_pContext;
    int m_frameCnt;
    float m_angle;
    glm::mat4 m_proj;

    std::chrono::time_point<std::chrono::system_clock> m_tStart;
    double estimateFPS(std::chrono::time_point<std::chrono::system_clock>& start, int& cnt);

    void onPaint(wxPaintEvent& evt);
    void onSize(wxSizeEvent& evt);
    void onMouseMove(wxMouseEvent& evt);
    void onLeftButtonDown(wxMouseEvent& evt);
    void onKeyDown(wxKeyEvent& evt);

    DECLARE_EVENT_TABLE()

public:
    GLPaneControl(wxFrame* parent, int* args);
    virtual ~GLPaneControl();

    GLPaneRenderer m_openGLRenderer;

    void oglInitialize(void);
    void oglDrawScene(void);

    void createConus(float topR, float botR, float height, vec3 color, int dotNumber, vec3 angle, vec3 center);
    void createPyramid(float side, float height, vec3 color, vec3 angle, vec3 center);
    void createCuboid(float length, float breadth, float height, vec3 color, vec3 angle, vec3 center);

    int getWidth();
    int getHeight();

};

#endif // !GL_PANE_CONTROL_H