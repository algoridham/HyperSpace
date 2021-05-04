#pragma once

#ifndef APP_H
#define APP_H

#include "MainFrame.h"

class OpenGLApp : public wxApp
{
private:
    MainFrame* m_pFrame;
    bool m_isMinimized;

    virtual bool OnInit() override;
    void OnIdle(wxIdleEvent& evt);
    void prepareMainFrame();
};

#endif // !APP_H