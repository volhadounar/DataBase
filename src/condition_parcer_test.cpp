

#include <sstream>
#include "condition_parser.h"
#include "test_runner.h"



void TestParseCondition() {
  {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
    Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
  }
  {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
    Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
  }
  {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
    Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
    Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
    Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
    Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
  }
  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }

  {
	  istringstream is (R"(event == "sport event" OR ( date == '2001-01-01' AND event == "my event") )");
	  shared_ptr<Node> root = ParseCondition(is);
	  Assert(!root->Evaluate({1,1,1}, "event"), "Parse condition 30");
	  Assert(root->Evaluate({1,1,1}, "sport event"), "Parse condition 31");
	  Assert(root->Evaluate({2001,1,1}, "my event"), "Parse condition 32");
  }

}



/*
void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestForEvent() {
	Database db;


	{
		istringstream is("Add 2017-11-17 Thursday");
		string command_add;
		is >> command_add;

		const auto date = ParseDate(is);
		const auto event = ParseEvent(is);

		db.Add(date, event);
		map<Date, std::vector<std::string>> m;
		m[date].push_back(event);
		AssertEqual(db.GetEvents(), m, "Add event 1");
	}
	{
		db.Add({2017, 1, 1}, "Holiday");
		db.Add({2017, 3, 8}, "Holiday");
		db.Add({2017, 1, 1}, "New Year");
		db.Add({2017, 1, 1}, "New Year");
	}

	{
		istringstream is("Del date == 2017-11-17");
		string command_del;
		is >> command_del;
		shared_ptr<Node> condition= ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event) {
			return condition->Evaluate(date, event);
		};

		int count = db.RemoveIf(predicate);
		AssertEqual(count, 1, "Del event 1");

	}

	{
		istringstream is("Del");
		cerr << "deleting all" << endl;
		string command_del;
		is >> command_del;
		shared_ptr<Node> condition=ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event) {
			return condition->Evaluate(date, event);
		};

		int count = db.RemoveIf(predicate);
		AssertEqual(count, 4, "Del all events");
	}
	{
		db.Print(cerr);
	}

	{
		istringstream is(R"(Find event != "working day")");
		string command_find;
		is >> command_find;

		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const string& event) {
			return condition->Evaluate(date, event);
		};
		const auto entries = db.FindIf(predicate);

		std::vector<pair<Date,std::string>> m;
		m.push_back(std::make_pair(Date{2017,1,1}, "Holiday"));
		m.push_back(std::make_pair(Date{2017,1,1}, "New Year"));
		m.push_back(std::make_pair(Date{2017,3,8},"Holiday"));



		m.push_back(std::make_pair(Date{2017,11,17}, "Thursday"));

		AssertEqual(entries, m, "TestFind");
	}

	{
		istringstream  is("Last 2017-01-01");
		string command_last;
		is >> command_last;
		cerr << db.Last(ParseDate(is)) << endl;
		//AssertEqual(db.Last(ParseDate(is)), "No entries", "TestLast 1");

		istringstream is2 ("Last 2017-01-01");
		is2 >> command_last;
		AssertEqual(db.Last(ParseDate(is2)), "2017-01-01 New Year", "TestLast 2");

		istringstream is3("Last 2017-11-18");
		is3 >> command_last;
		AssertEqual(db.Last(ParseDate(is3)), "2017-11-17 Thursday", "TestLast 3");
		//cerr << db.Last(ParseDate(is3));
	}


}
*/




