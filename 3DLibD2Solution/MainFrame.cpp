#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title) :
    wxFrame(parent, id, title)
{
    setFrameDimensions();
    preparePanes();
    prepareMenus();
}

MainFrame::~MainFrame()
{
    delete m_pGlPaneControl;
}

void MainFrame::preparePanes()
{
    SetBackgroundColour(wxColour(220, 220, 220));
    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* actionBarSizer = new wxBoxSizer(wxVERTICAL);

    m_pGlPaneControl = new GLPaneControl((wxFrame*)this, args);
    sizer->Add(m_pGlPaneControl, 1, wxEXPAND);

    actionBarSizer->AddSpacer(15);
    wxArrayString modes;
    modes.Add(wxString("View"));
    modes.Add(wxString("Edit"));
    m_pModePicker = new wxRadioBox((wxFrame*)this, 112, wxString("Choose Canvas Mode"), wxPoint(30, -1), wxSize(200, -1), modes);
    Connect(112, wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MainFrame::onModeSelect));
    actionBarSizer->Add(m_pModePicker, 0, wxALIGN_CENTER_HORIZONTAL);

    m_pClearSelection = new wxButton((wxFrame*)this, 118, "Clear Selection", wxDefaultPosition, wxSize(150, -1));
    Connect(118, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::onClearSelection));
    actionBarSizer->AddSpacer(10);
    actionBarSizer->Add(m_pClearSelection, 0, wxALIGN_CENTER_HORIZONTAL);

    wxArrayString shapes;
    shapes.Add(wxString("Cuboid"));
    shapes.Add(wxString("Pyramid"));
    shapes.Add(wxString("Cone"));
    m_pShapePicker = new wxRadioBox((wxFrame*)this, 110, wxString("Choose Shape To Add"), wxPoint(30, -1), wxSize(200, -1), shapes);
    actionBarSizer->AddSpacer(30);
    actionBarSizer->Add(m_pShapePicker, 0, wxALIGN_CENTER_HORIZONTAL);

    m_pColorPicker = new ColorPicker(this, wxID_ANY, wxDefaultPosition, wxSize(240, -1));
    actionBarSizer->AddSpacer(10);
    actionBarSizer->Add(m_pColorPicker);    

    m_pAddShape = new wxButton((wxFrame*)this, 114, "Add Shape", wxDefaultPosition, wxSize(150, -1));
    Connect(114, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::onAddShape));
    actionBarSizer->AddSpacer(10);
    actionBarSizer->Add(m_pAddShape, 0, wxALIGN_CENTER_HORIZONTAL);

    actionBarSizer->AddSpacer(30);
    
    wxBoxSizer* xRotate = new wxBoxSizer(wxHORIZONTAL);
    xRotate->AddSpacer(20);
    xRotate->Add(new wxStaticText(this, wxID_ANY, "Rotate X"), 0, wxALIGN_CENTER_VERTICAL);
    xRotate->AddSpacer(20);
    m_pXRotate = new wxSlider((wxFrame*)this, 121, 0, 0, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(121, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onRotateX));
    xRotate->Add(m_pXRotate);
    actionBarSizer->Add(xRotate);

    wxBoxSizer* yRotate = new wxBoxSizer(wxHORIZONTAL);
    yRotate->AddSpacer(20);
    yRotate->Add(new wxStaticText(this, wxID_ANY, "Rotate Y"), 0, wxALIGN_CENTER_VERTICAL);
    yRotate->AddSpacer(20);
    m_pYRotate = new wxSlider((wxFrame*)this, 122, 0, 0, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(122, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onRotateY));
    yRotate->Add(m_pYRotate);
    actionBarSizer->Add(yRotate);

    wxBoxSizer* zRotate = new wxBoxSizer(wxHORIZONTAL);
    zRotate->AddSpacer(20);
    zRotate->Add(new wxStaticText(this, wxID_ANY, "Rotate Z"), 0, wxALIGN_CENTER_VERTICAL);
    zRotate->AddSpacer(20);
    m_pZRotate = new wxSlider((wxFrame*)this, 123, 0, 0, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(123, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onRotateZ));
    zRotate->Add(m_pZRotate);
    actionBarSizer->Add(zRotate);

    actionBarSizer->AddSpacer(30);

    wxBoxSizer* Scale = new wxBoxSizer(wxHORIZONTAL);
    Scale->AddSpacer(20);
    Scale->Add(new wxStaticText(this, wxID_ANY, "Scale"), 0, wxALIGN_CENTER_VERTICAL);
    Scale->AddSpacer(30);
    m_pScale = new wxSlider((wxFrame*)this, 124, 10, 2, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(124, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onScale));
    Scale->Add(m_pScale);
    actionBarSizer->Add(Scale);

    wxBoxSizer* xScale = new wxBoxSizer(wxHORIZONTAL);
    xScale->AddSpacer(20);
    xScale->Add(new wxStaticText(this, wxID_ANY, "Scale X"), 0, wxALIGN_CENTER_VERTICAL);
    xScale->AddSpacer(20);
    m_pXScale = new wxSlider((wxFrame*)this, 125, 10, 2, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(125, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onScaleX));
    xScale->Add(m_pXScale);
    actionBarSizer->Add(xScale);

    wxBoxSizer* yScale = new wxBoxSizer(wxHORIZONTAL);
    yScale->AddSpacer(20);
    yScale->Add(new wxStaticText(this, wxID_ANY, "Scale Y"), 0, wxALIGN_CENTER_VERTICAL);
    yScale->AddSpacer(20);
    m_pYScale = new wxSlider((wxFrame*)this, 126, 10, 2, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(126, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onScaleY));
    yScale->Add(m_pYScale);
    actionBarSizer->Add(yScale);

    wxBoxSizer* zScale = new wxBoxSizer(wxHORIZONTAL);
    zScale->AddSpacer(20);
    zScale->Add(new wxStaticText(this, wxID_ANY, "Scale Z"), 0, wxALIGN_CENTER_VERTICAL);
    zScale->AddSpacer(20);
    m_pZScale = new wxSlider((wxFrame*)this, 127, 10, 2, 100, wxDefaultPosition, wxSize(150, -1));
    Connect(127, wxEVT_SLIDER, wxScrollEventHandler(MainFrame::onScaleZ));
    zScale->Add(m_pZScale);
    actionBarSizer->Add(zScale);


    sizer->Add(actionBarSizer, 0, wxEXPAND);

    SetSizer(sizer);
    SetAutoLayout(true);
}

