import os

if __name__ == '__main__':
    dir = r'C:\Users\jlli.AGIOEMA\Desktop\backup'
    files = os.listdir(dir)
    with open('merge.txt', 'w') as m:
        for file in files:
            path = os.path.join(dir,file)
            if not os.path.isfile(path):
                continue

            print(path)

            with open(path,encoding='utf-8') as f:
                lines = f.readlines()
                m.writelines(lines)

