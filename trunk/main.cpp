/*
TCPDUMP analyzer

program analizujacy logi programu tcpdump.
przetestowany na logach wygenerowanych z przelacznikami
	-n (celem wyswietlania wylacznie adresow IP a nie nazw hostow)
oraz ewentualnie z przelacznikiem -f
przykladowe logi pochodza z programu w wersji 4.0.0, libpcap 1.0.0


Copyright 2009 Michał Gajek, grupa 5
migajek@gmail.com
http://migajek.com/


uwagi:
	w przypadku wyswietlania dziwnych "krzakow" na wyjsciu, nalezy wylaczyc dyrektywe #DEFINE COLOR_OUTPUT z main.h	
*/

#include "main.h"
#include "parser.h"
#include "rules/ruleAbstract.h"
#include "rules/ruleStats.h"
#include "rules/ruleFilter.h"
#include "rules/ruleTop.h"


char activeSwitches[255]; //active literal switches, like -a -f -b etc
string ipFilter, tcpFileName;
using namespace std;

void copyrights(bool skipName = false) {
	if (activeSwitches['a'] || activeSwitches['b'] || activeSwitches['n'])  
		return ;
		
	if (!skipName)
		cout << colorOutputPart("01;33", "\n\nTCPDUMP analyzer");
	cout << colorOutputPart("01;34", "\nCopyright 2009 Michal Gajek, all rights reserved\nhttp://migajek.com\n");

}

int main(int argc, char **argv) {

	
	char *filename = NULL;
	
	for (int i = 1; i < argc; i++) {
	
		
		//debugOutput("Debug: argv[" << i << "]: " << argv[i] << "\n");
		
		
		if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "--?")) {
			cout << colorOutputPart("01;33", "\nTCPDUMP analyzer");
			
			cout << "\nUsage: tcpanalyzer "
			#ifdef DEBUG
			<< "[switches] "
			#endif
			
			<< colorOutputPart(32, "[switches]")  << colorOutputPart(31," file_name\n");
					
			cout << colorOutputPart(31, "correct file name must be given!\n");
			
			
			cout << "possible " <<  colorOutputPart(32, "switches") << ":\n";
			cout << " -a\t\t displays " << colorOutputPart("31;4", "only") << " IP4 packets count\n";
			
			cout << " -b\t\t displays " << colorOutputPart("31;4", "only") << " IP6 packets count\n";
			
			cout << " -n\t\t displays " << colorOutputPart("31;4", "only") << " overall packets count\n";
			
			cout << " -f "<< colorOutputPart(36, "<IP>") <<"\t displays " << colorOutputPart("31;4", "only") << " packets to/from given " << colorOutputPart(36, "<IP>") << "\n";
			
			cout << " -h\t\t displays " << colorOutputPart("33", "top ten") << " entries\n";
			#ifdef DEBUG
			cout << "possible <switches>:\n";
			cout << " -v\t\t verbose mode\n";
			#endif
			
			copyrights(true);
			return 0;
		}
		else if (strlen(argv[i]) > 1) {
		
			// handle options switch
			if (argv[i][0] == '-') {
				// if not empty after "-"
				activeSwitches[(int)argv[i][1]] = 1;
				if ((argv[i][1] == 'f') && (i + 1 < argc))
					ipFilter = argv[++i];
			} else {//assume its filename
				filename = argv[i];				
				tcpFileName = filename;
			}
			
		}
	}

	if (filename != NULL) {	
		// new parser object
		Parser *p = new Parser();
		
		//register parsing rule(s).
		if (activeSwitches['f'])
			p->registerRule(new Factory<RuleFilter>);
		else if (activeSwitches['h'])
			p->registerRule(new Factory<RuleTop>);
		else
			p->registerRule(new Factory<RuleStats>);
			
		// parse file
		p->parse(filename);
		
		//delete object
		delete p;
		
		copyrights();
		return 0;

	} else {
		cout << colorOutputPart("01;31", "\nIncorrect or missing parameters.") << "\nPlease run with --help switch to display help page.\n\n";
		return 0;
	}
}
