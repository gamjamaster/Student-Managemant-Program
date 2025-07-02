#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Student.h"
#include <vector>
#include <fstream>
#include <map>

const string filename = "students.txt";

class MainFrame : public wxFrame {
private:
    wxTextCtrl* idCtrl, * nameCtrl, * cwCtrl, * feCtrl;
    wxTextCtrl* searchCtrl;
    wxListCtrl* listCtrl;
    wxStaticText* avgText;
    wxStaticText* topText;
    wxStaticText* lowText;
    vector<Student> students;

public:
    MainFrame(const wxString& title);

    void OnAdd(wxCommandEvent& event);
    void OnUpdate(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void UpdateList();
    void SavetoFile();
    void LoadfromFile();
    void OnClose(wxCloseEvent& event);
    void OnSaveCSV(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void UpdateStats();
    void OnCountGrades(wxCommandEvent& event);

    void OnMenuSaveCSV(wxCommandEvent& event);
    void OnMenuExit(wxCommandEvent& event);
    void OnMenuAbout(wxCommandEvent& event);

    enum {
        ID_SaveCSV = 1,
        ID_Add,
        ID_Update,
        ID_Delete,
        ID_Count,
        ID_About,
    };
};
#pragma once
