'''
Starting point of executing an arbitrary program.
'''

from tokenizer import tokenizer
from infix_to_postfix import infix_to_postfix
from interpreter import interpreter

if __name__ == '__main__':
    import sys

    if len(sys.argv) < 2:
        print('In order to execute a program, use: python3 %s program_name' % (sys.argv[0]))
        exit()

    program_name = sys.argv[1]
    with open(program_name, 'r') as program:
        source_code = program.read()

    tokens = tokenizer(source_code)
    tokens = infix_to_postfix(tokens)
    interpreter(tokens)