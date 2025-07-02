#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame("切积 己利 包府 矫胶袍");
    frame->Show(true);
    return true;
}
