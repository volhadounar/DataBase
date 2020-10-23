#pragma once
#include <string>
#include <memory>
#include "date.h"

enum class Comparison {
	Less = 0,
	LessOrEqual,
    Greater,
	GreaterOrEqual,
    Equal,
    NotEqual

};

enum class LogicalOperation {
	Or = 1,
	And
};

struct Node{
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

struct EmptyNode : public Node {
	virtual bool Evaluate(const Date& date, const std::string& event) const override;
};

struct DateComparisonNode : public Node {
	DateComparisonNode(Comparison cmp, Date date) : _cmp(cmp), _date(date)
	{

	}
	virtual bool Evaluate(const Date& date, const std::string& event) const override;

private:
	const Comparison _cmp;
	const Date _date;
};


struct EventComparisonNode : public Node {
	EventComparisonNode(Comparison cmp, std::string event): _cmp(cmp), _event(event)
	{

	}

	virtual bool Evaluate(const Date& date, const std::string& event) const override;

private:

	const Comparison _cmp;
	const std::string _event;

};


struct LogicalOperationNode : public Node {
	LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> left, std::shared_ptr<Node> right): _op(op), _left(left), _right(right)
	{
	}
	virtual bool Evaluate(const Date& date, const std::string& event) const override;

private:
	LogicalOperation _op;
	std::shared_ptr< Node> _left, _right;

};
