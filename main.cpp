#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame("�л� ���� ���� �ý���");
    frame->Show(true);
    return true;
}
