from postfix_evaluator import postfix_evaluator
from utils import find_end_equivalent
import token_checking

class Lang_obj:
    def __init__(self, name, value):
        self.name = name
        self.value = value

def interpreter(tokens):

    data = []

    i = 0
    tokens_length = len(tokens)
    while i < tokens_length:

        if tokens[i] == '=':
            name = tokens[i-1] # name of the variable

            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1

            result = postfix_evaluator(expression)

            '''
            If a variable with the name `name` already exists, updates it, if not exists,
            creates a new one.
            '''
            variable_exists = False
            j = -1
            len_data = len(data)
            while j >= (-1 * len_data):
                if data[j].name == name:
                    variable_exists = True
                    break
                j -= 1

            if variable_exists:
                data[j].value = result
            else:
                lang_obj = Lang_obj(name, result)
                data.append(lang_obj)

        if tokens[i] == 'if' or tokens[i] == 'while':

            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1

            result = postfix_evaluator(expression)

            if token_checking.boolean_value(result) == True:
                i += 1
                continue

            end_pos = find_end_equivalent(tokens, i)
            i = end_pos + 2
            continue

        i += 1

    i = 0
    while i < len(data):
        print('%s: %s\n' % (data[i].name, data[i].value))
        i += 1



'''
This is for development and tests purposes.
'''
if __name__ == '__main__':

    some_tokens = ['if', '10', '10', '-', ';', 'foo', '=', '9', ';', 'end', ';']

    interpreter(some_tokens)
