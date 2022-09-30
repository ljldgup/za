import random
import re
from collections import defaultdict


def parse_line_values(insert_values: str):
    return list(filter(lambda x: x, re.sub(r'[\(\)\n;]', '', insert_values).split(',')))


def parse_values(lines: list):
    return list(filter(lambda x: x, (map(parse_line_values, filter(lambda x: x, lines)))))


def parse_file(file: str):
    with open(file, 'r', encoding='utf-8') as f:
        return parse_values(f.readlines())


def gen_dict_sql(line_values: list):
    type_sql_map = {}
    items_sql_map = defaultdict(list)
    for values in line_values:
        dict_type = values[4]
        code = values[7]
        if dict_type not in type_sql_map:
            type_sql_map[dict_type] = '({},{})'.format(dict_type, values[2])
        items_sql_map[dict_type].append('({},{},{},{})'.format(dict_type, code, values[6], values[5]))

    for dict_type in type_sql_map:
        print('insert into public.s_dict_type (type,description) values {};'.format((type_sql_map[dict_type])))

        for items_sql in items_sql_map[dict_type]:
            print('insert into public.s_dict_items (type,code,description,"order") values {};'.format(items_sql))
        print()


def get_device_type_sql(lines):
    rst = []
    for line in lines:
        line = re.sub(r"\s+", " ", line)
        name, topic_pattern, direction = line.split(" ")[:3]
        topic_suffix = topic_pattern.replace('/%s/%s', '')
        id = topic_suffix[1:].replace("/","_")
        print(
            'INSERT INTO public.dev_device_log_type (topic_pattern,topic_suffix,subtype,data_type,"name",id,"type",direction) '
            'VALUES (\'{}\',\'{}\',NULL,NULL,\'{}\',\'{}\',\'type\',\'{}\');'.format(
                topic_pattern, topic_suffix, name,
                id, direction))


if __name__ == '__main__':
    with  open(r'C:\Users\jlli.AGIOEMA\Desktop\device_type.txt', encoding='utf-8') as f:
        type_sql = get_device_type_sql(f.readlines())
    re.sub('([a_z])([A-Z])','\1\2','sadfS')