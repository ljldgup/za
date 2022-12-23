import re

import pandas as pd

arg_translate = {}
arg_translate[r'device:\d+'] = "device"
arg_translate[r'device-product-bind:\d+'] = "device-product-bind"
arg_translate[r'/rule-engine/'] = "rule-engine"
arg_translate[r'device_property_\d+'] = "device_property"


def parse_record(line):
    words = re.split(r'\s+', line)
    record = {}
    try:
        record['time'] = int(float(words[0]))
        record['cmd'] = words[3]
        for pat, val in arg_translate.items():
            if re.search(pat, words[4]):
                record['arg1'] = val
                break
        else:
            record['arg1'] = words[4]
        record['arg2'] = words[5]

    except Exception as e:
        print("ecpect:", e, ",", line)

    return record


def parse_file(path):
    with open(path, 'r') as f:
        return list(filter(lambda x: x, map(parse_record, f)))


if __name__ == '__main__':
    data = pd.DataFrame(parse_file('pre_monitor.txt'))
    data.groupby(['time']).count()

    t = data.groupby(['cmd', 'arg1']).count()
    tt = t[t['time'] > 100]
    tt.plot.pie(y='time')

    t = data[data['arg1'] == 'device'].groupby(['cmd', 'arg2']).count()
    tt = t[t['time'] > 100]
    tt.plot.pie(y='time')

    t = data[data['arg1'] == 'device_property'].groupby(['cmd', 'arg2']).count()
    tt = t[t['time'] > 100]
    tt.plot.pie(y='time', labels=tt['time'])
