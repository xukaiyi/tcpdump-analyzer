#include "ruleStats.h"

#define STATSCOLOR "01;36"

int RuleStats::packetType(string *str) {
	if (*str == "arp") return 3;
	else if (*str == "IP") return 0;
	else if (*str == "IPX") return 1;
	else if (*str == "IP6") return 2;
	else return 4;
}

void  RuleStats::LineParse(string *line) {
	if (*line == "") return;
	stringstream ssline(*line, stringstream::in | stringstream::out);
	
	string time, type;
	ssline >> time >> type;
		
	debugOutput("Debug: parsed (time: " << time << ", type: '" << type <<"')\n");
	
	// increase counter of given packet type
	packetsCount[packetType(&type)]++;
}

void  RuleStats::OutputStats() {
	if (activeSwitches['a'])
		cout << packetsCount[0];
	else if (activeSwitches['b'])
		cout << packetsCount[1];
	else
	cout 	<< "\nStats: \n"
		<< "File name\t\t " << colorOutputPart(STATSCOLOR,tcpFileName) << "\n"
		<< "IP Packets count\t " << colorOutputPart(STATSCOLOR, packetsCount[0]) << "\n"
		<< "IP6 Packets count\t " << colorOutputPart(STATSCOLOR, packetsCount[2]) << "\n"
		<< "IPX Packets count\t " << colorOutputPart(STATSCOLOR, packetsCount[1]) << "\n";
		
		debugOutput("ARP Packets count: " << packetsCount[3] << " [debug]\n"
		<< colorOutputPart("22;31", "<unknown> count: ") << colorOutputPart("01;31", packetsCount[4]) << " [debug]\n"
		);
}

string RuleStats::ruleName() { 
	return "Stats"; 
}
