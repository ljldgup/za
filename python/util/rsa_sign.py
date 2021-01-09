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


def sorted_param_str(params: dict):
    rst = ""
    for key in sorted(params.keys()):
        if type(params[key]) == str:
            rst += "{}={}&".format(key, params[key])
        else:
            rst += "{}={}&".format(key, json.dumps(params["biz_content"]).replace(" ", ""))
    return rst


if __name__ == "__main__":
    icbc_url = ""
    url = "api/mybank/pay/digitalwallet/baseinfoquery/V1"
    request_params = {"app_id": "10000000000000197026",
                      "msg_id": str(uuid.uuid4()),
                      "format": "json",
                      "charset": "utf-8",
                      "sign_type": "RSA2",
                      "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                      "biz_content":
                          {
                              "cooperator_no": "1234567890",
                              "agent_cooperator_no": "1122334455",
                              "serial_no": "002000000201234567891200001",
                              "related_serial_no": "",
                              "original_serial_no": "",
                              "work_date": "2020-12-12",
                              "work_time": "12:12:12",
                              "mac": "80:32:53:9E:3F:F9",
                              "IP": "fe80::bda7:7d60:bc48:bd36%6",
                              "wallet_id": "0022500497360019"
                          }
                      }

    # 注意自己使用的秘钥
    test_private_key = ""
    request_content = sorted_param_str(request_params)
    # print(sign(message.encode(), test_private_key, "RSA2"))
    # print(sign("签名内容".encode("utf-8"), test_private_key, "RSA2"))
    request_content += "sign=" + pkcs8_rsa2_sign(test_private_key, "?".join([url, request_content])).decode()

    # print(request_content)
    rst = requests.post(icbc_url + "?".join([url, request_content]))
    print(rst.json())