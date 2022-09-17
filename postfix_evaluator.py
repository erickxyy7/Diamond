import token_checking

def replace_identifiers_with_values(data, expression):
    i = 0
    l = len(expression)
    while i < l:

        if expression[i].isidentifier():
            j = -1
            len_data = len(data)
            while j >= (-1 * len_data):
                if data[j].name == expression[i]:
                    expression[i] = data[j].value
                j -= 1

        i += 1
    return expression

'''
`expression` is a list of tokens.
'''
def postfix_evaluator(data, expression):

    expression = replace_identifiers_with_values(data, expression)

    stack = []

    for element in expression:
        if element in ['+', '-', '*', '/',
                       '==', '!=', '<', '<=', '>', '>=',
                       '<-']:
            second_operand = stack.pop()
            first_operand = stack.pop()

            if token_checking.is_number(first_operand) and token_checking.is_number(second_operand):
                if element == '+':
                    result = float(first_operand) + float(second_operand)
                elif element == '-':
                    result = float(first_operand) - float(second_operand)
                elif element == '*':
                    result = float(first_operand) * float(second_operand)
                elif element == '/':
                    result = float(first_operand) * float(second_operand)
                elif element == '==':
                    result = float(first_operand) == float(second_operand)
                elif element == '!=':
                    result = float(first_operand) != float(second_operand)
                elif element == '<':
                    result = float(first_operand) < float(second_operand)
                elif element == '<=':
                    result = float(first_operand) <= float(second_operand)
                elif element == '>':
                    result = float(first_operand) > float(second_operand)
                elif element == '>=':
                    result = float(first_operand) >= float(second_operand)

            elif token_checking.is_string(first_operand) and token_checking.is_string(second_operand):
                if element == '+':
                    result = first_operand[1:-1] + second_operand[1:-1]
                elif element == '==':
                    result = first_operand[1:-1] == second_operand[1:-1]
                elif element == '!=':
                    result = first_operand[1:-1] != second_operand[1:-1]

            elif token_checking.is_string(first_operand) and token_checking.is_number(second_operand):
                if element == '*':
                    result = first_operand[1:-1] * int(second_operand)
                elif element == '<-':
                    result = "'" + first_operand[1:-1][int(float(second_operand))] + "'"

            elif token_checking.is_string(second_operand) and token_checking.is_number(first_operand):
                if element == '*':
                    result = int(first_operand) * second_operand[1:-1]

            stack.append(result)

        else:
            stack.append(element)

    return stack[0]