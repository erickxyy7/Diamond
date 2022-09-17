'''
Checks if a token is a number.
'''
def is_number(token):
    try:
        float(token)
        return True
    except ValueError:
        return False

'''
Checks if a token is a string.
'''
def is_string(token):
    if not isinstance(token, str):
        return False
    if len(token) < 2:
        return False
    if token[0] == '"' and token[-1] == '"':
        return True
    if token[0] == "'" and token[-1] == "'":
        return True
    return False

'''
Checks if a token is true or false. E.g: '0' is false.
'''
def boolean_value(token):
    if is_number(token):
        if float(token) == 0:
            return False
        return True

    if is_string(token):
        if len(token) == 2:
            return False
        return True