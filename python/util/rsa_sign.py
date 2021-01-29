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
def json_sign_params(private_key: str, url, params: dict):
    rst = ""
    for key in sorted(params.keys()):
        if type(params[key]) != str:
            # ensure_ascii=False 避免将中文转成ascii
            params[key] = json.dumps(params["biz_content"], ensure_ascii=False).replace(" ", "")
        rst += "{}={}&".format(key, params[key])

    params['sign'] = pkcs8_rsa2_sign(private_key, '?'.join([url, rst[:-1]])).decode()


if __name__ == "__main__":
    # print(sign("签名内容".encode(), test_private_key, "RSA2"))
    # print(sign("签名内容".encode("utf-8"), test_private_key, "RSA2"))

    # icbc_url = "https://gw.open.icbc.com.cn"
    icbc_url = "https://apipcs3.dccnet.com.cn"
    # icbc_url = "http://localhost"
    url = "/api/mybank/pay/digitalwallet/submerchantadd/V1"
    test_private_key = "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCm5Ow1+14YePTGcMrBJHv0c5/R0L4t9M7voxWZiZwe1J/WWuR14FkRZL0FSL+cRcSCWk/dNj2bV5aRcWLP5xcsX3HOmeQkMGryGGRXgAWAWb0ZPYSlSQFho0STpHGgvl77M2e0bHUDGSXH1+MX46I7XddzFoqCWu713CKBG7ZR8aS8sFrV+IWuU2X5+fVQGIkIpueJQNivCaTWray3Rs9QJRRWMls4LHXlnFbJ/DFN3IqHQTtA6qRL+49Jar6iJxKw9zEK78Txl77nY8VXxUUyVRLtSVCjsd1M+aZMaultihy6rkrw24lhceRMLzP+EcESx4lIPNIwe3HTCLEBht7dAgMBAAECggEBAKPo3yihSKfGW7htXGRWnbrWuBcL6UwfTAHE7NjPctpAvv56ZDh072UKyC3hZfZn+vh/FELRG65uVn1fm8lOT88PqilbsNnuB4rfc+UP4ddNy093wMfILKgk/pv2fHZ/oa8arHZhsoYpc5aTLADxWwrtPkVU1RHzlw82dVjRy70rfTYSppLDhHwiINoV+f0GNUxKVDW0oUW4q/VruEXFk8KNjJ5J+46TcLh7VGW+XJ3XkDvEdaBhs/u6rpTcTRKpOLgkU4jL2AhgT+5wOadnPS2VIMGVZm76rDQkzWH44DRVmcj0u+BFwBhmiQ+ysGgdPlNXbEzZVM5QVWBaH4ewZ2ECgYEA0E8x5g7XHDR00KnoBnPSgU2EhxGhPajKBCj0edyMAht/NsE+oLZ5aYeUlG2EIyhLKn6r6Mw9fi+aGuqSthxT3+050k49356BzYz5KBy4tN93nT4ryaM7Bhe0e4Rk+ack9Ozy4rqnA1yvRYaLT9lMyDSSULWasN02caVeHq3QELkCgYEAzRptoi5mtC7yQU+dA/rg03qfqg83LmL2yMwkqr6keYvXZfwMt/iKqVUZ3UydyFwk1nwS6IVDsmKX9V9ioIxCVb9ldO0RyycmoWDX2tQvJOvChydQLrEi3u3FGnabQqM3b41eekzw5U56L/ymxjoe/S9euchla/oY+BPtVdY0xUUCgYAkqfu/YVdNOJJi87TKBfLEHW+5EkpN/vpnlwnItR/TcyGF8qdiRBvEjj+BjHEYewwX06nQVLpyDlDScf0Wno/ItwlZUbokNNLl6e0kuUFtXHPCMmIkoF1QKjXzE49uPZQMo/PwIigpOFQFKbQ1fqq8BjzGheBPRvBBOnkBb1hSyQKBgQC9FToxI9nnDsijUUQNoUGXdRqw6qoSh4W/hAPhrTNwIm2HRaBsEiOzDBN2IuXrCpejbGr6FbFdSOuSeEcyf1vANVzROKUIxqUkbWVSBf8YaIjDlIilIwRkxIrLZMCp5FJ88rVAxqHmpDyc9KzDXl2nR/5qA8cMjlpqieRpF7s6iQKBgQCsRRDW8wmJDMr6lkrzhXeI+J+9ve3EGFm+f0X6h6LMIVkXAJwDzRt/GIQSJ9Y99pv1bxWUpbmDWzhUTtRrrmwUaNvys9B+ErqMpge6vTxNwkhFcJuRBzaal23fndPrPyU5bUUH7b4CorsA1GQo5sErBfRKVL3D3kjhBQ0x+1KVoQ=="

    request_params = {"charset": "UTF-8",
                      "biz_content": {
                          "pos_type": 110,
                          "contact_name": "张",
                          "contact_phone": "15618030321",
                          "wallet_name": "数字钱包",
                          "merchant_remark": "test",
                          "merchant_name": "区盟链测试",
                          "business_license_type": "NATIONAL_LEGAL",
                          "chantype": 39,
                          "merchant_id": "M00000022",
                          "business_license": "156180303211111111",
                          "busscode": "D203",
                          "contact_email": "15618030321@qq.com",
                          "service_phone": "15618030321",
                          "wallet_id": "112233445566778899",
                          "merchant_short_name": "qml",
                          "busstype": "02030",
                          "online_flag": 3,
                          "instruction_id": "1",
                          "channel_id": "1234567890",
                      },
                      "format": "json",
                      "msg_id": "069cedc0aaf848d6940a8ae5afacf439",
                      "app_id": "10000000000000197026",
                      "sign_type": "RSA2",
                      "timestamp": "2021-01-12 10:02:48",
                      }

    # 对字典类型json化，排序签名
    json_sign_params(test_private_key, url, request_params)
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
