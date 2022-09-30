import re


def parse_file(path):
    rst = []
    with open(path, encoding='utf-8') as f:
        lines = f.readlines()
        for line in lines:
            rst.append(re.split(r'\s+', line))
    return rst


def dash_to_camel(word):
    def upper_first_ch(w):
        return w[0].upper() + w[1:]

    words = word.split("_")
    return "".join([words[0]] + list(map(upper_first_ch, words[1:])))


def get_entity_json(info):
    result = "{\n"
    context = ""
    for r in info:
        if len(r) >= 3:
            context += "\"{}\":\"\" //{}\n".format(r[0], r[2])

    return result + context + "}\n"


if __name__ == '__main__':
    t = parse_file(r"C:\Users\jlli.AGIOEMA\Desktop\user.txt")
    t = list(map(
        lambda x: list(map(dash_to_camel, x)), t))
    entity_json = get_entity_json(t)
    with open("temp.json", 'w', encoding='gbk') as f:
        print(entity_json, file=f)
    f.close()
