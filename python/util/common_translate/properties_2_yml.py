import re
from functools import reduce


def set_property(properties_map, words):
    if len(words) < 2:
        return
    if len(words) == 2:
        properties_map[words[0]] = words[1]
        return

    if words[0] not in properties_map:
        properties_map[words[0]] = {}
    set_property(properties_map[words[0]], words[1:])


def split_property_line(line: str):
    prop = line.split("=")
    ans = []
    ans += prop[0].split('.')
    ans.append(prop[1])
    return ans


def split_properties(path):
    with open(path, encoding='utf-8') as f:
        properties = f.readlines()
    properties = filter(lambda p: not p.startswith("#"), map(lambda p: re.sub(r"\s+", "", p), properties))
    properties_map = {}
    for property_line in properties:
        words = split_property_line(property_line)
        set_property(properties_map, words)
    return properties_map


def map_2_yml(properties, padding=""):
    def get_property_head(key):
        return "{}{}:".format(padding, key)

    def map_2_yml_helper(k):
        new_properties = properties[k]
        if type(new_properties) is str:
            return "{}{}:  {}".format(padding, k, new_properties)
        else:
            return "{}\n{}".format(get_property_head(k), map_2_yml(properties[k], '  ' + padding))

    return reduce(lambda a, b: "{}\n{}".format(a, b),
                  map(map_2_yml_helper, properties.keys()))


if __name__ == '__main__':
    path =r'test.properties'
    prop_map = split_properties(path)
    yml_txt = map_2_yml(prop_map)
    # with open(path+".yml",'w',encoding='utf-8') as f:
    #     f.writelines(yml_txt)
    print(yml_txt)


