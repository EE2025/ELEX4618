#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <regex>
#include <iomanip>


using namespace std;

class CStudent
{
public:
	string student_number;
	float final_grade, lab_grade, quiz_grade, midterm_grade, final_exam_grade;
};

class CCourse
{
private:
	vector <CStudent> grades;
public:
	void edit_student(int index)
	{
		CStudent& grade = grades.at(index);
		string student_number;
		grade.student_number = ID_validation("Enter Student Number: ");

		string grades_output[4] = { "Lab Grade: ", "Quiz Grade: ", "Midterm Grade: ", "Final Grade: " };

		grade.lab_grade = stof(grade_entry(grades_output[0]));

		grade.quiz_grade = stof(grade_entry(grades_output[1]));

		grade.midterm_grade = stof(grade_entry(grades_output[2]));

		grade.final_exam_grade = stof(grade_entry(grades_output[3]));

		grade.final_grade = ((grade.lab_grade) * 0.4) + ((grade.quiz_grade) * 0.1) + ((grade.midterm_grade) * 0.2) + ((grade.final_exam_grade) * 0.3);
	}

	string ID_validation(string student_number)
	{
		string input;
		bool error;
		cin.ignore();
		do
		{
			error = false;
			cout << "Enter Student Number: ";
			getline(cin, input);
			if (input.substr(0, 3) == "A00" || input.substr(0, 3) == "A01")
			{
				for (char ch : input.substr(3, 6))
				{
					if (ch < '0' || ch > '9')
					{
						cout << "Enter a valid student number!" << endl;
						error = true;
						break;
					}
				}
				if (size(input) != 9)
				{
					cout << "Enter a valid student number!" << endl;
					error = true;
				}
			}

			else
			{
				cout << "Enter a valid student number!" << endl;
				error = true;
			}
		} while (error);
		return input;
	}

	string grade_entry(string grade)
	{
		string input;
		bool error;
		do
		{
			error = false;
			cout << grade;
			getline(cin, input);
			int decimal = 0;
			if (input.length() > 6)
			{
				cout << "Enter a valid grade between 0.0 and 100.0!" << endl;
				error = true;
			}
			else
			{
				for (char ch : input) {

					if (ch == '.')
					{
						decimal++;

						if (decimal > 1)
						{
							cout << "Enter a valid grade between 0.0 and 100.0!" << endl;
							error = true;
							//cin.ignore(10, '\n');
							break;

						}
					}
					else if (ch < '0' || ch > '9')
					{
						cout << "Enter a valid grade between 0.0 and 100.0!" << endl;
						error = true;
						//cin.ignore(10, '\n');
						break;
					}
				}
			}
			if (!error && (stof(input)) > 100)
			{
				cout << "Enter a valid grade between 0.0 and 100.0!" << endl;
				error = true;
				//cin.ignore(10, '\n');
			}
		} while (error);
		return input;
	}
	void add_student(string studentID)
	{
		CStudent student;
		student.student_number = studentID;
		grades.push_back(student);
		edit_student(grades.size() - 1);

	}

	void print_grades() {
		cout << "#" << "\t" << "Student" << "\t\t" << "Lab" << "\t" << "Quiz" << "\t" << "Midterm" << "\t\t" << "Final Exam" << "\t" << "Final Grade" << endl;

		for (int i = 0; i < grades.size(); i++)
		{
			cout << i + 1 << "\t" <<
				grades.at(i).student_number << "\t" <<
				fixed << setprecision(1) << grades.at(i).lab_grade << "\t" <<
				fixed << setprecision(1) << grades.at(i).quiz_grade << "\t" <<
				fixed << setprecision(1) << grades.at(i).midterm_grade << "\t\t" <<
				fixed << setprecision(1) << grades.at(i).final_exam_grade << "\t\t" <<
				fixed << setprecision(2) << grades.at(i).final_grade << endl;
		}
	}

	void deleteStudent(int index) {
		grades.erase(std::next(grades.begin(), index));
	}

	void save_file()
	{
		string file_name;
		cout << "Enter a file name to save as: ";
		cin >> file_name;

		ofstream file(file_name);
		if (file.is_open()) {
			for (int i = 0; i < grades.size(); i++)
			{
				file << grades[i].student_number << " " << grades[i].lab_grade << " " << grades[i].quiz_grade << " " << grades[i].midterm_grade << " " << grades[i].final_exam_grade << " " << grades[i].final_grade << endl;
			}
			file.close();
			cout << "Data saved to " << file_name << endl;
		}
		else {
			cout << "Error. Unable to open file." << endl;
		}
	}

	void load_file()
	{
		string file_name;
		cout << "Enter a file name to load: ";
		cin >> file_name;

		ifstream file(file_name);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				CStudent student;
				istringstream iss(line);
				iss >> student.student_number >> student.lab_grade >> student.quiz_grade >> student.midterm_grade >> student.final_exam_grade >> student.final_grade;
				grades.push_back(student);
			}
			file.close();
			cout << "Data loaded from " << file_name << endl;
		}
		else
		{
			cout << "Error. Unable to open file." << endl;
		}
	}

	bool check_student(int index)
	{
		for (int i = 0; i < grades.size(); i++)
		{
			if (i < index)
			{
				cout << "Error! Student not found." << endl;
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	
	int check_int()
	{
		int i;
		bool valid = false;
		do
		{
			cout << "Number of Student: " << flush;
			cin >> i;
			if (cin.good())
			{
				valid = true;
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error! Please enter a valid fucking integer!!!!!" << endl;
			}
		} while (!valid);
		return i;
	}
};

void print_menu()
{
	cout << "***********************************\n" << endl;
	cout << "ELEX4618 grade system, by Jimmy Wang\n" << endl;
	cout << "***********************************\n" << endl;
	cout << "(A)dd student\n" << endl;
	cout << "(E)dit student\n" << endl;
	cout << "(D)elete student\n" << endl;
	cout << "(P)rint grades\n" << endl;
	cout << "(S)ave class\n" << endl;
	cout << "(L)oad class\n" << endl;
	cout << "(Q)uit\n" << endl;
}

int main()
{
	CCourse myGrades;
	string student_integer;
	string studentID;
	while (1)
	{
		print_menu();
		//string student_integer;
		char cmd;
		cout << "CMD> ";
		cin >> cmd;

		switch (cmd)
		{
		case 'A':
			cout << "Adding Student \n";
			myGrades.add_student(studentID);
			break;

		case 'E':
			int number_of_student ;
			cout << "Enter a student to edit: ";
			cin >> number_of_student;
				
			if 	(myGrades.check_student(number_of_student-1))
				{
					myGrades.edit_student(number_of_student-1);
				}

			break;
			

		case 'P':
			myGrades.print_grades();
			break;

		case 'Q':
			cout << "Goodbye!" << endl;
			return 0;
			break;

		case 'D':
			int delete_student;
			cout << "Enter a student to delete: ";
			cin >> delete_student;
			if (myGrades.check_student(delete_student - 1))
			{
				myGrades.deleteStudent(delete_student - 1);
			}
			cout << "Deleted student " << delete_student << "!" << endl;
			break;

		case 'S':

			myGrades.save_file();
			break;

		case 'L':
			myGrades.load_file();
			break;

		default:
			cout << "Unknown command." << endl;
			break;
		}
	}
}