void MainFrame::prepareMenus()
{
    m_pMenuBar = new wxMenuBar();
    m_pFileMenu = new wxMenu();
    m_pFileMenu->Append(wxID_SAVE, wxT("&Save"));
    m_pFileMenu->Append(wxID_ADD, wxT("&Load"));
    m_pFileMenu->Append(wxID_EXIT, wxT("&Exit"));
    Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnSave));
    Connect(wxID_ADD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnLoad));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));
    m_pMenuBar->Append(m_pFileMenu, wxT("&File"));
    SetMenuBar(m_pMenuBar);
}

void MainFrame::setFrameDimensions()
{
    int scrWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int scrHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
    constexpr int frmWidth = 800;
    constexpr int frmHeight = 700;
    SetSize((scrWidth - frmWidth) / 2, (scrHeight - frmHeight) / 2, frmWidth, frmHeight);
}

void MainFrame::onModeSelect(wxCommandEvent& evt)
{
    if (evt.GetSelection() == 0) {
        //ViewMode
        m_pGlPaneControl->m_openGLRenderer.pickMode = false;
        m_pGlPaneControl->m_openGLRenderer.viewMode = true;
    }
    else if (evt.GetSelection() == 1) {
        //EditMode
        m_pGlPaneControl->m_openGLRenderer.pickMode = true;
        m_pGlPaneControl->m_openGLRenderer.viewMode = false;
        // set default camera view to avoid problems with moving objects
        m_pGlPaneControl->m_fPosX = 0.0f;		// X position of model in camera view
        m_pGlPaneControl->m_fPosY = 0.0f;		// Y position of model in camera view
        m_pGlPaneControl->m_fZoom = 45.0f;	// Zoom on model in camera view
        m_pGlPaneControl->m_fRotX = 45.05f;		// Rotation on model in camera view
        m_pGlPaneControl->m_fRotY = -10.05f;		// Rotation on model in camera view
        m_pGlPaneControl->m_bIsMaximized = false;
    }
}

void MainFrame::onAddShape(wxCommandEvent& evt)
{
    int selection = m_pShapePicker->GetSelection();
    vec3 currentColor((float)(m_pColorPicker->rValue)/255, (float)m_pColorPicker->gValue/255, (float)m_pColorPicker->bValue/255);
    if (selection == 0) {
        //Cuboid
        m_pGlPaneControl->createCuboid(5, 5, 5, currentColor, vec3(0, 0, 0), vec3(0, 0, 0));
    }
    else if (selection == 1) {
        //Pyramid    
        m_pGlPaneControl->createPyramid(7, 7, currentColor, vec3(0, 0, 0), vec3(0, 0, 0));
    }
    else if (selection == 2) {
        //Cone
        m_pGlPaneControl->createConus(1, 3, 5, currentColor, 16, vec3(0, 0, 0), vec3(0, 0, 0));
    }
}

