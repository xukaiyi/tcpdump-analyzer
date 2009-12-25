#ifndef _ruleFilter_included_
#define _ruleFilter_included_

#include <iostream>
#include <sstream>
#include "../main.h"
#include "ruleAbstract.h"
extern string ipFilter;
using namespace std;
class RuleFilter: public ParserRule {
private:
public:
	virtual void LineParse(string *line);
	virtual void OutputStats();
	virtual string ruleName();
};
#endif
