#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std;

class Date;
Date ParseDate(istream& is) ;
//void EnsureNextSymbolAndSkip(stringstream& is, int& val, string s_date);

struct Date {
  int year, month, day;
};

/*
class Date {
	int day = 0;

	int month = 0;

	int year = 0;

public:
	Date(int y, int m, int d ) {
		year = y;
		month = m;
		day = d;
	}
	Date(string s_date) {
		stringstream ss(s_date);
		int d, m, y;

		ss >> y;
		EnsureNextSymbolAndSkip(ss, m, s_date);
		EnsureNextSymbolAndSkip(ss, d, s_date);

		char ch = ss.peek();

		if (ch > 0) {
			stringstream ss;
			ss << "Wrong date format: " << s_date;
			throw runtime_error(ss.str());
		}

		if (m > 12 || m < 1) {
			stringstream ss;
			ss << "Month value is invalid: " << m;
			throw runtime_error(ss.str());
		}
		if (d > 31 || d < 1) {
			stringstream ss;
			ss << "Day value is invalid: " << d;
			throw runtime_error(ss.str());
		}

		day = d;
		month = m;
		year = (y);
	}

};
*/



ostream& operator << (ostream& os, const Date& date);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);
bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);
