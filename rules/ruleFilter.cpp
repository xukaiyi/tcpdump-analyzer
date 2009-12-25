#include "ruleFilter.h"


void  RuleFilter::LineParse(string *line) {
	if (*line == "") return;
	stringstream ssline(*line, stringstream::in | stringstream::out);
	
	string time, type, from, sep, to;
	ssline >> time >> type >> from >> sep >> to;
	//string filterIP = "153.19.49.25";
	if ( (type == "IP") && ( (from.find(ipFilter) != string::npos) || (to.find(ipFilter) != string::npos) )) {
		cout /*<< "Found matching entry: " */<< *line << "\n";
	}
	//debugOutput("Debug: type: " << type << ", from: '" << from << ", to: " << to <<"')\n");
	debugOutput("from: '"<<from<<"', to:'"<< to << "'\n\n");
	
}

void  RuleFilter::OutputStats() {


}

string RuleFilter::ruleName() { 
	return "Filter"; 
}
