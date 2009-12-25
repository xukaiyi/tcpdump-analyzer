#ifndef _parser_included_
#define _parser_included_

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "rules/ruleAbstract.h"
#include "main.h"

struct IFactory { virtual ParserRule* create() = 0; };

template< typename Type > struct Factory : public IFactory {
   virtual Type* create( ) {
      return new Type( );
   }
};


class Parser {
private:
	list<IFactory*> rules;
public:
	Parser();
	~Parser();
	int parse(char *filename);
	void registerRule(IFactory *rule);
};
#endif
