import ply.lex as lex

# 优先级控制（方法根据出现的顺序，而字符串的正则表达式依据正则表达式的长度）

# List of token names.   This is always required
tokens = (
    'KEY',
    'VALUE',
    'ARRAY_MARK',
)

# Can't build lexer多半正则有问题
line_start_pos = 0

def t_KEY(t):
    r'.+:'
    return t

def t_ARRAY_MARK(t):
    r'-'
    return t

def t_VALUE(t):
    r'[^-:\r\n]+'
    return t



def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


# Build the lexer
lexer = lex.lex()

if __name__ == '__main__':

    data = '''
    config:
     demo:
      value: testValue

      simpleConfig:
       config: testConfig
  
      str1: abc,cde
      str2:
       - abc
       - cde
    '''

    # Give the lexer some input
    lexer.input(data)

    # Tokenize
    while True:
        tok = lexer.token()
        if not tok:
            break  # No more input
        print(tok)


