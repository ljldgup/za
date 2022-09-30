import re

from common_util import parse_file, dash_to_camel


def get_length(varchar):
    return re.search(r'\d+', varchar).group()


def gen_java(info):
    code = ""
    for record in info:
        if len(record) < 3:
            print(str(record) + " 长度太小")
            continue

        code += '@Comment("{}")\n'.format(record[2])
        code += '@Schema(description = "{}")\n'.format(record[2])
        if 'var' in record[1].lower():
            length = get_length(record[1])
            code += '@Column(length={})\n'.format(length)
            code += 'private String {};\n'.format(record[0])
        elif 'bool' in record[1].lower():
            code += '@Column\n'
            code += 'private Boolean {};\n'.format(record[0])
        elif 'int8' in record[1].lower():
            code += '@Column\n'
            code += 'private Long {};\n'.format(record[0])
        else:
            code += '@Column\n'
            code += 'private String {};\n'.format(record[0])
        code += '\n'
    return code


if __name__ == '__main__':
    t = parse_file(r"C:\Users\jlli.AGIOEMA\Desktop\user.txt")
    t = list(map(
        lambda x: list(map(dash_to_camel, x)), t))
    code = gen_java(t)
    with open("temp.java", 'w') as f:
        f.writelines(code)
    f.close()
