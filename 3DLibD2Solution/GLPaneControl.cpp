#include "GLPaneControl.h"
#include <gtc/matrix_transform.hpp>;
#include <iomanip>

GLPaneControl::GLPaneControl(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
    m_frameCnt(0),
    m_tStart(std::chrono::system_clock::now()),
    m_angle(0.f)
{
    m_pContext = new wxGLContext(this);
    wxGLCanvas::SetCurrent(*m_pContext);

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
    
    glewExperimental = GL_TRUE;
    glewInit();
    oglInitialize();

    //SetBackgroundStyle(wxBG_STYLE_PAINT);
    std::cout << std::fixed << std::setprecision(2);

    m_fPosX = 0.0f;		// X position of model in camera view
    m_fPosY = 0.0f;		// Y position of model in camera view
    m_fZoom = 45.0f;	// Zoom on model in camera view
    m_fRotX = 45.05f;		// Rotation on model in camera view
    m_fRotY = -10.05f;		// Rotation on model in camera view
    m_bIsMaximized = false;

    m_openGLRenderer.init();
}

void GLPaneControl::oglInitialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 

    createConus(1, 3, 5, vec3(0.25, 0.5, 0.5), 16, vec3(0, 0, 0), vec3(0, 0, 0));
}

void GLPaneControl::oglDrawScene(void)
{
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -m_fZoom);
    glTranslatef(m_fPosX, m_fPosY, 0.0f);
    glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
    glEnable(GL_BLEND);
    m_openGLRenderer.render(); 
}

void GLPaneControl::createConus(float topR, float botR, float height, vec3 color, int dotNumber, vec3 angle, vec3 center)
{
    Shape* conus = new Conus(height, topR, botR, dotNumber, color, angle, center);
    m_openGLRenderer.shapes.push_back(conus);
    m_openGLRenderer.newAdded = true;
}

void GLPaneControl::createPyramid(float side, float height, vec3 color, vec3 angle, vec3 center)
{
    Shape* pyramid = new Pyramid(side, height, color, angle, center);
    m_openGLRenderer.shapes.push_back(pyramid);
    m_openGLRenderer.newAdded = true;
}

void GLPaneControl::createCuboid(float length, float breadth, float height, vec3 color, vec3 angle, vec3 center)
{
    Shape* cuboid = new Cuboid(length, breadth, height, color, angle, center);
    m_openGLRenderer.shapes.push_back(cuboid);
    m_openGLRenderer.newAdded = true;
}

void GLPaneControl::onPaint(wxPaintEvent& evt)
{
    //ValidateRect();
    if ( IsShown() ) {
        wxPaintDC(this);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        oglDrawScene();
        glFlush();
        SwapBuffers();
        m_frameCnt++;
        std::cout << '\r' << estimateFPS(m_tStart, m_frameCnt) << " FPS";
    }
}

