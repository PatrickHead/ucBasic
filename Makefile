ub: CC = gcc
ub: COPTS = -g -Wall -O0 -I include
generic/.o: CC = gcc
generic/.o: COPTS = -g -Wall -O0 -I include
avrub: CC = avr-gcc
avrub: COPTS = -mmcu=atmega328p -Wall -Os -I include
avr/.o: CC = avr-gcc
avr/.o: COPTS = -mmcu=atmega328p -Wall -Os -I include

all: ub avrub

ub: generic/ub.o generic/program.o generic/variable.o generic/token.o \
    generic/command-lexicon.o generic/language-lexicon.o \
		generic/command-grammar.o generic/language-grammar.o generic/function.o \
    generic/utility.o generic/error.o
	$(CC) $(COPTS) -o ub \
    generic/ub.o generic/program.o generic/variable.o generic/token.o \
    generic/command-lexicon.o generic/language-lexicon.o \
    generic/command-grammar.o generic/language-grammar.o generic/function.o \
    generic/utility.o generic/error.o

generic/ub.o: src/ub.c include/program.h include/token.h \
              include/command-grammar.h include/error.h
	$(CC) $(COPTS) -o generic/ub.o -c src/ub.c

generic/program.o: src/program.c include/variable.h include/token.h \
                   include/language-grammar.h include/error.h include/program.h
	$(CC) $(COPTS) -o generic/program.o -c src/program.c

generic/variable.o: src/variable.c include/variable.h
	$(CC) $(COPTS) -o generic/variable.o -c src/variable.c

generic/token.o: src/token.c include/token.h
	$(CC) $(COPTS) -o generic/token.o -c src/token.c

generic/language-lexicon.o: src/language-lexicon.c include/token.h \
                            include/language-lexicon.h
	$(CC) $(COPTS) -o generic/language-lexicon.o -c src/language-lexicon.c

generic/language-grammar.o: src/language-grammar.c include/token.h \
                            include/program.h include/variable.h \
                            include/language-lexicon.h \
                            include/language-grammar.h include/function.h \
                            include/utility.h include/error.h
	$(CC) $(COPTS) -o generic/language-grammar.o -c src/language-grammar.c

generic/command-lexicon.o: src/command-lexicon.c include/token.h \
                           include/command-lexicon.h
	$(CC) $(COPTS) -o generic/command-lexicon.o -c src/command-lexicon.c

generic/command-grammar.o: src/command-grammar.c include/token.h \
                           include/program.h include/command-lexicon.h \
                           include/language-lexicon.h \
                           include/language-grammar.h include/error.h \
                           include/utility.h include/command-grammar.h
	$(CC) $(COPTS) -o generic/command-grammar.o -c src/command-grammar.c

generic/function.o: src/function.c include/program.h include/function.h
	$(CC) $(COPTS) -o generic/function.o -c src/function.c

generic/utility.o: src/utility.c include/utility.h
	$(CC) $(COPTS) -o generic/utility.o -c src/utility.c

generic/error.o: src/error.c include/error.h
	$(CC) $(COPTS) -o generic/error.o -c src/error.c

avrub: avr/avrub.o avr/program.o avr/variable.o avr/token.o \
       avr/command-lexicon.o avr/language-lexicon.o avr/command-grammar.o \
       avr/language-grammar.o avr/function.o avr/utility.o avr/error.o
	$(CC) $(COPTS) -o avrub \
    avr/avrub.o avr/program.o avr/variable.o avr/token.o avr/command-lexicon.o \
    avr/language-lexicon.o avr/command-grammar.o avr/language-grammar.o \
    avr/function.o avr/utility.o avr/error.o

avr/avrub.o: src/avrub.c include/program.h include/token.h \
             include/command-grammar.h include/error.h include/utility.h
	$(CC) $(COPTS) -o avr/avrub.o -c src/avrub.c

avr/program.o: src/program.c include/variable.h include/token.h \
               include/language-grammar.h include/error.h include/program.h
	$(CC) $(COPTS) -o avr/program.o -c src/program.c

avr/variable.o: src/variable.c include/variable.h
	$(CC) $(COPTS) -o avr/variable.o -c src/variable.c

avr/token.o: src/token.c include/token.h
	$(CC) $(COPTS) -o avr/token.o -c src/token.c

avr/language-lexicon.o: src/language-lexicon.c include/token.h \
                        include/language-lexicon.h
	$(CC) $(COPTS) -o avr/language-lexicon.o -c src/language-lexicon.c

avr/language-grammar.o: src/language-grammar.c include/token.h \
                        include/program.h include/variable.h \
                        include/language-lexicon.h \
                        include/language-grammar.h include/function.h \
                        include/utility.h include/error.h
	$(CC) $(COPTS) -o avr/language-grammar.o -c src/language-grammar.c

avr/command-lexicon.o: src/command-lexicon.c include/token.h \
                       include/command-lexicon.h
	$(CC) $(COPTS) -o avr/command-lexicon.o -c src/command-lexicon.c

avr/command-grammar.o: src/command-grammar.c include/token.h \
                       include/program.h include/command-lexicon.h \
                       include/language-lexicon.h include/language-grammar.h \
                       include/error.h include/utility.h \
                       include/command-grammar.h
	$(CC) $(COPTS) -o avr/command-grammar.o -c src/command-grammar.c

avr/function.o: src/function.c include/program.h include/function.h
	$(CC) $(COPTS) -o avr/function.o -c src/function.c

avr/utility.o: src/utility.c include/utility.h
	$(CC) $(COPTS) -o avr/utility.o -c src/utility.c

avr/error.o: src/error.c include/error.h
	$(CC) $(COPTS) -o avr/error.o -c src/error.c

clean:
	rm -f ub generic/*.o ub avr/*.o avrub

copy:
	rm -rf ~/ws1/Develop/ucBasic/*
	cp -r * ~/ws1/Develop/ucBasic
