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

def infix_to_postfix(expression):

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

if __name__ == '__main__':
  print(infix_to_postfix(["'oi'", '0', '<-']))
