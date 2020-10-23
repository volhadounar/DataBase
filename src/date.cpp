#include "date.h"

Date ParseDate(istream& is) {

	Date result;
	is >> result.year;
	is.ignore(1);
	is >> result.month;
	is.ignore(1);
	is >> result.day;
	return result;

	/*string line;
	if (is)
		is >> line;


	Date d(line);

	return d;*/

}

/*
void CheckNum(stringstream& is, string s_date) {
	std::vector<char> num = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	if (is && end(num) == find(begin(num), end(num), is.peek())) {
		stringstream ss;
		ss << "Wrong date format: " << s_date;
		throw runtime_error(ss.str());
	}
}

void EnsureNextSymbolAndSkip(stringstream& is, int& val, string s_date) {

	if (is.peek() != '-') {
		stringstream ss;
		ss << "Wrong date format: " << s_date;
		throw runtime_error(ss.str());
	}

	is.ignore(1);

	if (is.peek() == '+') {
		is.ignore(1);
		CheckNum(is, s_date);
	}

	if (is.peek() == '-') {
		is.ignore(1);
		CheckNum(is, s_date);
		is >> val;
		val *= (-1);
	} else {
		is >> val;
	}

	if (!is) {
		stringstream ss;
		ss << "Wrong date format: " << s_date;
		throw runtime_error(ss.str());
	}
}
*/

ostream& operator << (ostream& os, const Date& date) {
  os << setw(4) << setfill('0') << date.year << '-'
     << setw(2) << setfill('0') << date.month << '-'
     << setw(2) << setfill('0') << date.day;
  return os;
}

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator != (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) != tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator <= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) <= tie(rhs.year, rhs.month, rhs.day);
}

bool operator > (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) > tie(rhs.year, rhs.month, rhs.day);
}

bool operator >= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) >= tie(rhs.year, rhs.month, rhs.day);
}

