import json

sql_format = "INSERT INTO public.s_menu (id,title, name, icon,  \"path\", parent_id, hidden_item,\"order\", \"type\") values" \
             "({},{},{},{},{},{},{},{},{});"

wrap_quote = "\'{}\'"


def generator_n(n: int):
    for i in range(n):
        yield i


id_generator = generator_n(10000)


def gen_menu_sql(item):
    if 'id' not in item or item["id"] != '-1':
        item["id"] = next(id_generator)

    if 'parent_id' not in item:
        item['parent_id'] = '-1'
        item['level'] = 0

    if "hiddenItem" in item:
        item["hiddenItem"] = "true"
    else:
        item["hiddenItem"] = "false"

    columns = ["icon", "path", "type"]
    for c in columns:
        if c not in item:
            item[c] = "NULL"

    values = tuple(map(lambda s: s if "NULL" == s else wrap_quote.format(s),
                       [item["id"], item["title"], item["name"], item["icon"], item["path"],
                        item['parent_id'], item["hiddenItem"], item["order"], item["type"]]))
    sql = sql_format.format(*values)

    if item["order"]: print(sql)

    if 'children' not in item:
        return

    order = 1
    for child in item['children']:
        child['parent_id'] = item['id']
        child['level'] = item['level'] + 1

        child['order'] = item["order"] + str(order)
        order += 1
        gen_menu_sql(child)


if __name__ == '__main__':
    with open('menu.json', encoding='utf-8') as f:
        menu_json = json.loads(f.read())
        root = {'id': '-1', 'title': '虚拟根目录', 'name': 'root', 'type': 'dummy', 'order': 1}
        root['children'] = menu_json
        root['order'] = ""
        for menu in menu_json: menu['parent_id'] = '-1'
        gen_menu_sql(root)
