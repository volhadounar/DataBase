#include "database.h"
#include <algorithm>
#include <set>


/*std::ostream& operator<< (std::ostream& out, const std::pair<Date, std::vector<std::string>>& ev) {

	for (const auto& item : ev.second)
		out << ev.first << " " << item << endl;

	return out;
}*/

ostream& operator << (ostream& os, const Entry& e) {
  return os << e.date << " " << e.event;
}

bool operator == (const Entry& lhs, const Entry& rhs) {
  return tie(lhs.date, lhs.event) == tie(rhs.date, rhs.event);
}

bool operator != (const Entry& lhs, const Entry& rhs) {
  return tie(lhs.date, lhs.event) != tie(rhs.date, rhs.event);
}


void Database::Add(const Date& date, const string& event) {

	Events[date].Add(event);

}

void Database::Print(std::ostream& out) const {

	for (const auto& item : Events)
		  for (const auto& event : item.second.GetAll()) {
		      out << item.first << ' ' << event << endl;
		    }
}

Entry Database::Last(Date date) const {

	auto it_first = Events.upper_bound(date);

	if (it_first == begin(Events))
		 throw invalid_argument("");

	--it_first;

	return {it_first->first, it_first->second.GetAll().back()};
	/*

	stringstream res;
	if (Events.size() == 0)
		return  res_empty;

	auto it_first = Events.lower_bound(date);

	if (it_first == begin(Events) && (*it_first).first != date ) {
		return res_empty;
	}

	if (it_first != end(Events) && (*it_first).first == date) {
		res << (*it_first).first << " ";
		res << (*it_first).second.back();
		return res.str();
	}

	res << (*std::prev(it_first)).first << " ";
	res << (*std::prev(it_first)).second.back();
	return res.str();

*/
}


