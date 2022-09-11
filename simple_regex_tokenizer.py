'''
Quick and simple Regex tokenizer. Useful for development.
'''

import re

from infix_to_postfix import infix_to_postfix

def tokens_infix_to_postfix(tokens):
  
  new_tokens = []
  i = 0
  while i < len(tokens):
    
    if tokens[i] == '=':
      new_tokens.append(tokens[i])
      
      expression = []
      i += 1
      while tokens[i] != ';':
        expression.append(tokens[i])
        i += 1
      
      new_tokens += infix_to_postfix(expression) + [';']
      i += 1
      continue
    
    if tokens[i] == 'if':
      new_tokens.append(tokens[i])
      
      expression = []
      i += 1
      while tokens[i] != ';':
        expression.append(tokens[i])
        i += 1
      
      new_tokens += infix_to_postfix(expression) + [';']
      i += 1
      continue
    
    if tokens[i] == 'while':
      new_tokens.append(tokens[i])
      
      expression = []
      i += 1
      while tokens[i] != ';':
        expression.append(tokens[i])
        i += 1
      
      new_tokens += infix_to_postfix(expression) + [';']
      i += 1
      continue
    
    new_tokens.append(tokens[i])
    i += 1
  
  return new_tokens

def double_end_of_command_remotion(tokens):
  new_tokens = []
  for token in tokens:
    new_tokens.append(token)
    if len(new_tokens) > 2:
      if new_tokens[-1] == ';' and new_tokens[-2] == ';':
        del new_tokens[-1]
  return new_tokens

def tokenizer(program):
  regex = r"<-|[a-zA-Z_][a-zA-Z0-9_]*|[0-9.]{1,65535}|[;]|={2,2}|!=|=|<=|<|>=|>|[*+-\/]|\(|\)|\n|'.*?'|\".*?\""

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

  tokens = double_end_of_command_remotion(tokens)
  tokens = tokens_infix_to_postfix(tokens)

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
