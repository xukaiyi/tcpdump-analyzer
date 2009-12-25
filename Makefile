# kompilator
CC = g++
# linker
LD = g++
# flagi kompilatora
CFLAGS = -Wall
# flagi linkera
LDFLAGS = -o3 -s
# polecenie do usuwania plikow
RM = /bin/rm -f
# lista plikow
OBJS = main.o parser.o rules/ruleAbstract.o rules/ruleStats.o rules/ruleFilter.o rules/ruleTop.o
# nazwa pliku wykonywalnego
PROG = tcpanalyzer

# domyslny switch
all: $(PROG)

# dla debugowania, dodaj odpowiednie flagi
debug: CFLAGS += -DDEBUG -g
debug: LDFLAGS += -DDEBUG -g
# i wykonaj kompilacje
debug: $(PROG)

# zasady linkowania
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)


main.o: main.cpp main.h
	$(CC) $(CFLAGS) -c main.cpp

parser.o: parser.cpp parser.h main.h
	$(CC) $(CFLAGS) -c parser.cpp
	
rules/ruleAbstract.o: rules/ruleAbstract.cpp rules/ruleAbstract.h main.h
	$(CC) $(CFLAGS) -c rules/ruleAbstract.cpp -o rules/ruleAbstract.o
	
rules/ruleStats.o: rules/ruleStats.cpp rules/ruleStats.h main.h
	$(CC) $(CFLAGS) -c rules/ruleStats.cpp -o rules/ruleStats.o
	
rules/ruleFilter.o: rules/ruleFilter.cpp rules/ruleFilter.h main.h
	$(CC) $(CFLAGS) -c rules/ruleFilter.cpp -o rules/ruleFilter.o

rules/ruleTop.o: rules/ruleTop.cpp rules/ruleTop.h main.h
	$(CC) $(CFLAGS) -c rules/ruleTop.cpp -o rules/ruleTop.o


# czyszczenie plikow
clean:
	$(RM) $(PROG) $(OBJS)
