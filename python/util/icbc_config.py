import uuid

from datetime import datetime


class base_info_quer:
    url = "/api/mybank/pay/digitalwallet/baseinfoquery/V1"
    test_private_key = "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCm5Ow1+14YePTGcMrBJHv0c5/R0L4t9M7voxWZiZwe1J/WWuR14FkRZL0FSL+cRcSCWk/dNj2bV5aRcWLP5xcsX3HOmeQkMGryGGRXgAWAWb0ZPYSlSQFho0STpHGgvl77M2e0bHUDGSXH1+MX46I7XddzFoqCWu713CKBG7ZR8aS8sFrV+IWuU2X5+fVQGIkIpueJQNivCaTWray3Rs9QJRRWMls4LHXlnFbJ/DFN3IqHQTtA6qRL+49Jar6iJxKw9zEK78Txl77nY8VXxUUyVRLtSVCjsd1M+aZMaultihy6rkrw24lhceRMLzP+EcESx4lIPNIwe3HTCLEBht7dAgMBAAECggEBAKPo3yihSKfGW7htXGRWnbrWuBcL6UwfTAHE7NjPctpAvv56ZDh072UKyC3hZfZn+vh/FELRG65uVn1fm8lOT88PqilbsNnuB4rfc+UP4ddNy093wMfILKgk/pv2fHZ/oa8arHZhsoYpc5aTLADxWwrtPkVU1RHzlw82dVjRy70rfTYSppLDhHwiINoV+f0GNUxKVDW0oUW4q/VruEXFk8KNjJ5J+46TcLh7VGW+XJ3XkDvEdaBhs/u6rpTcTRKpOLgkU4jL2AhgT+5wOadnPS2VIMGVZm76rDQkzWH44DRVmcj0u+BFwBhmiQ+ysGgdPlNXbEzZVM5QVWBaH4ewZ2ECgYEA0E8x5g7XHDR00KnoBnPSgU2EhxGhPajKBCj0edyMAht/NsE+oLZ5aYeUlG2EIyhLKn6r6Mw9fi+aGuqSthxT3+050k49356BzYz5KBy4tN93nT4ryaM7Bhe0e4Rk+ack9Ozy4rqnA1yvRYaLT9lMyDSSULWasN02caVeHq3QELkCgYEAzRptoi5mtC7yQU+dA/rg03qfqg83LmL2yMwkqr6keYvXZfwMt/iKqVUZ3UydyFwk1nwS6IVDsmKX9V9ioIxCVb9ldO0RyycmoWDX2tQvJOvChydQLrEi3u3FGnabQqM3b41eekzw5U56L/ymxjoe/S9euchla/oY+BPtVdY0xUUCgYAkqfu/YVdNOJJi87TKBfLEHW+5EkpN/vpnlwnItR/TcyGF8qdiRBvEjj+BjHEYewwX06nQVLpyDlDScf0Wno/ItwlZUbokNNLl6e0kuUFtXHPCMmIkoF1QKjXzE49uPZQMo/PwIigpOFQFKbQ1fqq8BjzGheBPRvBBOnkBb1hSyQKBgQC9FToxI9nnDsijUUQNoUGXdRqw6qoSh4W/hAPhrTNwIm2HRaBsEiOzDBN2IuXrCpejbGr6FbFdSOuSeEcyf1vANVzROKUIxqUkbWVSBf8YaIjDlIilIwRkxIrLZMCp5FJ88rVAxqHmpDyc9KzDXl2nR/5qA8cMjlpqieRpF7s6iQKBgQCsRRDW8wmJDMr6lkrzhXeI+J+9ve3EGFm+f0X6h6LMIVkXAJwDzRt/GIQSJ9Y99pv1bxWUpbmDWzhUTtRrrmwUaNvys9B+ErqMpge6vTxNwkhFcJuRBzaal23fndPrPyU5bUUH7b4CorsA1GQo5sErBfRKVL3D3kjhBQ0x+1KVoQ=="

    request_params = \
        {"app_id": "10000000000000197026",
         "format": "json",
         "msg_id": str(uuid.uuid4()),
         "charset": "utf-8",
         "sign_type": "RSA2",
         "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
         'biz_content':
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

class mercht_query:

    url = "/api/mybank/pay/digitalwallet/submerchantquery/V1"
    test_private_key = "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCm5Ow1+14YePTGcMrBJHv0c5/R0L4t9M7voxWZiZwe1J/WWuR14FkRZL0FSL+cRcSCWk/dNj2bV5aRcWLP5xcsX3HOmeQkMGryGGRXgAWAWb0ZPYSlSQFho0STpHGgvl77M2e0bHUDGSXH1+MX46I7XddzFoqCWu713CKBG7ZR8aS8sFrV+IWuU2X5+fVQGIkIpueJQNivCaTWray3Rs9QJRRWMls4LHXlnFbJ/DFN3IqHQTtA6qRL+49Jar6iJxKw9zEK78Txl77nY8VXxUUyVRLtSVCjsd1M+aZMaultihy6rkrw24lhceRMLzP+EcESx4lIPNIwe3HTCLEBht7dAgMBAAECggEBAKPo3yihSKfGW7htXGRWnbrWuBcL6UwfTAHE7NjPctpAvv56ZDh072UKyC3hZfZn+vh/FELRG65uVn1fm8lOT88PqilbsNnuB4rfc+UP4ddNy093wMfILKgk/pv2fHZ/oa8arHZhsoYpc5aTLADxWwrtPkVU1RHzlw82dVjRy70rfTYSppLDhHwiINoV+f0GNUxKVDW0oUW4q/VruEXFk8KNjJ5J+46TcLh7VGW+XJ3XkDvEdaBhs/u6rpTcTRKpOLgkU4jL2AhgT+5wOadnPS2VIMGVZm76rDQkzWH44DRVmcj0u+BFwBhmiQ+ysGgdPlNXbEzZVM5QVWBaH4ewZ2ECgYEA0E8x5g7XHDR00KnoBnPSgU2EhxGhPajKBCj0edyMAht/NsE+oLZ5aYeUlG2EIyhLKn6r6Mw9fi+aGuqSthxT3+050k49356BzYz5KBy4tN93nT4ryaM7Bhe0e4Rk+ack9Ozy4rqnA1yvRYaLT9lMyDSSULWasN02caVeHq3QELkCgYEAzRptoi5mtC7yQU+dA/rg03qfqg83LmL2yMwkqr6keYvXZfwMt/iKqVUZ3UydyFwk1nwS6IVDsmKX9V9ioIxCVb9ldO0RyycmoWDX2tQvJOvChydQLrEi3u3FGnabQqM3b41eekzw5U56L/ymxjoe/S9euchla/oY+BPtVdY0xUUCgYAkqfu/YVdNOJJi87TKBfLEHW+5EkpN/vpnlwnItR/TcyGF8qdiRBvEjj+BjHEYewwX06nQVLpyDlDScf0Wno/ItwlZUbokNNLl6e0kuUFtXHPCMmIkoF1QKjXzE49uPZQMo/PwIigpOFQFKbQ1fqq8BjzGheBPRvBBOnkBb1hSyQKBgQC9FToxI9nnDsijUUQNoUGXdRqw6qoSh4W/hAPhrTNwIm2HRaBsEiOzDBN2IuXrCpejbGr6FbFdSOuSeEcyf1vANVzROKUIxqUkbWVSBf8YaIjDlIilIwRkxIrLZMCp5FJ88rVAxqHmpDyc9KzDXl2nR/5qA8cMjlpqieRpF7s6iQKBgQCsRRDW8wmJDMr6lkrzhXeI+J+9ve3EGFm+f0X6h6LMIVkXAJwDzRt/GIQSJ9Y99pv1bxWUpbmDWzhUTtRrrmwUaNvys9B+ErqMpge6vTxNwkhFcJuRBzaal23fndPrPyU5bUUH7b4CorsA1GQo5sErBfRKVL3D3kjhBQ0x+1KVoQ=="

    request_params = {
        "charset": "UTF-8",
        "biz_content": {
            "chantype": 39,
            "merchant_id": "M00000022",
            "instruction_id": "1",
            "channel_id": "3324"
        },
        "format": "json",
        "msg_id": str(uuid.uuid4()),
        "app_id": "10000000000000197026",
        "sign_type": "RSA2",
        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    }
