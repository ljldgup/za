if __name__ == '__main__':
    # type 可以生成匿名类,名称，基类，
    newClass = type('Dummy', (object,), {"attr1": "somehing", "attr2": 344})
    t = newClass()
    print(t.attr1)
    t.attr3 = {1:2}
    print(t.attr3)

    # 直接在object上动态添加属性添加有可能无法成功，原因不明
    t = object()
    setattr(t,'attr3', {1:2})
    print(t.attr3)