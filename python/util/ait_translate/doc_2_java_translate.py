import re

from common_util import parse_file, dash_to_camel

"""
windows表格-》java
"""


def get_length(varchar):
    return re.search(r'\d+', varchar).group()


def gen_java(info):
    code = ""
    for record in info:
        record_len = len(record)
        if record_len < 3:
            print(str(record) + " 长度太小")
            continue

        if record_len >= 4:
            code += '@Comment("{}:{}")\n'.format(record[2], record[3])
        else:
            code += '@Comment("{}")\n'.format(record[2])

        code += '@Schema(description = "{}")\n'.format(record[2])
        if 'var' in record[1].lower():
            length = get_length(record[1])
            code += '@Column(length={})\n'.format(length)
            code += 'private String {};\n'.format(record[0])
        elif 'bool' in record[1].lower():
            code += '@Column\n'
            code += 'private Boolean {};\n'.format(record[0])
        elif 'int' in record[1].lower():
            code += '@Column\n'
            code += 'private Long {};\n'.format(record[0])
        else:
            code += '@Column\n'
            code += 'private String {};\n'.format(record[0])
        code += '\n'
    return code


if __name__ == '__main__':
    # doc表复制出来，格式：menu_id	varchar(64)	菜单id
    t = parse_file(r"temp.txt")
    t = list(map(
        lambda x: list(map(dash_to_camel, x)), t))
    code = gen_java(t)
    with open("temp.java", 'w') as f:
        f.writelines(code)
    f.close()
