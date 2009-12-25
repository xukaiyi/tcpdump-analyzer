#ifndef _ruleStats_included_
#define _ruleStats_included_

#include <iostream>
#include <sstream>
#include "../main.h"
#include "ruleAbstract.h"

using namespace std;
class RuleStats: public ParserRule {
private:
	int packetType(string *str);
	int packetsCount[5]; // 0: IP, 1: IPX, 2: IP6, 3: arp, 4: unknown (might be parse error)
public:
	virtual void LineParse(string *line);
	virtual void OutputStats();
	virtual string ruleName();
};
#endif
