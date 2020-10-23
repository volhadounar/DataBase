#pragma once

#include <set>
#include <string>
#include <vector>
#include <map>
#include <ostream>

#include "date.h"
#include "event_set.h"


struct Entry {
  Date date;
  string event;
};


ostream& operator << (ostream& os, const Entry& e);
bool operator == (const Entry& lhs, const Entry& rhs);
bool operator != (const Entry& lhs, const Entry& rhs);

class Database {

private:
	std::map<Date, EventSet> Events; ///!!! + struct EventSet

public:
	std::map<Date, EventSet>& GetEvents() {return Events;}

	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& out) const;
	Entry Last(Date date) const;

	//int RemoveIf(const function<bool(const Date&, const string& events)> pred);
	template<class Func>
	int RemoveIf(Func f) {

		long res_count = 0;
		for (auto& item : Events) {
			auto& events = item.second;
			const auto& date = item.first;
			res_count += events.RemoveIf([=](const string& event) {
				return f(date, event);
			});
		}

		for (auto it = Events.begin(); it != Events.end();) {
			if ((*it).second.GetAll().empty()) {
				it = Events.erase(it);
			} else
				it++;
		}

		return res_count;
	}

	template<class Func>
	std::vector<Entry> FindIf(Func f) const { ///!!!!! + struct Entry

		std::vector<Entry> res;
		for (const auto& item : Events) {

			const auto& events = item.second;
			const auto& date = item.first;

			for (const auto& ev : events.GetAll()) {
				if (f(date, ev))
					res.push_back({date, ev});
			}

			/*std::vector<std::string> new_items;
			std::copy_if(begin(events), end(events), back_inserter(new_items), [&](const auto& ev){
						return f(date, ev);
					});

			for (const auto & el : new_items)
				res.push_back(std::make_pair(date, el));*/
		}
		return res;
	}


};
