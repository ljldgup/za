# -----------------------------------------------------------
# calclex.py
#
# tokenizer for a simple expression evaluator for
# numbers and +,-,*,/
# ------------------------------------------------------------
import ply.lex as lex

# 优先级控制（方法根据出现的顺序，靠前的优先，而字符串的正则表达式依据正则表达式的长度）
# List of token names.   This is always required
tokens = (
    'NUMBER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIVIDE',
    'LPAREN',
    'RPAREN',
)

# t_token名称， 函数则正则表达式放在文档字符串中
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_LPAREN = r'\('
t_RPAREN = r'\)'


# A regular expression rule with some action code
def t_NUMBER(t):
    r'[\-]{0,1}\d+'
    t.value = int(t.value)
    return t


# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)


# A string containing ignored characters (spaces and tabs)
t_ignore = ' \t'


# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


# Build the lexer
lexer = lex.lex()

# Yacc example

import ply.yacc as yacc

# 优先级按照定义的顺序来，越后面的优先级越高
# 从文档字符串中取
def p_expression_plus(p):
    'expression : expression PLUS term'
    #   ^            ^        ^    ^
    #  p[0]         p[1]     p[2] p[3]
    # 这里expression，term不代表具体的值，只用来指代表达式的一部分，
    # 左边的expression是加法结果，结合右边的expression说明 expression PLUS term结果还能作为expression来用，即这是一个递归定义
    p[0] = p[1] + p[3]

def p_expression_minus(p):
    'expression : expression MINUS term'
    p[0] = p[1] - p[3]

def p_expression_term(p):
    'expression : term'
    p[0] = p[1]

def p_term_times(p):
    'term : term TIMES factor'
    p[0] = p[1] * p[3]

def p_term_div(p):
    'term : term DIVIDE factor'
    p[0] = p[1] / p[3]

def p_term_factor(p):
    'term : factor'
    p[0] = p[1]

def p_factor_num(p):
    'factor : NUMBER'
    p[0] = p[1]

def p_factor_expr(p):
    'factor : LPAREN expression RPAREN'
    p[0] = p[2]

# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")

# Build the parser
parser = yacc.yacc()




if __name__ == '__main__':
    # Test it out
    data = '''
    3 + -4 * 10
      + -20 *2
    '''

    # Give the lexer some input
    lexer.input(data)

    # Tokenize
    while True:
        tok = lexer.token()
        if not tok: break  # No more input
        print(lexer.lineno, ':', tok)

    # while True:
    #     try:
    #         s = input('calc > ')
    #     except EOFError:
    #         break
    #     if not s: continue
    #     result = parser.parse(s)
    #     print(result)
    result = parser.parse(data)
    print(result)