void GLPaneControl::onSize(wxSizeEvent& evt)
{
    m_openGLRenderer.windowHeight = getHeight();
    m_openGLRenderer.windowWidth = getWidth();
    glViewport(0, 0, (GLsizei)getWidth(), (GLsizei)getHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set our current view perspective
    gluPerspective(45.0f, (float)evt.GetSize().x / (float)evt.GetSize().y, 0.01f, 2000.0f);
    glScalef(0.01, 0.01, 0.01);
    glMatrixMode(GL_MODELVIEW);
    Refresh();
}

void GLPaneControl::onMouseMove(wxMouseEvent& evt)
{
    wxPoint point = evt.GetPosition();
    int diffX = (int)(point.x - m_fLastX);
    int diffY = (int)(point.y - m_fLastY);
    m_fLastX = (float)point.x;
    m_fLastY = (float)point.y;
    static wxPoint prev = point;
    bool picking = false;
    std::string res = m_openGLRenderer.pickRects(point.x, point.y);
    //cout << "move x=> " << point.x << " = y=> " << point.y << endl;
    // Left mouse button
    if (evt.LeftIsDown() && evt.ControlDown())
    {
        m_fPosX += (float)0.05f * diffX;
        m_fPosY -= (float)0.05f * diffY;
    }
    else if (evt.LeftIsDown())
    {
        //cout << "Left Down " << endl;
        for (auto& i : m_openGLRenderer.shapes)
        {
            if (i->marked)
            {
                vec3 lastCenter = i->getCenter();
                lastCenter.x += (float)0.05f * diffX;
                lastCenter.y -= (float)0.05f * diffY;

                i->changeCenter(lastCenter);
                picking = true;

            }
        }

        if (!picking) {
            m_fRotX += (float)0.5f * diffY;

            if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
            {
                m_fRotX = 0.0f;
            }

            m_fRotY += (float)0.5f * diffX;

            if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
            {
                m_fRotY = 0.0f;
            }
        }
        picking = false;
    }

    // Right mouse button
    else if (evt.RightIsDown())
    {
        m_fZoom -= (float)0.1f * diffY;
        //cout << "Right Down " << endl;
    }
    

    //OnDraw(NULL);

    //CWnd::OnMouseMove(nFlags, point);
    prev = point;
}

void GLPaneControl::onLeftButtonDown(wxMouseEvent& evt)
{
    SetFocus();
    if (m_openGLRenderer.pickMode) {
        m_openGLRenderer.m_pick = true;
        m_openGLRenderer.m_mouseX = evt.GetX();
        m_openGLRenderer.m_mouseY = evt.GetY();
        cout << "mpick = > " << m_openGLRenderer.m_pick;
        cout << " | mouseX => " << m_openGLRenderer.m_mouseX;
        cout << " | mouseY => " << m_openGLRenderer.m_mouseY << endl;
    }
    else
        m_openGLRenderer.m_pick = false;
}

void GLPaneControl::onKeyDown(wxKeyEvent& evt)
{
    if (evt.GetKeyCode() == 'K') {
        cout << "Pick Mode" << endl;
        m_openGLRenderer.pickMode = true;
        m_openGLRenderer.viewMode = false;
        // set default camera view to avoid problems with moving objects
        m_fPosX = 0.0f;		// X position of model in camera view
        m_fPosY = 0.0f;		// Y position of model in camera view
        m_fZoom = 45.0f;	// Zoom on model in camera view
        m_fRotX = 45.05f;		// Rotation on model in camera view
        m_fRotY = -10.05f;		// Rotation on model in camera view
    }
    /*else if (evt.GetKeyCode() == 'S') {
        boolean picking = false;
        int pickerer = -1;
        int j = 0;
        cout << "mpick = > " << m_openGLRenderer.m_pick;
        cout << " | mouseX => " << m_openGLRenderer.m_mouseX;
        cout << " | mouseY => " << m_openGLRenderer.m_mouseY << endl;
        for (auto& i : m_openGLRenderer.shapes)
        {
            j++;
            if (i->marked)
            {
                picking = true;
                pickerer = j;
            }
        }
        cout << "isAnythingPicked? => " << pickerer << "\n";
    }*/
}

GLPaneControl::~GLPaneControl()
{
    delete m_pContext;
}


int GLPaneControl::getWidth()
{
    return GetSize().x;
}

int GLPaneControl::getHeight()
{
    return GetSize().y;
}

double GLPaneControl::estimateFPS(std::chrono::time_point<std::chrono::system_clock>& start, int& cnt)
{
    auto tEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = tEnd - start;
    if (elapsedSeconds.count() >= 1.0) {
        start = std::chrono::system_clock::now();
        cnt = 0;
    }
    return cnt / elapsedSeconds.count();
}


BEGIN_EVENT_TABLE(GLPaneControl, wxGLCanvas)
EVT_PAINT(GLPaneControl::onPaint)
EVT_SIZE(GLPaneControl::onSize)
EVT_MOTION(GLPaneControl::onMouseMove)
EVT_LEFT_DOWN(GLPaneControl::onLeftButtonDown)
EVT_KEY_DOWN(GLPaneControl::onKeyDown)
END_EVENT_TABLE()