#include "main.h"
#include "parser.h"
Parser::Parser() {

}


int Parser::parse(char *filename) {
	ifstream tcpFile;
	tcpFile.open(filename);
	
	if (!tcpFile || !tcpFile.is_open()) {
		cout << "Cannot open file "<< filename << ". Terminating.\n";
		return 0;
	}
	
	string tmpline;
	
	// list of parsers instances 
	vector<ParserRule*> parsers;
	// make instance of each registered parser
	for (list<IFactory*>::iterator iter = rules.begin(); iter != rules.end(); iter++) {
		ParserRule *tmpO = (*iter)->create();
		parsers.push_back(tmpO);
	}			
	
	int linesCount = 0;	
	while (getline(tcpFile, tmpline) && ++linesCount) {
		
		debugOutput( "Debug: parsing line \"" << tmpline << "\"");
		
		
		vector<ParserRule*>::iterator iter;
		for (iter = parsers.begin(); iter != parsers.end(); iter++) {
			ParserRule *tmpO = *iter;
			debugOutput("Parsing, rule " << tmpO->ruleName());
			tmpO->LineParse(&tmpline);
		}		
	}
	
	if (activeSwitches['n']) {
		cout << linesCount << "\n";
		return 0;
	}
	
	vector<ParserRule*>::iterator iter;
	for (iter = parsers.begin(); iter != parsers.end(); iter++) {
		ParserRule *tmpO = *iter;			
		tmpO->OutputStats();
		delete tmpO;
	}		
	
	return 0;
	
		
}

Parser::~Parser() {
	while (!rules.empty()) {
		delete rules.front();
		rules.pop_front();
	}
}

void Parser::registerRule(IFactory *rule) {
	rules.push_back(rule);
}
