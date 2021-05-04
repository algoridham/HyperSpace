#pragma once

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "GLPaneControl.h"
#include "ColorPicker.h"
#include <wx/wfstream.h>

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent, wxWindowID id, const wxString& title);
    ~MainFrame();

    void updateGLPane();

private:
    wxMenuBar* m_pMenuBar;
    wxMenu* m_pFileMenu;
    GLPaneControl* m_pGlPaneControl;
    ColorPicker* m_pColorPicker;
    wxRadioBox* m_pShapePicker;
    wxRadioBox* m_pModePicker;
    wxButton* m_pAddShape;
    wxButton* m_pClearSelection;
    wxSlider* m_pXRotate;
    wxSlider* m_pYRotate;
    wxSlider* m_pZRotate;
    wxSlider* m_pXScale;
    wxSlider* m_pYScale;
    wxSlider* m_pZScale;
    wxSlider* m_pScale;
    
    void preparePanes();
    void prepareMenus();
    void setFrameDimensions();
    void onModeSelect(wxCommandEvent& evt);
    void onAddShape(wxCommandEvent& evt);
    void onClearSelection(wxCommandEvent& evt);
    void onRotateX(wxScrollEvent& evt);
    void onRotateY(wxScrollEvent& evt);
    void onRotateZ(wxScrollEvent& evt);
    void onScale(wxScrollEvent& evt);
    void onScaleX(wxScrollEvent& evt);
    void onScaleY(wxScrollEvent& evt);
    void onScaleZ(wxScrollEvent& evt);
    void OnQuit(wxCommandEvent& evt);
    void OnSave(wxCommandEvent& evt);
    void OnLoad(wxCommandEvent& evt);
};

#endif // !MAIN_FRAME_H