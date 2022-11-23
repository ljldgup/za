import hashlib

device_config = {

    "gatewayInfo": {
        "1579640765576941568": {
            "password": "4d3tMxIIcd+vNkP7gFYXlCpauxPC30GEy6UtaMoVUV2gsafE0zG7smgQ+WoBryBL",
            "clientId": "1579640765576941568",
            "productCode": "agioe-cable",
            "deviceCode": "monitor001",
            "username": "1579640765576941568&1665451628162"
        }

    },
    "childrenInfo": {
        "1579640765576941568": [{"number": 20, "productCode": "agioe-pump"},
                                {"number": 20, "productCode": "GroundCurrent"},
                                {"number": 20, "productCode": "O2Sensor"}],
        # "1575445794436988928": [{"number": 0, "productCode": "smartlight"}]
    },
    "productModel": {
        "agioe-pump": {
            "data":
                {
                    "XH": "V12.0.1",
                    "RunState": 1
                }
            # "event": [
            #     {"event": "devCtrl"}
            #
            # ]
        },
        "GroundCurrent": {
            "data":
                {
                    "XH": "GNS983729323",
                    "CurrentA": 20.1,
                    "CurrentB": 19.1,
                    "CurrentC": 19.8
                },
            "event": [
                {
                    "event": "CurrentAlarm", "data": {
                    "phase": "1",
                    "AlarmValue": 11.1,
                    "CableSeg": 100,
                    "AlarmTime": "1665453116991"
                }
                }

            ]
        },
        "O2Sensor": {
            "data":
                {
                    "XH": "SEN983729323",
                    "O2": 13.1
                },
            "event": [
                {
                    "event": "O2Alarm", "data": {
                    "O2": 33,
                    "eventTime": "1665453116991"
                }
                }
            ]
        }
    }

}

if __name__ == "__main__":
    with open("device_config.py", "rb") as f:
        print(hashlib.md5(f.read()).hexdigest())
