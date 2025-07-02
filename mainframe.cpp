#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 600)) {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    idCtrl = new wxTextCtrl(panel, wxID_ANY);
    nameCtrl = new wxTextCtrl(panel, wxID_ANY);
    cwCtrl = new wxTextCtrl(panel, wxID_ANY);
    feCtrl = new wxTextCtrl(panel, wxID_ANY);
    searchCtrl = new wxTextCtrl(panel, wxID_ANY);
    avgText = new wxStaticText(panel, wxID_ANY, "Avg Mark: -");
    topText = new wxStaticText(panel, wxID_ANY, "Highest Mark: -");
    lowText = new wxStaticText(panel, wxID_ANY, "Lowest Mark: -");
    wxButton* searchButton = new wxButton(panel, wxID_ANY, "Search Student");

    hbox->Add(new wxStaticText(panel, wxID_ANY, "ID:"), 0, wxRIGHT, 5);
    hbox->Add(idCtrl, 1, wxRIGHT, 10);
    hbox->Add(new wxStaticText(panel, wxID_ANY, "Name:"), 0, wxRIGHT, 5);
    hbox->Add(nameCtrl, 1, wxRIGHT, 10);
    hbox->Add(new wxStaticText(panel, wxID_ANY, "CW:"), 0, wxRIGHT, 5);
    hbox->Add(cwCtrl, 1, wxRIGHT, 10);
    hbox->Add(new wxStaticText(panel, wxID_ANY, "FE:"), 0, wxRIGHT, 5);
    hbox->Add(feCtrl, 1, wxRIGHT, 10);
    hbox->Add(new wxStaticText(panel, wxID_ANY, "°Λ»φ(ID):"), 0, wxRIGHT | wxLEFT, 5);
    hbox->Add(searchCtrl, 1, wxRIGHT, 5);
    hbox->Add(searchButton, 0, wxRIGHT, 5);

    vbox->Add(hbox, 0, wxEXPAND | wxALL, 10);
    vbox->Add(avgText, 0, wxLEFT | wxBOTTOM, 5);
    vbox->Add(topText, 0, wxLEFT | wxBOTTOM, 5);
    vbox->Add(lowText, 0, wxLEFT | wxBOTTOM, 5);

    listCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    listCtrl->InsertColumn(0, "ID");
    listCtrl->InsertColumn(1, "Name");
    listCtrl->InsertColumn(2, "CW");
    listCtrl->InsertColumn(3, "FE");
    listCtrl->InsertColumn(4, "Avg");
    listCtrl->InsertColumn(5, "Grade");

    vbox->Add(listCtrl, 1, wxEXPAND | wxALL, 10);
    panel->SetSizer(vbox);

    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_SaveCSV, "Save as CSV...\tCtrl-S", "Save student data to a CSV file");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(ID_Add, "Add Student", "Add a new student record");
    editMenu->Append(ID_Update, "Update Student", "Update the selected student record");
    editMenu->Append(ID_Delete, "Delete Student", "Delete the selected student record");
    editMenu->AppendSeparator();
    editMenu->Append(ID_Count, "Count Grades", "Count students per grade");

    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_About, "&About...\tF1", "Show about dialog");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::OnMenuSaveCSV, this, ID_SaveCSV);
    Bind(wxEVT_MENU, &MainFrame::OnMenuAbout, this, ID_About);
    Bind(wxEVT_MENU, &MainFrame::OnMenuExit, this, wxID_EXIT);

    Bind(wxEVT_MENU, &MainFrame::OnAdd, this, ID_Add);
    Bind(wxEVT_MENU, &MainFrame::OnUpdate, this, ID_Update);
    Bind(wxEVT_MENU, &MainFrame::OnDelete, this, ID_Delete);
    Bind(wxEVT_MENU, &MainFrame::OnCountGrades, this, ID_Count);

    searchButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearch, this);

    LoadfromFile();
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

void MainFrame::OnAdd(wxCommandEvent& event) {
    long id;
    if (!idCtrl->GetValue().ToLong(&id)) {
        wxMessageBox("ID has to a numerical value.");
        return;
    }

    wxString name = nameCtrl->GetValue();
    double cw, fe;
    if (!cwCtrl->GetValue().ToDouble(&cw) || !feCtrl->GetValue().ToDouble(&fe)) {
        wxMessageBox("Mark has to be a numerical value.");
        return;
    }

    Student s(id, std::string(name.mb_str()), cw, fe);
    s.setgrade();
    students.push_back(s);
    UpdateList();
    UpdateStats();

    idCtrl->Clear();
    nameCtrl->Clear();
    cwCtrl->Clear();
    feCtrl->Clear();
}

void MainFrame::UpdateList() {
    listCtrl->DeleteAllItems();

    for (size_t i = 0; i < students.size(); ++i) {
        const Student& s = students[i];
        listCtrl->InsertItem(i, wxString::Format("%d", s.getID()));
        listCtrl->SetItem(i, 1, s.getName());
        listCtrl->SetItem(i, 2, wxString::Format("%.1f", s.getCW()));
        listCtrl->SetItem(i, 3, wxString::Format("%.1f", s.getFE()));
        listCtrl->SetItem(i, 4, wxString::Format("%.1f", s.getFG()));
        listCtrl->SetItem(i, 5, s.getGrade());
    }
}

