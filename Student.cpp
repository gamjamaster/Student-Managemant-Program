#include "Student.h"

Student::Student(int id, string name, double coursework, double finalExam) {
	this->id = id;
	this->name = name;
	this->coursework = coursework;
	this->finalexam = finalExam;
}

int Student::getID() const { return id; }
string Student::getName() const { return name; }
double Student::getCW() const { return coursework; }
double Student::getFE() const { return finalexam; }
double Student::getFG() const { return coursework * 0.4 + finalexam * 0.6; }
string Student::getGrade() const { return gradeletter; }

void Student::setCoursework(double cw) {
	coursework = cw;
}
void Student::setFinalExam(double fe) {
	finalexam = fe;
}

void Student::setID(int Newid) {
	id = Newid;
}

void Student::setName(string Newname) {
	name = Newname;
}

void Student::setgrade() {
	double score = getFG();

	if (score >= 85) {
		gradeletter = "A+";
	}
	
	else if (score >= 78) {
		gradeletter = "A";
	}

	else if (score >= 71) {
		gradeletter = "B+";
	}

	else if (score >= 64) {
		gradeletter = "B";
	}
	
	else if (score >= 57) {
		gradeletter = "C+";
	}

	else if (score >= 50) {
		gradeletter = "C";
	}

	else {
		gradeletter = "D";
	}
}

void Student::display() const {
	cout << "ID: " << id << ", Name: " << name
		<< ", Coursework: " << coursework
		<< ", Final Exam: " << finalexam
		<< ", Final Mark: " << getFG()
		<< ", Final Grade: " << getGrade() << endl;
}

