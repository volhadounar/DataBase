/*
 * node.cpp
 *
 *  Created on: 16 Sep 2019
 *      Author: Gebruiker
 */
#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
 return true;
}

 bool DateComparisonNode::Evaluate(const Date& date, const std::string& event = "") const {

	 if (_cmp == Comparison::Less)
		 return date < _date;
	 else if (_cmp == Comparison::LessOrEqual)
		 return (date <= _date) ;
	 else if (_cmp == Comparison::Greater)
		 return (date > _date) ;
	 else if (_cmp == Comparison::GreaterOrEqual)
		return (date >= _date) ;
	 else if (_cmp == Comparison::Equal)
		 return (date == _date);
	 else if (_cmp == Comparison::NotEqual)
		 return (date != _date);

	 return false;
 }

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {

	if (_cmp == Comparison::Equal)
		return _event == event;
	else if (_cmp == Comparison::NotEqual)
		return _event != event;
	if (_cmp == Comparison::Less)
		return event < _event;
	if (_cmp == Comparison::LessOrEqual)
		return event <= _event;
	if (_cmp == Comparison::Greater)
		return event > _event;
	if (_cmp == Comparison::GreaterOrEqual)
		return event >= _event;

	return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event)  const{

	if (_op ==  LogicalOperation::And)
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
	else if (_op == LogicalOperation::Or)
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);

	return false;
}
