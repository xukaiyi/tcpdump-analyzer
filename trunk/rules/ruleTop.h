#ifndef _ruleTop_included_
#define _ruleTop_included_

#include <iostream>
#include <sstream>
#include <list>
#include "../main.h"
#include "ruleAbstract.h"

using namespace std;

struct TopEntryItem {
	string line, ip;
	unsigned int count;
};

class RuleTop: public ParserRule {
private:
	list<TopEntryItem*> entries;
	TopEntryItem* findByIp(string IP);
public:
	virtual void LineParse(string *line);
	virtual void OutputStats();
	virtual string ruleName();
};
#endif
