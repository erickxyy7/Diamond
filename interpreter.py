from postfix_evaluator import postfix_evaluator
from utils import find_end_equivalent
from utils import find_token_of_end
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

            result = postfix_evaluator(data, expression)

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

            result = postfix_evaluator(data, expression)

            if token_checking.boolean_value(result) == True:
                i += 1
                continue

            end_pos = find_end_equivalent(tokens, i)
            i = end_pos + 2
            continue

        if tokens[i] == 'end':
            token_of_end = find_token_of_end(tokens, i)

            if tokens[token_of_end] == 'while':
                i = token_of_end
                continue

        if tokens[i] == 'break':
            '''
            Finds the `while` of this `break` and skips to the `end` of this `while`.
            '''
            i -= 1
            while tokens[i] != 'while':
                i -= 1

            skip_to = find_end_equivalent(tokens, i) + 2
            i = skip_to
            continue

        if tokens[i] == 'continue':
            '''
            Finds the `while` of this `continue` and continues from it.
            '''
            i -= 1
            while tokens[i] != 'while':
                i -= 1
            continue

        if tokens[i] == 'puts':
            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1

            result = postfix_evaluator(data, expression)

            print(result)

        i += 1



'''
This is for development and tests purposes.
'''
if __name__ == '__main__':

    some_tokens = ['foo', '=', '"oi"', '0', '<-', ';', 'foo', '=', '4', ';', 'foo', '=', 'foo', 'foo', '*', ';']

    interpreter(some_tokens)
