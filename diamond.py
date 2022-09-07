import os
import json
from simple_regex_tokenizer import tokenizer

if len(os.sys.argv) == 1:
  exit()

program_name = os.sys.argv[1]
with open(program_name, 'r') as file:
  program = file.read()

tokens = tokenizer(program)

with open('.tokens.h', 'w') as file:
  file.write('char *tokens[] = ')
  t = json.dumps(tokens)
  t = '{' + t[1:-1] + '};'
  file.write(t)
  file.write('\nunsigned int tokens_length = %d;' % (len(tokens)))

os.system('gcc main.c -std=c11')
