#include "ruleAbstract.h"

void ParserRule::LineParse(string *line) {
	// do nothing, it's abstract!
}
void ParserRule::OutputStats(){
	// do nothing, it's abstract
}

string ParserRule::ruleName(){
	return "<abstract>";
}

