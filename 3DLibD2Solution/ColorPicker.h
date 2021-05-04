#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/clrpicker.h>

class ColorPicker : public wxPanel
{
public:
	ColorPicker(wxWindow* parent, wxWindowID id, wxPoint point, wxSize size);
	~ColorPicker();
	int rValue;
	int gValue;
	int bValue;

private:

	void setSliders();
	void setColorPicker();
	void setColorEditors();
	void connectEvents();
	void redSliderEvent(wxScrollEvent& event);
	void greenSliderEvent(wxScrollEvent& event);
	void blueSliderEvent(wxScrollEvent& event);
	void colorPickerEvent(wxColourPickerEvent& event);

	const int ID_RED_SLIDER = 100;
	const int ID_GREEN_SLIDER = 101;
	const int ID_BLUE_SLIDER = 102;
	const int ID_COLOR_PICKER = 103;

	wxSlider *m_redSlider;
	wxSlider *m_greenSlider;
	wxSlider *m_blueSlider;
	wxStaticText *m_redLabel;
	wxStaticText *m_greenLabel;
	wxStaticText *m_blueLabel;
	wxStaticText *m_selectColor;
	/*wxTextCtrl* m_redText = nullptr;
	wxTextCtrl* m_greenText = nullptr;
	wxTextCtrl* m_blueText = nullptr;*/
	wxColourPickerCtrl *m_colorPicker;	
};

