#pragma once

#include <wx/wx.h>
#include <wx/slider.h>

class ColorHandler : public wxPanel
{
public:
	ColorHandler(wxFrame* parent, wxSize size);

	void onRedScroll(wxScrollEvent& event);
	void onBlueScroll(wxScrollEvent& event);

	wxSlider* redSlider;
	int red;
	wxSlider* blueSlider;
	int blue;
};

const int ID_RED = 100;
const int ID_BLUE = 101;
