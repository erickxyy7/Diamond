Operators = set(['or', 'and', '==', '!=', '<', '<=', '>', '>=', '<-', '+', '-', '*', '/', '(', ')'])

Priority = {'or': 1,
            'and': 2,

            '==': 3,
            '!=': 3,
            '<': 4,
            '<=': 4,
            '>': 4,
            '>=': 4,

            '+': 5,
            '-': 5,
            '*': 6,
            '/': 6,

            '<-': 7}

def expr_infix_to_postfix(expression):

    stack = []

    output = []

    for character in expression:

        if character not in Operators:
            output.append(character)

        elif character=='(':
            stack.append('(')

        elif character==')':
            while stack and stack[-1]!= '(':
                output.append(stack.pop())
            stack.pop()

        else:
            while stack and stack[-1]!='(' and Priority[character]<=Priority[stack[-1]]:
                output.append(stack.pop())
            stack.append(character)

    while stack:
        output.append(stack.pop())

    return output

'''
Takes an entire program as argument (`tokens`) and converts the infix expressions
to postfix.
'''
def infix_to_postfix(tokens):
    new_tokens = []
    i = 0
    tokens_length = len(tokens)
    while i < tokens_length:

        if tokens[i] == '=':
            new_tokens.append(tokens[i])
            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1
            postfix = expr_infix_to_postfix(expression)
            new_tokens += postfix + [';']
            i += 1
            continue

        if tokens[i] == 'if' or tokens[i] == 'while':
            new_tokens.append(tokens[i])
            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1
            postfix = expr_infix_to_postfix(expression)
            new_tokens += postfix + [';']
            i += 1
            continue

        if tokens[i] == 'puts':
            new_tokens.append(tokens[i])
            expression = []
            i += 1
            while tokens[i] != ';':
                expression.append(tokens[i])
                i += 1
            postfix = expr_infix_to_postfix(expression)
            new_tokens += postfix + [';']
            i += 1
            continue

        new_tokens.append(tokens[i])
        i += 1

    return new_tokens