void MainFrame::OnUpdate(wxCommandEvent& event) {
    long itemIndex = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex == -1) {
        wxMessageBox("Select the record to update.");
        return;
    }

    long id;
    if (!idCtrl->GetValue().ToLong(&id)) {
        wxMessageBox("ID has to be a numerical value.");
        return;
    }

    wxString name = nameCtrl->GetValue();
    double cw, fe;
    if (!cwCtrl->GetValue().ToDouble(&cw) || !feCtrl->GetValue().ToDouble(&fe)) {
        wxMessageBox("Mark has to be a numerial number.");
        return;
    }

    students[itemIndex].setID(id);
    students[itemIndex].setName(std::string(name.mb_str()));
    students[itemIndex].setCoursework(cw);
    students[itemIndex].setFinalExam(fe);
    students[itemIndex].setgrade();

    UpdateList();
    UpdateStats();

    idCtrl->Clear();
    nameCtrl->Clear();
    cwCtrl->Clear();
    feCtrl->Clear();
}

void MainFrame::OnDelete(wxCommandEvent& event) {
    long itemIndex = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex == -1) {
        wxMessageBox("Select the record to delete.");
        return;
    }

    wxString name = listCtrl->GetItemText(itemIndex, 1);

    int result = wxMessageBox(
        "Delete this record?",
        "Record Deleted",
        wxYES_NO | wxICON_QUESTION
    );

    if (result == wxNO) return;

    students.erase(students.begin() + itemIndex);
    UpdateList();
    UpdateStats();

    wxMessageBox("Student record has been deleted.", "Complete", wxOK | wxICON_INFORMATION);
}

void MainFrame :: SavetoFile() {
    ofstream out(filename);
    if (!out) {
        wxMessageBox("No record has been found.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    for (const Student& s : students) {
        out << s.getID() << " "
            << s.getName() << " "
            << s.getCW() << " "
            << s.getFE() << " "
            << s.getGrade() << " " << endl;
    }

    out.close();
}

void MainFrame::LoadfromFile() {
    ifstream in(filename);
    if (!in) {
        wxLogWarning("Unable to load student data.");
        return;
    }

    students.clear();

    int id;
    string name;
    double cw, fe;

    while (in >> id >> name >> cw >> fe) {
        Student s(id, name, cw, fe);
        s.getGrade();
        students.push_back(s);
    }

    in.close();
    UpdateList();
    UpdateStats();
}

void MainFrame::OnClose(wxCloseEvent& event) {
    SavetoFile();
    event.Skip();
}

void MainFrame::OnSaveCSV(wxCommandEvent& event) {
    ofstream out("students.csv");
    if (!out) {
        wxMessageBox("Unable to save the data.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    out << "ID,Name,Coursework,FinalExam,FinalMark,Grade\n";

    for (const Student& s : students) {
        out << s.getID() << ","
            << s.getName() << ","
            << s.getCW() << ","
            << s.getFE() << ","
            << s.getFG() << ","
            << s.getGrade() << "\n";
    }

    out.close();
    wxMessageBox("Saved the record as CSV.", "Complete", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnSearch(wxCommandEvent& event) {
    long searchID;
    if (!searchCtrl->GetValue().ToLong(&searchID)) {
        wxMessageBox("Enter the ID.");
        return;
    }

    listCtrl->DeleteAllItems();
    bool found = false;

    for (size_t i = 0; i < students.size(); ++i) {
        const Student& s = students[i];
        if (s.getID() == searchID) {
            listCtrl->InsertItem(0, wxString::Format("%d", s.getID()));
            listCtrl->SetItem(0, 1, s.getName());
            listCtrl->SetItem(0, 2, wxString::Format("%.1f", s.getCW()));
            listCtrl->SetItem(0, 3, wxString::Format("%.1f", s.getFE()));
            listCtrl->SetItem(0, 4, wxString::Format("%.1f", s.getFG()));
            listCtrl->SetItem(0, 5, s.getGrade());
            found = true;
            break;
        }
    }

    if (!found) {
        wxMessageBox("The ID does not exist.");
        UpdateList();
        UpdateStats();
    }
}

void MainFrame::UpdateStats() {
    if (students.empty()) {
        avgText->SetLabel("Avg Mark: -");
        topText->SetLabel("Highest Mark: -");
        lowText->SetLabel("Lowest Mark: -");
        return;
    }

    double total = 0;
    const Student* top = &students[0];
    const Student* low = &students[0];

    for (const Student& s : students) {
        total += s.getFG();
        if (s.getFG() > top->getFG()) top = &s;
        if (s.getFG() < low->getFG()) low = &s;
    }

    double avg = total / students.size();

    avgText->SetLabel(wxString::Format("Avg Mark: %.1f", avg));
    topText->SetLabel(wxString::Format("Highest Mark: %s (%.1f)", top->getName(), top->getFG()));
    lowText->SetLabel(wxString::Format("Lowest Mark: %s (%.1f)", low->getName(), low->getFG()));
}

#include <map>

void MainFrame::OnCountGrades(wxCommandEvent& event) {
    if (students.empty()) {
        wxMessageBox("No student data has been found.");
        return;
    }

    std::map<std::string, int> gradeCounts;

    for (const Student& s : students) {
        gradeCounts[s.getGrade()]++;
    }

    wxString result = "Number per Grade:\n";
    for (const auto& pair : gradeCounts) {
        result += wxString::Format("%s: %dΈν\n", pair.first, pair.second);
    }

    wxMessageBox(result, "Grade Distribution", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnMenuSaveCSV(wxCommandEvent& event) {
    OnSaveCSV(event);
}

void MainFrame::OnMenuExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnMenuAbout(wxCommandEvent& event) {
    wxMessageBox("This is a Student Record Management application.\n\nCreated using wxWidgets.",
        "About Student Records", wxOK | wxICON_INFORMATION);
}