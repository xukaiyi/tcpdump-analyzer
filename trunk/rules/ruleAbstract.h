#ifndef _ruleAbstract_included_
#define _ruleAbstract_included_

#include <iostream>

using namespace std;
class ParserRule {
public:
	virtual void LineParse(string *line);
	virtual string ruleName();
	virtual void OutputStats();
};


#endif
