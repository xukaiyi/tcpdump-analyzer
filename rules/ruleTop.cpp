#include "ruleTop.h"

bool compare_entries(TopEntryItem *a, TopEntryItem *b) {
	return a->count > b->count;
}

TopEntryItem*  RuleTop::findByIp(string IP) {
	for (list<TopEntryItem*>::iterator iter = entries.begin(); iter != entries.end(); iter++) {
		TopEntryItem *tmpO = *iter;
		if (tmpO->ip == IP) 
			return tmpO;
	}
	return NULL;
}

void  RuleTop::LineParse(string *line) {

	if (*line == "") return;
	stringstream ssline(*line, stringstream::in | stringstream::out);
	
	string time, type, from, sep, to;
	ssline >> time >> type >> from;

	if (type != "IP") return;
	
	// read 4 digits of IP4 address, make a string of them
	int a = 0,b = 0,c = 0, d = 0;
	sscanf(from.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);	
	
	if ((a ==0) && (b ==0) && (c ==0) && (d ==0)) 
		return;
	
	std::ostringstream os;
	os << a << "." << b << "." << c << "." << d;
	std::string ip(os.str());
	
	TopEntryItem *entry = findByIp(ip);
	
	if (entry != NULL) 
		entry->count++;
	else {
		entry = new TopEntryItem;
		entry->line = *line;
		entry->ip = ip;
		entry->count = 1;
		entries.push_back(entry);
	}
}

void  RuleTop::OutputStats() {
	cout << colorOutputPart(33, "\nTop 10 source addresses") << ": \n";
	entries.sort(compare_entries);
	int i = 0;
	for (list<TopEntryItem*>::iterator iter = entries.begin(); iter != entries.end(); iter++) {
		if (++i > 10) 
			break;
		TopEntryItem *tmpO = *iter;
		cout << colorOutputPart(31, i) << "\t IP: " << colorOutputPart(4, tmpO->ip) << "\t " << colorOutputPart(32, tmpO->count) << "\n";
	}
	
}

string RuleTop::ruleName() { 
	return "Top10"; 
}
