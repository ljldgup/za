# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import urllib.request
import re
import os


httpproxy_handler = urllib.request.ProxyHandler({"http" : "cn-proxy.jp.oracle.com:80","https" : "cn-proxy.jp.oracle.com:80"})
nullproxy_handler = urllib.request.ProxyHandler({})
proxySwitch = True

if proxySwitch:
    opener = urllib.request.build_opener(httpproxy_handler)
else:
    opener = urllib.request.build_opener(nullproxy_handler)

header={
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept - Encoding': 'gzip, deflate, br',
        'Accept-Language': 'en-US,en;q=0.7,zh-CN;q=0.3',
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:60.0) Gecko/20100101 Firefox/60.0"
}


def getUrlList(url, regex):
    request = urllib.request.Request(url, headers=header)
    response = opener.open(request)
    html = response.read().decode('utf-8')
    rst = re.findall(regex, html)
    return rst

def getUrlBin(url, filename):
    try:
        request = urllib.request.Request(url, headers=header)
        response = opener.open(request)
        with open(filename, 'wb') as f:
            f.write(response.read())
    except Exception as e:
        print("failed:" + url)


if __name__ == "__main__":
    for word in ['hentai','milf','ahegao', 'orgasm', 'chikan']:

        try:
            os.mkdir(word)
        except:
            print("dir create failed")
        urls = getUrlList("https://www.google.com.hk/search?q=" + word + "&tbm=isch", "https:[^<>]*(?!=http)[^<>]*\.jpg")

        for i in range(word + "," + len(urls)):
            print(urls[i])
            getUrlBin(urls[i], word + '/' + str(i) + ".jpg")