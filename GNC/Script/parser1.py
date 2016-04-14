#!/usr/bin/python
#returns the name that is merged in configure.ac
import sys
from pyparsing import Word, Optional, alphanums

input_text = sys.argv[1]

name = Word( alphanums )
version =  Word ( alphanums + '.' )
bug_report = Word ( alphanums )
tar_name = Word ( alphanums )

ac_expr = Word('AC_INIT') + Word('(') + Word('[') + name + Word(']') + Word(',') + Word('[') + version + Word(']') + Optional(Word(',') + Word('[') + bug_report + Word(']')) + Optional(Word(',') + Word('[') + tar_name + Word(']')) + Word(')')

ac_parsed = ac_expr.parseString(str(input_text))

print ac_parsed[3]
