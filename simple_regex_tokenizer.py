'''
Quick and simple Regex tokenizer. Useful for development.
'''

import re

def tokenizer(program):
  regex = r"[a-zA-Z_][a-zA-Z0-9_]*|[0-9.]{1,65535}|[;]|={2,2}|!=|=|<=|<|>=|>|[*+-\/]|\n|'.*?'|\".*?\""

  matches = re.finditer(regex, program, re.MULTILINE)

  tokens = []
  for matchNum, match in enumerate(matches, start=1):
      tokens.append(match.group())

  i = 0
  while i < len(tokens):
    if tokens[i] == '\n':
      tokens[i] = ';'
    i += 1

  i = 0
  while i < len(tokens):
    if tokens[i] == 'then':
      tokens[i] = ';'
    i += 1

  if tokens[-1] != ';':
    tokens.append(';')

  return tokens

if __name__ == '__main__':

  import sys

  if len(sys.argv) == 1:
    print('Usage: python3 %s program_name.lang' % (sys.argv[0]))
    exit()

  with open(sys.argv[1], 'r') as program_file:
    program = program_file.read()

  tokens = tokenizer(program)

  print(tokens)
