#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>



#define COLOR_OUTPUT

extern char activeSwitches[255];
extern std::string tcpFileName;

#ifdef DEBUG
#define debugOutput(args) if(activeSwitches[(int)'v']) {cout << args << "\n";}
#else 
#define debugOutput(args)
#endif

#ifdef COLOR_OUTPUT
#define colorOutputPart(color, text) "\033[" << color << "m" << text << "\033[0m"
#else 
#define colorOutputPart(color, text) text 
#endif
