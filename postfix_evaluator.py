import token_checking

'''
`expression` is a list of tokens.
'''
def postfix_evaluator(expression):

    stack = []

    for element in expression:
        if element in ['+', '-', '*', '/']:
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

            elif token_checking.is_string(first_operand) and token_checking.is_string(second_operand):
                if element == '+':
                    result = first_operand[1:-1] + second_operand[1:-1]

            elif token_checking.is_string(first_operand) and token_checking.is_number(second_operand):
                if element == '*':
                    result = first_operand[1:-1] * int(second_operand)

            elif token_checking.is_string(second_operand) and token_checking.is_number(first_operand):
                if element == '*':
                    result = int(first_operand) * second_operand[1:-1]

            stack.append(result)

        else:
            stack.append(element)

    return stack[0]