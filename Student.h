#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
private:
	int id;
	string name;
	double coursework;
	double finalexam;
	string gradeletter;

public:
	Student(int id, string name, double coursework, double finalExam);
	int getID() const;
	string getName() const;
	double getCW() const;
	double getFE() const;
	double getFG() const;
	string getGrade() const;

	void setCoursework(double cw);
	void setFinalExam(double fe);
	void setID(int Newid);
	void setName(string Newname);
	void display() const;
	void setgrade();
};

#endif#pragma once
