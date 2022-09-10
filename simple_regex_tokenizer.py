'''
Quick and simple Regex tokenizer. Useful for development.
'''

import re

def tokenizer(program):
  regex = r"[a-zA-Z_][a-zA-Z0-9_]*|[0-9.]{1,65535}|[;]|={2,2}|=|[*+-\/]|\n|'.*?'|\".*?\""

  matches = re.finditer(regex, program, re.MULTILINE)

  tokens = []
  for matchNum, match in enumerate(matches, start=1):
      tokens.append(match.group())
  
  i = 0
  l = len(tokens)
  while i < l:
    if tokens[i] == '\n':
      tokens[i] = ';'
    i += 1

  if tokens[-1] != ';':
    tokens.append(';')

  return tokens

if __name__ == '__main__':
  print(tokenizer('foo = 4 4 =='))
