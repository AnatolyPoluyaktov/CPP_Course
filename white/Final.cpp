
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <exception>
#include <stdexcept>
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date() {
		year = 0;
		month = 0;
		day = 0;
	}
	Date(int init_year, int init_month, int init_day) {
		if (init_month > 12 || init_month < 1) {
			throw logic_error("Month value is invalid: " + to_string(init_month));
		}
		if (init_day > 31 || init_day < 1) {
			throw logic_error("Day value is invalid: " + to_string(init_day));
		}
		year = init_year;
		month = init_month;
		day = init_day;

	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
};

istream& operator >>(istream& stream, Date& date) {
	int year, month, day;
	stream >> year;
	if (stream.peek() != '-') {
		throw exception();
	}
	stream.ignore(1);
	stream >> month;
	stream.ignore(1);
	stream >> day;
	date = { year,month,day };
	return stream;

}
bool operator<(const Date& l, const Date& r) {
	if (l.GetYear() == r.GetYear()) {
		if (l.GetMonth() == r.GetMonth())
			return l.GetDay() < r.GetDay();
		else
			return l.GetMonth() < r.GetMonth();
	}
	else
		return l.GetYear() < r.GetYear();
}
ostream& operator << (ostream& stream, const Date& date) {
	stream << setfill('0');
	stream << setw(4) << date.GetYear() << '-';
	stream << setw(2) << date.GetMonth() << '-';
	stream << setw(2) << date.GetDay();
	return stream;
}

class Database {
private:
	map<Date, set<string>>Data;
public:
	void AddEvent(const Date& date, const string& event) {
		Data[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		bool y;
		if (Data[date].count(event) > 0) {
			Data[date].erase(event);
			y = true;
		}
		else {
			y = false;
		}
		return y;
	}
	int  DeleteDate(const Date& date) {
		int n = 0;
		if (Data.count(date) > 0) {
			n = Data[date].size();
			Data.erase(date);
		}
		return n;
	}

	void Find(const Date& date) const {
		if (!Data.count(date)) {
			return;
		}

		for (const auto& de : Data.at(date))
			cout << de << endl;
	}

	void Print() const {
		for (const auto& de : Data) {
			for (const auto& e : de.second) {
				cout << de.first << ' ' << e << endl;
			}

		}
	}
};
struct ParseCom {
	string com;
	string date;
	string event;

};

ParseCom pars(const string command) {
	stringstream is(command);

	ParseCom obj;
	is >> obj.com;
	if (obj.com == "Print")
		return obj;
	if (obj.com != "Add" && obj.com != "Del" && obj.com != "Print" && obj.com != "Find")
		throw logic_error("Unknown command: " + obj.com);
	is >> obj.date;
	if (is.peek() != EOF)
		is >> obj.event;
	else return obj;
	return obj;
}
Date Parsedate(string s) {
	istringstream ss(s);
	int year, month, day;
	ss >> year;
	if (ss.peek() != '-') {

		throw logic_error("Wrong date format: " + s);
	}
	ss.ignore(1);
	if (!isdigit(ss.peek())&& ss.peek()!='+'&&ss.peek()!='-' ) {

		throw logic_error("Wrong date format: " + s);
	}
	ss >> month;
	if (ss.peek() != '-') {
		throw logic_error("Wrong date format: " + s);
	}
	ss.ignore(1);
	if (!isdigit(ss.peek()) && ss.peek() != '+' && ss.peek() != '-') {
		
		throw logic_error("Wrong date format: " + s);
	}
	ss >> day;
	if (ss.peek() != EOF) {
		
		throw logic_error("Wrong date format: " + s);
		
	}
	return Date{ year,month,day };
	

}


int main() {


	Date a;
	Database db;
	string command;
	string comm;
	Date data;
	string event;
	try {
		while (getline(cin, command)) {
			if (command.empty())
				continue;
			ParseCom obj = pars(command);
			comm = obj.com;
			if (comm == "Add") {
				//cout<<"ff";
				data = Parsedate(obj.date);
				event = obj.event;
				db.AddEvent(data, event);
			}
			else if (comm == "Del") {
				data = Parsedate(obj.date);
				if (obj.event.empty()) {
					cout << "Deleted " << db.DeleteDate(data) << " events" << endl;
				}
				else {
					event = obj.event;
					if (db.DeleteEvent(data, event))
						cout << "Deleted successfully" << endl;
					else
						cout << "Event not found" << endl;
				}

			}
			else if (comm == "Find") {
				data = Parsedate(obj.date);
				db.Find(data);
			}
			else if (comm == "Print") {
				db.Print();
			}




		}
	}
	catch (logic_error le) {
		cout << le.what();
		return 2;
	}
	//считайте команды с потока ввода и обработайте каждую


	return 0;
}
