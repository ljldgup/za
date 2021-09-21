import os
import re
from collections import defaultdict

'''
倒排索引 
保存的内容是 词-》文档-》位置
'''

# 嵌套默认值字典，第二层字典的value默认是list
words_to_files = defaultdict(lambda: defaultdict(list));


def re_split(file_path: str, pattern: str):
    with open(file_path, encoding='utf-8') as f:
        line_num = 1
        line = f.readline()

        while line:
            line = line.lower()
            words = re.split(pattern, line)
            words = list(filter(lambda x: len(x) > 1, words))
            for pos in range(len(words)):
                words_to_files[words[pos]][file_path].append((line_num, pos))
            # print(words)
            line_num += 1
            line = f.readline()


def build_reverse_index(root, pattern):
    words_to_files.clear()
    items = os.listdir(root)
    for item in items:
        path = os.path.join(root, item)
        path = os.path.abspath(path)
        print('build ' + path)
        if os.path.isdir(path):
            build_reverse_index(path, pattern)
        else:
            re_split(path, pattern)


def display_index():
    for word in words_to_files:
        print(word)
        for doc in words_to_files[word]:
            print(doc)
            for pos in words_to_files[word][doc]:
                print(pos)
        print("------------\n\n")


if __name__ == '__main__':
    # build_reverse_index('.', r'[^0-9.]+')
    build_reverse_index('.', r'[^a-zA-Z]+')

    display_index()
