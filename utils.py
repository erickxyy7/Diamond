'''
Finds the `end` equivalent of a block of code opening.
'''
def find_end_equivalent(tokens, block_opening):
    i = block_opening
    gauge = 0
    while True:
        i += 1
        if tokens[i] == 'if' or \
           tokens[i] == 'while' or \
           tokens[i] == 'fn':
            gauge += 1
        elif tokens[i] == 'end':
            if gauge == 0:
                return i
            gauge -= 1