void MainFrame::onClearSelection(wxCommandEvent& evt)
{
    m_pGlPaneControl->m_openGLRenderer.clearSelection();
}

void MainFrame::onRotateX(wxScrollEvent& evt)
{
    int value = evt.GetInt();
    m_pGlPaneControl->m_openGLRenderer.incrementRotX = (float)value * 0.001;
}

void MainFrame::onRotateY(wxScrollEvent& evt)
{
    int value = evt.GetInt();
    m_pGlPaneControl->m_openGLRenderer.incrementRotY = (float)value * 0.001;
}

void MainFrame::onRotateZ(wxScrollEvent& evt)
{
    int value = evt.GetInt();
    m_pGlPaneControl->m_openGLRenderer.incrementRotZ = (float)value * 0.001;
}

void MainFrame::onScale(wxScrollEvent& evt)
{
    static float prev = 2;
    int value = evt.GetInt();
    float cof = value * 0.1;
    for (auto i : m_pGlPaneControl->m_openGLRenderer.shapes) {
        if (i->marked) {
            vec3 smp(1, 1, 1);
            i->currentScale += smp * (float)(cof - prev);
        }
    }
    prev = value * 0.1;
}

void MainFrame::onScaleX(wxScrollEvent& evt)
{
    static float prevX = 2;
    int value = evt.GetInt();
    float cof = value * 0.1;
    for (auto i : m_pGlPaneControl->m_openGLRenderer.shapes) {
        if (i->marked) {
            vec3 smp(1, 0, 0);
            i->currentScale += smp * (float)(cof - prevX);
        }
    }
    prevX = value * 0.1;
}

void MainFrame::onScaleY(wxScrollEvent& evt)
{
    static float prevY = 2;
    int value = evt.GetInt();
    float cof = value * 0.1;
    for (auto i : m_pGlPaneControl->m_openGLRenderer.shapes) {
        if (i->marked) {
            vec3 smp(0, 1, 0);
            i->currentScale += smp * (float)(cof - prevY);
        }
    }
    prevY = value * 0.1;
}

void MainFrame::onScaleZ(wxScrollEvent& evt)
{
    static float prevZ = 2;
    int value = evt.GetInt();
    float cof = value * 0.1;
    for (auto i : m_pGlPaneControl->m_openGLRenderer.shapes) {
        if (i->marked) {
            vec3 smp(0, 0, 1);
            i->currentScale += smp * (float)(cof - prevZ);
        }
    }
    prevZ = value * 0.1;
}

void MainFrame::OnQuit(wxCommandEvent& evt)
{
    Close(true);
}

void MainFrame::OnSave(wxCommandEvent& evt)
{
    wxFileDialog saveFileDialog(this, _("Save rbva model file"), "", "", "RBVA files (*.rbva)|*.rbva", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }
    wxFile* file(output_stream.GetFile());
    file->Write(m_pGlPaneControl->m_openGLRenderer.sData());
}

void MainFrame::OnLoad(wxCommandEvent& evt)
{
    wxFileDialog loadFileDialog(this, _("Load rbva model file"), "", "", "RBVA files (*.rbva)|*.rbva", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
        return;
    wxFileInputStream input_stream(loadFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", loadFileDialog.GetPath());
        return;
    }
    wxFile* file(input_stream.GetFile());
    wxString* text = new wxString("empty");
    file->ReadAll(text);
    m_pGlPaneControl->m_openGLRenderer.loadData(string(text->mb_str()));
    // set default camera view to avoid problems with moving objects
    m_pGlPaneControl->m_fPosX = 0.0f;		// X position of model in camera view
    m_pGlPaneControl->m_fPosY = 0.0f;		// Y position of model in camera view
    m_pGlPaneControl->m_fZoom = 45.0f;	// Zoom on model in camera view
    m_pGlPaneControl->m_fRotX = 45.05f;		// Rotation on model in camera view
    m_pGlPaneControl->m_fRotY = -10.05f;		// Rotation on model in camera view
    m_pGlPaneControl->m_bIsMaximized = false;
}

void MainFrame::updateGLPane()
{
    m_pGlPaneControl->Refresh();
}


