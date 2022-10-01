import os
if __name__ == '__main__':
    filename = os.fspath('../fefe')
    print(filename)
    print(os.path.abspath(filename))