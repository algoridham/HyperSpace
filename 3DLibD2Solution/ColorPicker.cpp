#include "ColorPicker.h"

ColorPicker::ColorPicker(wxWindow* parent, wxWindowID id, wxPoint point, wxSize size) :
	wxPanel(parent, id, point, size)
{
	std::cout << "here \n";
	rValue = 0;
	gValue = 0;
	bValue = 255;
	std::cout << "r => " << rValue << " g => " << gValue << " b => " << bValue << "\n";
	setSliders();
	setColorPicker();
	connectEvents();
}


ColorPicker::~ColorPicker()
{
}

void ColorPicker::setSliders()
{
	m_selectColor = new wxStaticText(this, wxID_ANY, "Select Colour", wxPoint(30, 10));

	m_redLabel = new wxStaticText(this, wxID_ANY, "Red", wxPoint(30, 45), wxSize(30, 20), wxTEXT_ALIGNMENT_LEFT);
	m_redSlider = new wxSlider(this, ID_RED_SLIDER, rValue, 0, 255, wxPoint(70, 40), wxSize(150, 20));
	
	m_greenLabel = new wxStaticText(this, wxID_ANY, "Green", wxPoint(30, 70), wxSize(30, 20), wxTEXT_ALIGNMENT_LEFT);
	m_greenSlider = new wxSlider(this, ID_GREEN_SLIDER, gValue, 0, 255, wxPoint(70, 65), wxSize(150, 20));
	
	m_blueLabel = new wxStaticText(this, wxID_ANY, "Blue", wxPoint(30, 95), wxSize(30, 20), wxTEXT_ALIGNMENT_LEFT);
	m_blueSlider = new wxSlider(this, ID_BLUE_SLIDER, bValue, 0, 255, wxPoint(70, 90), wxSize(150, 20));
}

void ColorPicker::setColorPicker()
{
	m_colorPicker = new wxColourPickerCtrl(this, ID_COLOR_PICKER, wxColour(0, 0, 255), wxPoint(120, 5));
}

void ColorPicker::setColorEditors()
{
}

void ColorPicker::connectEvents()
{
	Connect(ID_RED_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(ColorPicker::redSliderEvent));
	Connect(ID_GREEN_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(ColorPicker::greenSliderEvent));
	Connect(ID_BLUE_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(ColorPicker::blueSliderEvent));
	Connect(ID_COLOR_PICKER, wxEVT_COLOURPICKER_CHANGED, wxColourPickerEventHandler(ColorPicker::colorPickerEvent));
}

void ColorPicker::redSliderEvent(wxScrollEvent& event)
{
	rValue = m_redSlider->GetValue();
	//m_colorPicker->SetColour(wxColour(r, g, b, 0));
	m_colorPicker->SetColour(wxColor(rValue, gValue, bValue));
}

void ColorPicker::greenSliderEvent(wxScrollEvent& event)
{
	gValue = m_greenSlider->GetValue();
	m_colorPicker->SetColour(wxColor(rValue, gValue, bValue));
	std::cout << "r => " << rValue << " g => " << gValue << " b => " << bValue << "\n";
}

void ColorPicker::blueSliderEvent(wxScrollEvent& event)
{
	bValue = m_blueSlider->GetValue();
	m_colorPicker->SetColour(wxColor(rValue, gValue, bValue));
}

void ColorPicker::colorPickerEvent(wxColourPickerEvent& event)
{
	rValue = event.GetColour().Red();
	gValue = event.GetColour().Green();
	bValue = event.GetColour().Blue();
	m_redSlider->SetValue(rValue);
	m_greenSlider->SetValue(gValue);
	m_blueSlider->SetValue(bValue);
}

//BEGIN_EVENT_TABLE(ColorPicker, wxPanel)
//	EVT_(redSlider, ColorPicker::redSliderEvent)
//END_EVENT_TABLE()

