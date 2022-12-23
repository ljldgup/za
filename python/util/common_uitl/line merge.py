import re


def merge(path1, path2, path3, column_num1, column_num2, keep_index=[]):
    f1 = open(path1, encoding='utf8')
    f2 = open(path2, encoding='utf8')
    f3 = open(path3, mode='w', encoding='utf8')
    context1 = f1.read().replace('\r\n', '\n')
    context2 = f2.read().replace('\r\n', '\n')
    lines1 = context1.split('\n')
    lines2 = context2.split('\n')
    table1 = list(map(lambda line: re.split(r'\s+', line), lines1))
    # print(list(table1))
    table2 = list(map(lambda line: re.split(r'\s+', line), lines2))
    # print(list(table2))
    # 这里可以通过加行号，然后hash，连接，再按行号排序来做，但复杂些,我对时间没要求所以直接嵌套循环
    for row1 in table1:
        for row2 in table2:
            if row1[column_num1] == row2[column_num2]:
                if not keep_index:
                    f3.write(" ".join(row1 + row2) + '\n')
                else:
                    t_row = row1 + row2
                    new_row = []
                    for idx in keep_index:
                        if idx < len(t_row):
                            new_row.append(t_row[idx])
                    f3.write(" ".join(new_row) + '\n')

    f1.close()
    f2.close()
    f3.close()


if __name__ == '__main__':
    merge(r'C:\Users\kmhqumenglian\Desktop\1',
          r'C:\Users\kmhqumenglian\Desktop\2',
          r'C:\Users\kmhqumenglian\Desktop\3',
          0, 0, [])
