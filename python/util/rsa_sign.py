import urllib
import uuid

import rsa
import base64
import json
import requests
from datetime import datetime
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
# 关键在这里 使用Crypto模块中的pkcs1_v1_5。就是对应pkcs8的格式了
# from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
from Crypto.Signature import PKCS1_v1_5 as Signature_pkcs1_v1_5

__pem_begin = "-----BEGIN RSA PRIVATE KEY-----\n"
__pem_end = "\n-----END RSA PRIVATE KEY-----"


def sign(content, private_key, sign_type):
    if sign_type.upper() == "RSA":
        return rsa_sign(content, private_key, "SHA-1")
    elif sign_type.upper() == "RSA2":
        return rsa_sign(content, private_key, "SHA-256")
    else:
        raise Exception("sign_type错误")


# 这几个函数用的load_pkcs1 测试秘钥是pkcs8没办法正常工作，使用openssl生成的证书可以工作
def rsa_sign(content, private_key, _hash):
    private_key = _format_private_key(private_key)
    pri_key = rsa.PrivateKey.load_pkcs1(private_key.encode("utf-8"))
    sign_result = rsa.sign(content, pri_key, _hash)
    return base64.b64encode(sign_result)


def _format_private_key(private_key):
    if not private_key.startswith(__pem_begin):
        private_key = __pem_begin + private_key
    if not private_key.endswith(__pem_end):
        private_key = private_key + __pem_end
    return private_key


def pkcs8_rsa2_sign(key_str: str, content: str):
    # Cipher_pkcs1_v1_5 使用的pkcs8和java一致
    key_bytes = bytes(key_str, encoding="utf-8")
    key_bytes = base64.b64decode(key_bytes)
    rsakey = RSA.importKey(key_bytes)

    """
    cipher = Cipher_pkcs1_v1_5.new(rsakey)
    print(cipher.encrypt("这里太长会报错".encode("utf8")))
    """

    signer = Signature_pkcs1_v1_5.new(rsakey)
    digest = SHA256.new()
    digest.update(content.encode())
    sign = signer.sign(digest)
    signature = base64.b64encode(sign)
    return signature


# 排序,对字典类型json化，签名
def json_sign_params(private_key:str, url, params: dict):
    rst = ""
    for key in sorted(params.keys()):
        if type(params[key]) != str:
            params[key] = json.dumps(params["biz_content"]).replace(" ", "")
        rst += "{}={}&".format(key, params[key])

    params['sign'] = pkcs8_rsa2_sign(private_key, '?'.join([url,rst[:-1]])).decode()


if __name__ == "__main__":
    # print(sign("签名内容".encode(), test_private_key, "RSA2"))
    # print(sign("签名内容".encode("utf-8"), test_private_key, "RSA2"))

    # icbc_url = "https://gw.open.icbc.com.cn"
    icbc_url = "https://apipcs3.dccnet.com.cn"
    # icbc_url = "http://localhost"
    url = "/api/mybank/pay/digitalwallet/submerchantquery/V1"
    test_private_key = ""
    request_params = {
        "charset": "UTF-8",
        "biz_content": {
            "chantype": 39,
            "merchant_id": "M00000022",
            "instruction_id": "1",
            "channel_id": "3324"
        },
        "format": "json",
        "msg_id": 'd501c538ab7a4dc5863cbff448a2eba5',
        "app_id": "10000000000000197026",
        "sign_type": "RSA2",
        "timestamp": "2021-01-10 00:22:41"
        # "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    }

    # 对字典类型json化，排序签名
    json_sign_params(test_private_key,url, request_params)
    body = urllib.parse.urlencode(request_params).replace("+", "%20")
    rst = requests.post(icbc_url + url, data=request_params)

    """
    print(rst.request.headers)
    print(rst.request.url)
    print(rst.request.body)
    """

    """
    data = urllib.parse.urlencode(request_params)
    data = data.encode()
    rst = urllib.request.urlopen(url=icbc_url + url, data=data)
    """
    print(rst.json())
