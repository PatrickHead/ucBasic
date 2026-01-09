#ucBasic

<b>ucBasic</b> is a very small basic interpreter intended for use in micro controllers
and micro controller based development boards.  This version is inspired by
Tiny BASIC by Dennis Allison.  Although this version does deviate and extend
Tiny BASIC, it syntactically maintains most of the same language elements.
This implementation is a pure interpreter, omitting the use of any intermediate
language virtual machine.  Also, this version is written in GNU/ANSI C
entirely.

The interpreter design uses many of the concepts developed and documented in
tutorial form by Jack W. Crenshaw PHD.  ucBasic is a pure recursive descent
parsing interpreter, with the code organized basically in two components.  The
first part being a lexicon, or list of program language "words", which is
really a pattern matching library.  The second part is a grammatical parser.

Other code modules are also added to provide utility functionality, such as
program data maintenance and control, a separate ucBasic function library, an
error library, etc.

Also, a deviation, or maybe more of an extension of the Crenshaw plan, is
incorporated into the design of ucBasic.  ucBasic has two complete lexicons and
grammars.  The first comprising the main language elements used during program
and single statement execution.   The second is provided exclusively for
interactive command line elements.  This abstraction is provided to make it
easier to omit the interactive CLI components if the final size of the
interpreter dictates, or if the CLI functionality is just not necessary in an
implementation.

