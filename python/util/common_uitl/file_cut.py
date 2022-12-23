import os


def cut_file(src, dest, bytes_start, bytes_count=None):
    s = open(src, 'rb')
    d = open(dest, 'wb')
    s.seek(bytes_start)
    if bytes_count:
        d.write(s.read(bytes_count))
    else:
        d.write(s.read())
    s.close()
    d.close()


if __name__ == '__main__':
    os.chdir("C:/Users/kmhqumenglian/Desktop")
    cut_file('2.jpg', '2.7z', 331634)
