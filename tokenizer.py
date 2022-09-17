import re

regex = r"<-|\n|(\".*?[^\\]\")|('.*?[^\\]')|>=|<=|[<>]|(!=)|={2,2}|((?<![0-9\.])-[0-9\.]+|[0-9\.]+)|[\+\-\*/=]|[a-zA-Z0-9_]{1,1000}"

def tokenizer(source_code):
    matches = re.finditer(regex, source_code, re.MULTILINE)
    tokens = []
    for matchNum, match in enumerate(matches, start=1):
        tokens.append(match.group())
    
    '''
    Replace '\n' with ';'.
    '''
    i = 0
    tokens_length = len(tokens)
    while i < tokens_length:
        if tokens[i] == '\n':
            tokens[i] = ';'
        i += 1
    
    '''
    Append ';' into the end of `tokens` if it doesn't have.
    '''
    if tokens[-1] != ';':
        tokens.append(';')
    
    return tokens