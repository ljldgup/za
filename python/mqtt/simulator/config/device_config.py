import hashlib

device_config = {

    "gatewayInfo": {
        "1574696641356816384": {
            "password": "53yR03+TJJcvGC5jAior5u/6Ws9noNMrSHHY5pXcarqkwUx3pOFFYuJNdofGeW0S",
            "clientId": "1574696641356816384", "productCode": "product4", "deviceCode": "d67dd71f-a5e",
            "username": "1574696641356816384&1664272625126"
        },
        "1574696642199871488": {
            "password": "4jJmFWsPI9vZPMrld9+hicYtJE2SF2tur2jvOXh4KdInqNqo+nguPovAxyr1ZDbo",
            "clientId": "1574696642199871488", "productCode": "product4", "deviceCode": "33973664-4d6",
            "username": "1574696642199871488&1664272625192"
        },
        "1574696641616863232": {
            "password": "HoF9Bpit1HbIj3Dcvj0rd+i/EJo7ylDCaU1FgSHXnOfk5ioxYpV3N+W82ftAY+Sd",
            "clientId": "1574696641616863232", "productCode": "product4", "deviceCode": "c89015d1-246",
            "username": "1574696641616863232&1664272625183"
        },
        "1574696641298096128": {
            "password": "2v9wf0eEPi5tRKjCpY+O8Up4SYC80TaM6O56S/KCbfHlM3hlnV6TXVY7a3JqMInP",
            "clientId": "1574696641298096128", "productCode": "product4", "deviceCode": "3a95aa1e-61e",
            "username": "1574696641298096128&1664272625135"
        },
        "1574696641495228416": {
            "password": "tjiNpMS8eTHWSxrMGOVBi28i+9ZnsKiA6RZNOGMiZ8tOONdvvcIpIEVkjiKKcF2Q",
            "clientId": "1574696641495228416", "productCode": "product4", "deviceCode": "a2b92a03-e80",
            "username": "1574696641495228416&1664272625160"
        },
        "1574696641751080960": {
            "password": "6gLwwOWyRuMVsFRwo5IE5Qa1e4lBKUuUDaaqutHZWILMXjP+WT70VJiHZ00WqT+B",
            "clientId": "1574696641751080960", "productCode": "product4", "deviceCode": "851e6695-86c",
            "username": "1574696641751080960&1664272625191"
        },
        "1574696641629446144": {
            "password": "zmhI0HKVr0zIJ1ulBpEX6gIx5gCqIeFNa2PCZcnZZmvrZnPURrqYcEfD7QyKmpaZ",
            "clientId": "1574696641629446144", "productCode": "product4", "deviceCode": "d28d1438-c49",
            "username": "1574696641629446144&1664272625184"
        },
        "1574696642099208192": {
            "password": "P6Fogm2xMk2Y4PDfFBy/xp42td6MBPgv833oqn7PiNXNqkDA3xskLXnOv1tKyM8z",
            "clientId": "1574696642099208192", "productCode": "product4", "deviceCode": "3ddefdc9-af3",
            "username": "1574696642099208192&1664272625117"
        },
        "1574696640664756224": {
            "password": "ePn8QCwkuHVlhQBRQzPwe99EM4A4pfKP1XPCIF3G/iJMBYfJZGsoopLgn9Ezl2su",
            "clientId": "1574696640664756224", "productCode": "product4", "deviceCode": "720e5bdb-5a1",
            "username": "1574696640664756224&1664272625139"
        },
        "1574696642048876544": {
            "password": "B95SwjI2fe7rr+VdMBDVEM6gz7OraXSivpbNDMD1cKiOYWLfkVVquXMwiSaPmc4t",
            "clientId": "1574696642048876544", "productCode": "product4", "deviceCode": "7d527920-3ff",
            "username": "1574696642048876544&1664272625174"
        },
        "1574696641432313856": {
            "password": "BnQjzrwfgUeaBrKO/DRc2NznY4l/fx2omiQCUxkjWQ+0VpRO//hnVK5HczxmuPyk",
            "clientId": "1574696641432313856", "productCode": "product4", "deviceCode": "3648dfc0-6be",
            "username": "1574696641432313856&1664272625132"
        },
        "1574696642086625280": {
            "password": "Dj5jZ4QBLN4EXBZVcSfqShKEvRul8qoDPTpj/qgnvB9AvHAOisXfZjY6gOeEZncq",
            "clientId": "1574696642086625280", "productCode": "product4", "deviceCode": "8c97ac5d-ee9",
            "username": "1574696642086625280&1664272625138"
        },
        "1574696641860132864": {
            "password": "ah1tXl14GHUHrv6knRLe8ecTPjZqfVBY6WzNkL6DIDSASzpxdpOUpaYu5QKwqr1B",
            "clientId": "1574696641860132864", "productCode": "product4", "deviceCode": "16db9f12-c49",
            "username": "1574696641860132864&1664272625142"
        },
        "1574696640580870144": {
            "password": "qg6T3NEvq8ouXs0Z87PoYnXhJP4gahKSwB6pMDUI5ASFQNb1CG7CzDTkmWFZsA46",
            "clientId": "1574696640580870144", "productCode": "product4", "deviceCode": "eb45371b-0b1",
            "username": "1574696640580870144&1664272625124"
        },
        "1574696641482645504": {
            "password": "LdGGyTHKBnIsnf53nULIblori57ufaO0M4uqbj4oGsMAnljzT+qn04i8yRLhVNvu",
            "clientId": "1574696641482645504", "productCode": "product4", "deviceCode": "4a9e8b8c-fca",
            "username": "1574696641482645504&1664272625157"
        },
        "1574696640878665728": {
            "password": "S9gGL3/1+5AwcBQZ3kfiCd1r9lrHBNX4gkuJmD3FSp0rrlAPqf8ge7eyleKslXrF",
            "clientId": "1574696640878665728", "productCode": "product4", "deviceCode": "2f8a42f4-3f6",
            "username": "1574696640878665728&1664272625159"
        },
        "1574696640928997376": {
            "password": "HNx9Vj73vwBApdbBtVKtnkJ7caWAurH/R3yZnH71Fcf7pnjCzL2279CvyvVJIOmP",
            "clientId": "1574696640928997376", "productCode": "product4", "deviceCode": "55e38cd0-db9",
            "username": "1574696640928997376&1664272625163"
        },
        "1574696642174705664": {
            "password": "VcagIHZrHIWNRcTnVeqipCFn6C9ZlIDhH/I5AQoal3Sa/D+a4kQSG3C7vBHpq0op",
            "clientId": "1574696642174705664", "productCode": "product4", "deviceCode": "74de71ce-5ec",
            "username": "1574696642174705664&1664272625111"
        },
        "1574696641117741056": {
            "password": "Ut8WHyeFAMbq53R9iD2cApmZ+hY2U5fu6HurtxZ7tLL9w6vnJBDWvbBLbDdtsaUA",
            "clientId": "1574696641117741056", "productCode": "product4", "deviceCode": "b2970e14-370",
            "username": "1574696641117741056&1664272625184"
        },
        "1574696640404709376": {
            "password": "EgE8KCDWF8ll0jIgCBod3QrtcQQKtoAct4us+Mietxryb2Vlv/xb0q21XcY+QI1O",
            "clientId": "1574696640404709376", "productCode": "product4", "deviceCode": "fc05af70-2f3",
            "username": "1574696640404709376&1664272624965"
        },
        "1574696642162122752": {
            "password": "goIPcq+kODJK9w9+yWoTUE0kbBCjk5Y6aLC+RQXUS/lwp0WCDb1cFS6pCql3quWq",
            "clientId": "1574696642162122752", "productCode": "product4", "deviceCode": "2d114457-efb",
            "username": "1574696642162122752&1664272625182"
        },
        "1574696641990156288": {
            "password": "Cr9EDABTi3EZpOPzZjgOfAhsXiKxR3fFmh6opyGPJep5snsGcAwcHk7Cdy56CXtA",
            "clientId": "1574696641990156288", "productCode": "product4", "deviceCode": "455cfcf6-630",
            "username": "1574696641990156288&1664272625168"
        },
        "1574696642183094272": {
            "password": "C5eUOU7XrWvyM2tjI5Dw44h2oSQ7fh/E3XtSvnZa5Scs61yS2npVwZg2E3ZUsdwy",
            "clientId": "1574696642183094272", "productCode": "product4", "deviceCode": "344232d9-ff4",
            "username": "1574696642183094272&1664272625155"
        },
        "1574696641650417664": {
            "password": "bj3w/ECtPCZhxGog80pdHlnDadSy5EsEJLe8toxBvoMZPZyRIGQxd60ZE8NnokHW",
            "clientId": "1574696641650417664", "productCode": "product4", "deviceCode": "940454c4-1bf",
            "username": "1574696641650417664&1664272625186"
        },
        "1574696641046437888": {
            "password": "naZkyRg+X2gETdRj2orqz4nziUXg/PrLVC+ldsBS2dDeReVXm196Mmpk/6hXcLiF",
            "clientId": "1574696641046437888", "productCode": "product4", "deviceCode": "b2219a98-263",
            "username": "1574696641046437888&1664272625178"
        },
        "1574696641386176512": {
            "password": "v4qzO+QNsv3KHz7J0RUAuRFOPKm9maTxhokVp8lnc+DjnkNh9Qe+LV7atAJTnCS0",
            "clientId": "1574696641386176512", "productCode": "product4", "deviceCode": "e5735d83-d9e",
            "username": "1574696641386176512&1664272625193"
        },
        "1574696640635396096": {
            "password": "hi8sg8Dx94yaY+qSjRZ4oo2pOJJKw5xWJX4vBwdG6/Mouw1d78D1uwSrTwVK9f2G",
            "clientId": "1574696640635396096", "productCode": "product4", "deviceCode": "8563c4c7-bd6",
            "username": "1574696640635396096&1664272625128"
        },
        "1574696640719282176": {
            "password": "VuOYvUFLBQeuSx1iL+NQlsOJ3Iixh3UXYHRgT/N6Nj/dUxeyxxpzNnyspddkXrdH",
            "clientId": "1574696640719282176", "productCode": "product4", "deviceCode": "e0b6c6ee-f2a",
            "username": "1574696640719282176&1664272625149"
        },
        "1574696641138712576": {
            "password": "z5pn/+q0v5N5eiQpP0RitEoIRVfQ1SSId5ZkjlH95CDHmp8xYGCFsv11lvWAjNCl",
            "clientId": "1574696641138712576", "productCode": "product4", "deviceCode": "84b885df-d12",
            "username": "1574696641138712576&1664272625185"
        },
        "1574696641667194880": {
            "password": "ysKgfxAptp4JJBSzZiSeFalu7uEcyL14ghiTZUQjrZlZY8skqwyNu6Nj+aIus3Wd",
            "clientId": "1574696641667194880", "productCode": "product4", "deviceCode": "4ec04cca-422",
            "username": "1574696641667194880&1664272625187"
        },
        "1574696641021272064": {
            "password": "vCGnn2I+U8J1+11ZUWKBF3d3uG+Y+11w/hQiq1qrhBQJXYMxBvwQz5BH+wml6cjq",
            "clientId": "1574696641021272064", "productCode": "product4", "deviceCode": "939772d0-ae9",
            "username": "1574696641021272064&1664272625175"
        },
        "1574696641709137920": {
            "password": "Gl00NkBiKBrH92j/cCnhW3L+KJ5bTD7N5z9toHcwN6Coj4BnJeMfbinrs/+98Pp/",
            "clientId": "1574696641709137920", "productCode": "product4", "deviceCode": "f22faef7-d26",
            "username": "1574696641709137920&1664272625102"
        },
        "1574696641960796160": {
            "password": "BTp3lD44r3t9nRVdf8744qASYv93CFPlCgB0BU79vf3WtoqEDzMbKeKNcR35uc9Q",
            "clientId": "1574696641960796160", "productCode": "product4", "deviceCode": "c67b073e-d88",
            "username": "1574696641960796160&1664272625161"
        },
        "1574696640618618880": {
            "password": "kMOwZw7yJm2ATMKhL8L9boWbaCKHhI1JLaldK2MIjrpdi252W3cuaxOa4UqIa9EV",
            "clientId": "1574696640618618880", "productCode": "product4", "deviceCode": "e81cdcc1-956",
            "username": "1574696640618618880&1664272625131"
        },
        "1574696641344233472": {
            "password": "7seDKOhQdEuBtvgL/lRfXnSECkgqmYb4lIz9dXMk/SyqOPSabC9rRZBZtG4F4kM/",
            "clientId": "1574696641344233472", "productCode": "product4", "deviceCode": "c7077193-395",
            "username": "1574696641344233472&1664272625129"
        },
        "1574696641541365760": {
            "password": "CwIxzni5aQlmbhFOWVrdHhhng3d6p19rwZNkNBt5bdsQKyK4MgEQFaSA0xQ4zTyP",
            "clientId": "1574696641541365760", "productCode": "product4", "deviceCode": "86e17455-ea6",
            "username": "1574696641541365760&1664272625170"
        },
        "1574696641079992320": {
            "password": "QjfZIIhQ0f3q+Msl4lTQx5feq2X+XGo6yWo7fw911LxeFencvxNPMQ2CKMqKtD9C",
            "clientId": "1574696641079992320", "productCode": "product4", "deviceCode": "929b4b51-d10",
            "username": "1574696641079992320&1664272625181"
        },
        "1574696641063215104": {
            "password": "MpAoOxOQFpKlgheuwbqO3g0Qn9u5Yo51gLDNIHBi0ycFH36jhQmbkj5vYqaMUOR+",
            "clientId": "1574696641063215104", "productCode": "product4", "deviceCode": "dc9233e9-aa5",
            "username": "1574696641063215104&1664272625180"
        },
        "1574696641683972096": {
            "password": "XFUrndS7woRPlvfzIzKhlS49bz7zIZlej6NihK3DUJtfxwAyyYU5nz+zDUWxPo5A",
            "clientId": "1574696641683972096", "productCode": "product4", "deviceCode": "c4820da3-b56",
            "username": "1574696641683972096&1664272625189"
        },
        "1574696641176461312": {
            "password": "akagwB0V7WRFrspWA1IMFqeU3zpa4ioJ04tQgfg8ERmWJYTkmmy6IUjBRuTX4t4l",
            "clientId": "1574696641176461312", "productCode": "product4", "deviceCode": "8ad33073-148",
            "username": "1574696641176461312&1664272625186"
        },
        "1574696641927241728": {
            "password": "jK8iOVGhq3j6fkfvZXcOfPfKsuPlx5iIFZnPL16M8WqkKkI3/EfuucRk2JKbTucj",
            "clientId": "1574696641927241728", "productCode": "product4", "deviceCode": "d0f02eb2-95a",
            "username": "1574696641927241728&1664272625152"
        },
        "1574696641583308800": {
            "password": "e0KRJkHTVokapGrQ2WeYNDapGebRnyk49Q0Jh1r+Buw1W5LdZTQfi94vXE4IeJwc",
            "clientId": "1574696641583308800", "productCode": "product4", "deviceCode": "3551b6c3-62f",
            "username": "1574696641583308800&1664272625178"
        },
        "1574696641780441088": {
            "password": "va5HB+3kFbprQmPlHyppjsZmk4q6mSNS31McgMPgI46XqM7yJdPgdQzdpMY/dy+2",
            "clientId": "1574696641780441088", "productCode": "product4", "deviceCode": "bce312ae-ab9",
            "username": "1574696641780441088&1664272625106"
        },
        "1574696640698310656": {
            "password": "0bT9IJFoHmFSfeTZh1Dr2jUphaWuhMzOwu+VkGxfqXp9tR6G51dXijLoxGR87GBT",
            "clientId": "1574696640698310656", "productCode": "product4", "deviceCode": "dcf60d36-556",
            "username": "1574696640698310656&1664272625146"
        },
        "1574696641524588544": {
            "password": "KKJ+dOGTT42vXczGS8yQzwE7L2GwA7itK2QW0RDXKDh80N1Ru+nsicR+25QkEvoe",
            "clientId": "1574696641524588544", "productCode": "product4", "deviceCode": "9f07de3c-717",
            "username": "1574696641524588544&1664272625167"
        },
        "1574696641876910080": {
            "password": "DogRyJzpYjOdJerQ/9hvwAKfH6ed8zN+mEZpIpa9Pz8QXEshP2xgDQ6S57GZWQha",
            "clientId": "1574696641876910080", "productCode": "product4", "deviceCode": "a38271d9-57a",
            "username": "1574696641876910080&1664272625154"
        },
        "1574696641440702464": {
            "password": "9haavkgchkv8Ei2LLg4dOe5Lk8NL7wjXWBVucuNAEqWVQ54scl2owHLsa62C26oV",
            "clientId": "1574696641440702464", "productCode": "product4", "deviceCode": "fa60495f-d21",
            "username": "1574696641440702464&1664272625154"
        },
        "1574696641944018944": {
            "password": "EG/7mLg7qyUFnQpbMiWIGNKMKuw+NCvAsb1xizFI/TtQpq5m12pPQ7c1hso5icr6",
            "clientId": "1574696641944018944", "productCode": "product4", "deviceCode": "2d756052-884",
            "username": "1574696641944018944&1664272625158"
        },
        "1574696641327456256": {
            "password": "bKc1mGE8TiJNKKRpbU+rk0LctuSgObcIY4w4UQpUEX0mJJpB7wgOETCVc9ig9iN1",
            "clientId": "1574696641327456256", "productCode": "product4", "deviceCode": "274261db-a86",
            "username": "1574696641327456256&1664272625105"
        },
        "1574696640547315712": {
            "password": "obd6lbv2oPzPA3fo2XYbCtYj7Sng0e3atqggX1alFRw5u5uST8um/srPrTvnD2sC",
            "clientId": "1574696640547315712", "productCode": "product4", "deviceCode": "90c0d3a7-89e",
            "username": "1574696640547315712&1664272625112"
        },
        "1574696641847549952": {
            "password": "6aTBB+/CdIDVjK5mDiGKcwL9/0OAuBiZet+3wNum/IO8jw6dyPcvPnIQtks39czi",
            "clientId": "1574696641847549952", "productCode": "product4", "deviceCode": "2dd6807b-0a4",
            "username": "1574696641847549952&1664272625194"
        },
        "1574696640949968896": {
            "password": "2QKJ3LmrSMn3RIq25XZSaoRLPkOzQzuHLnaU42H4REmO9MxwS06MpQOMesh3ZcID",
            "clientId": "1574696640949968896", "productCode": "product4", "deviceCode": "0291bf9e-976",
            "username": "1574696640949968896&1664272625166"
        },
        "1574696642006933504": {
            "password": "6zC6o/7yeSAKJlvnukxSQ8NKsyevsNmfgx1R2TpsK/Ooq5jwO2pMG+Le13+xzfWa",
            "clientId": "1574696642006933504", "productCode": "product4", "deviceCode": "96d72696-4a6",
            "username": "1574696642006933504&1664272625177"
        },
        "1574696641574920192": {
            "password": "57nQ6Fk8v/VVJOf1NQ2K9wlxAj1jUJT02jDbDglS+yv8Rh0ulJPE8O8BGy8hU2y0",
            "clientId": "1574696641574920192", "productCode": "product4", "deviceCode": "89499ecb-aa6",
            "username": "1574696641574920192&1664272625180"
        },
        "1574696641977573376": {
            "password": "JU1FBwsaLdrOU29ejzuE/fyBvuQhE4pHFmMbJr/loyd8hh6fHO5RsQftiEEYex2x",
            "clientId": "1574696641977573376", "productCode": "product4", "deviceCode": "0aad6a68-afa",
            "username": "1574696641977573376&1664272625165"
        },
        "1574696641000300544": {
            "password": "MTFTMz73pbG3SkFD3uMCE+5ZOCCSb2DTkvxrWZRntgkAda7arnTW5C1ivJ5YG8oH",
            "clientId": "1574696641000300544", "productCode": "product4", "deviceCode": "60d327da-f9a",
            "username": "1574696641000300544&1664272625172"
        },
        "1574696642115985408": {
            "password": "eKwrHcTLrGjGcx1uYgq7kk/NRegiu0DcmOnViELPZfd9gLwhdrZ62gtgc9SBh/N3",
            "clientId": "1574696642115985408", "productCode": "product4", "deviceCode": "ad7c50d9-90c",
            "username": "1574696642115985408&1664272625195"
        },
        "1574696642061459456": {
            "password": "8aJOC5tUCj2XJ5TIu/5nAbLYgDWQYcOsJYZDXo2912aBlbsQ3icPIiyRwRFFhe+8",
            "clientId": "1574696642061459456", "productCode": "product4", "deviceCode": "71e45739-e9f",
            "username": "1574696642061459456&1664272625181"
        },
        "1574696641285513216": {
            "password": "eDEXUiI6x6p/VPlRVjXnMKaxK3CxPh8ASnaa+vBRBLfXNNQISydd0kYawo3Ds8df",
            "clientId": "1574696641285513216", "productCode": "product4", "deviceCode": "3c5e28c0-381",
            "username": "1574696641285513216&1664272625108"
        },
        "1574696641369399296": {
            "password": "MJeBm/fjxuvxoZGv65+OWq2nDsUZoqkFZwkb8tleWjLUwv5o94n15iiBu4GzO0cM",
            "clientId": "1574696641369399296", "productCode": "product4", "deviceCode": "64672cd7-8fa",
            "username": "1574696641369399296&1664272625147"
        },
        "1574696641272930304": {
            "password": "CrHyYK5hoBQXsaI3QTpXo5gUeURjkyf/WynqVR3ANo1htmFu8qeqkzN8UlhoEwRp",
            "clientId": "1574696641272930304", "productCode": "product4", "deviceCode": "d32db883-c91",
            "username": "1574696641272930304&1664272625101"
        },
        "1574696641797218304": {
            "password": "0PFVkuF0hVYA2HWiqq3K6+VaJr+jTgbE7etHMTh6KNxN9c10++g4V5X1Zm81tmFD",
            "clientId": "1574696641797218304", "productCode": "product4", "deviceCode": "73cd2caf-362",
            "username": "1574696641797218304&1664272625148"
        },
        "1574696641826578432": {
            "password": "AOMqTovADTEZaM41JijniFxBoe2N9mV8FocDcBlCa1NZE0N9pRt4Zcg829afNC4E",
            "clientId": "1574696641826578432", "productCode": "product4", "deviceCode": "ad4cff66-c0a",
            "username": "1574696641826578432&1664272625146"
        },
        "1574696641813995520": {
            "password": "00C1Z9THFRABQDaHgyPbrSeU2DkxQeIIyuiE0F3dF2lhvNxSb3n2/O9YT/xC7VxK",
            "clientId": "1574696641813995520", "productCode": "product4", "deviceCode": "18c85655-bf4",
            "username": "1574696641813995520&1664272625127"
        },
        "1574696641457479680": {
            "password": "6fi/+/tVb00noxcnAH9PlBPv2c0vQO2ZHO2eaiF5OMUtrKo8Ta1Qz1KIHisyOafL",
            "clientId": "1574696641457479680", "productCode": "product4", "deviceCode": "29b03150-53a",
            "username": "1574696641457479680&1664272625150"
        },
        "1574696640790585344": {
            "password": "IO3uxTfnGFAJ7OpDO4vG4mNNsixDk5gX0mR/OQ2eNp8cZvKBfCf77t412vjdU7zB",
            "clientId": "1574696640790585344", "productCode": "product4", "deviceCode": "e04058aa-44b",
            "username": "1574696640790585344&1664272625156"
        },
        "1574696641738498048": {
            "password": "4AqKaRQL9EiGzSeLm12wW11JlejMzX8SexEmj7bf9K3QuHBFe9s5z35XvrLVuRy/",
            "clientId": "1574696641738498048", "productCode": "product4", "deviceCode": "3cc76cc1-486",
            "username": "1574696641738498048&1664272625115"
        },
        "1574696641696555008": {
            "password": "RjYYNszFZnMs5VacPGduZ2NUAXTIl4BMmcejUQQjBbSdQgr2LEeagfJeOGnc4XeV",
            "clientId": "1574696641696555008", "productCode": "product4", "deviceCode": "3b9c4fcb-9b7",
            "username": "1574696641696555008&1664272625136"
        },
        "1574696642107596800": {
            "password": "ocaPLOugpanG7Gr9nyAGmb7DotZ/2iTKgmMcrSHESvnf4Q/EyiE5kk4bN7odgqBb",
            "clientId": "1574696642107596800", "productCode": "product4", "deviceCode": "c8366847-bf4",
            "username": "1574696642107596800&1664272625149"
        },
        "1574696641637834752": {
            "password": "VbCNy4EsKxocwm3a633wpbeMTIPg/PjtBC30hNcdB0bYteyfvYIs6Vw0u4woIR9h",
            "clientId": "1574696641637834752", "productCode": "product4", "deviceCode": "41eb4a5d-909",
            "username": "1574696641637834752&1664272625185"
        },
        "1574696641893687296": {
            "password": "4fvGBhAFnsQiEAbMh/+PcpJUoK0rROYGo4QOp7fYk8iAsvyeL1nTQSIuodmgt+00",
            "clientId": "1574696641893687296", "productCode": "product4", "deviceCode": "79ab37a3-83f",
            "username": "1574696641893687296&1664272625133"
        },
        "1574696641415536640": {
            "password": "+YVDe5oLGND4gZ3mv9b3pUS0lOsdkH2xk2MC4n/RSIrtMMUKSFr5ozfGfFjHd7PR",
            "clientId": "1574696641415536640", "productCode": "product4", "deviceCode": "e674cc4d-cc6",
            "username": "1574696641415536640&1664272625140"
        },
        "1574696641512005632": {
            "password": "ehstVfk+vDBvv3m+9KPZv27STjiVOP0gQsFoSZih0xNfdmSt8BN00h4q6/+8EcFs",
            "clientId": "1574696641512005632", "productCode": "product4", "deviceCode": "33b8d83d-a70",
            "username": "1574696641512005632&1664272625164"
        },
        "1574696642191482880": {
            "password": "/Qsgf8A4nmz5CTNjD6iPloT4TvvvRZjmRpSmI7vSWiGetrJVfzlARxtNkRDkrWKW",
            "clientId": "1574696642191482880", "productCode": "product4", "deviceCode": "0ebbbd55-df3",
            "username": "1574696642191482880&1664272625103"
        },
        "1574696640530538496": {
            "password": "URljtWVTC+xDdZQPypoLgAjt8+S3evcKt1DxYoOpU2j+0C9hMYkNZYWhUeulkXEX",
            "clientId": "1574696640530538496", "productCode": "product4", "deviceCode": "8f6663c9-c5e",
            "username": "1574696640530538496&1664272625107"
        },
        "1574696640744448000": {
            "password": "fjmZTVIIX0IsIYWF05a/CFiyLVElf36OLbBi35i5wy+ehEasFT68s8OrZ1miykIg",
            "clientId": "1574696640744448000", "productCode": "product4", "deviceCode": "d98a1787-2d4",
            "username": "1574696640744448000&1664272625151"
        },
        "1574696641230987264": {
            "password": "4DZBtaJsrblp+DyKs6YYh7MaySn7e+BuTHjwzSVGwfDQxZWkmTOYoSPGVUxDXrNq",
            "clientId": "1574696641230987264", "productCode": "product4", "deviceCode": "19b16934-f3d",
            "username": "1574696641230987264&1664272625188"
        },
        "1574696642153734144": {
            "password": "pmsyiKiA1xMDEQHWiLSuicqubEZcF8VTncxWlwtR9FS8Y6S+KuoZesce6RNKltOS",
            "clientId": "1574696642153734144", "productCode": "product4", "deviceCode": "5468421d-ddb",
            "username": "1574696642153734144&1664272625196"
        },
        "1574696641906270208": {
            "password": "BivMaWsn+BiAiPGoHxxINtMXn2ttnmS6aApTeBMmqRF8xuyArnS2ZvnrQHChC83f",
            "clientId": "1574696641906270208", "productCode": "product4", "deviceCode": "46aa4188-fe9",
            "username": "1574696641906270208&1664272625150"
        },
        "1574696641100963840": {
            "password": "EoRB53C8aqh5rHvl5G2Jxu+pbtWFAkVJ41mfKL6a8aCvHDxII2EZgEncAFFCZoSY",
            "clientId": "1574696641100963840", "productCode": "product4", "deviceCode": "cdf3efa2-44d",
            "username": "1574696641100963840&1664272625183"
        },
        "1574696642036293632": {
            "password": "645rO8rwdR/BcsjZbYQMQEm0n8YVEF/VkkpkNwtK5IRtcmYe2pMK5QPwOV6KWh2V",
            "clientId": "1574696642036293632", "productCode": "product4", "deviceCode": "aca4a2e7-edc",
            "username": "1574696642036293632&1664272625171"
        },
        "1574696640769613824": {
            "password": "r0xP1fDpOkyTtcJK7LoUUuOvRXbU5AwRVgfey5cR0ctcYYAeUBk4PkHJZnTqcNj0",
            "clientId": "1574696640769613824", "productCode": "product4", "deviceCode": "74a3f4bd-940",
            "username": "1574696640769613824&1664272625153"
        },
        "1574696642074042368": {
            "password": "pwOFhJ3Bo2ExQBNE3+w4qQe6FojoRDLDEZFUwxJ+itIX6FQkPxiWpj8jLB+nxKma",
            "clientId": "1574696642074042368", "productCode": "product4", "deviceCode": "b41d42b3-9ae",
            "username": "1574696642074042368&1664272625179"
        },
        "1574696640647979008": {
            "password": "U9hMkoiKbmyVuDnesKgYmuuVBuTbQqgKPyBaQEPB0e2dbgSdW5CW6JnEkvKiBxbM",
            "clientId": "1574696640647979008", "productCode": "product4", "deviceCode": "64a4bb7f-39b",
            "username": "1574696640647979008&1664272625134"
        },
        "1574696641767858176": {
            "password": "q3b4czWsvR7ezfch/Lwp7PRycNaWEgNdmZ0WIsuAB4lSLFZNeeggT4Sr8af7kbfI",
            "clientId": "1574696641767858176", "productCode": "product4", "deviceCode": "0bdbad41-e1a",
            "username": "1574696641767858176&1664272625195"
        },
        "1574696641256153088": {
            "password": "imRCH/RZZB8+Eo+EOMH3rMT/N4g5S2yfOTeJhC62HzX9B6sG9pHjTkhTyqi1PppR",
            "clientId": "1574696641256153088", "productCode": "product4", "deviceCode": "be65b8f2-8e5",
            "username": "1574696641256153088&1664272625190"
        },
        "1574696641398759424": {
            "password": "DxZvuRS9wh5UQOeei0Cdyp9O0cL7iOcHUy23SMEHagOfCkTlkTJmZvfne3faJl+2",
            "clientId": "1574696641398759424", "productCode": "product4", "deviceCode": "36916c30-244",
            "username": "1574696641398759424&1664272625145"
        },
        "1574696641566531584": {
            "password": "ndduCeytF99Sv1MpcxfCjV9R05gqgpXgRgQ527vRimj7FTf66QTLnaMAGzigyf4Q",
            "clientId": "1574696641566531584", "productCode": "product4", "deviceCode": "437019a7-6c6",
            "username": "1574696641566531584&1664272625173"
        },
        "1574696642141151232": {
            "password": "9Fizx8fmSI2AjLJmmlu/CxKUmVtfQqapncSOdSx1sKvHd00vwzwLGJ3ljlKHcFv/",
            "clientId": "1574696642141151232", "productCode": "product4", "deviceCode": "b41f181a-db8",
            "username": "1574696642141151232&1664272625143"
        },
        "1574696640509566976": {
            "password": "4xITLE6IgSL/uX9jyjy8YmaLx8SnZpHLxTam0vrwIzPUfHct1GXRVLsFSPAghzkk",
            "clientId": "1574696640509566976", "productCode": "product4", "deviceCode": "26cbbd6b-0f4",
            "username": "1574696640509566976&1664272625104"
        },
        "1574696640681533440": {
            "password": "Z+k5fmtlsHC3O9u/t9F7WyDsxg/bBPrzeDpy3ENP9/pavAhGLHT6MPwL35DfiGh7",
            "clientId": "1574696640681533440", "productCode": "product4", "deviceCode": "6cae7379-1cf",
            "username": "1574696640681533440&1664272625144"
        },
        "1574696640979329024": {
            "password": "eVyNx0Re++/Ew/BoFAazPzWcqVrRc6re9koOtWPh6NyBql/eK3y4dvWPhsAdOlZ2",
            "clientId": "1574696640979329024", "productCode": "product4", "deviceCode": "72807d9b-dca",
            "username": "1574696640979329024&1664272625169"
        },
        "1574696642132762624": {
            "password": "L82boab3MGRPDIhrVusodK5mtQw0WYNqceM5WAP8cQbtwJRMoyzP6OwGPcyZq2w8",
            "clientId": "1574696642132762624", "productCode": "product4", "deviceCode": "6fb72030-7e9",
            "username": "1574696642132762624&1664272625183"
        },
        "1574696641470062592": {
            "password": "qte2xYDXPrgSYxiwEd3OblraRvV0yTPBEiAyxXT0M/JCrvt4+zXIDl3mxKc64j3e",
            "clientId": "1574696641470062592", "productCode": "product4", "deviceCode": "0e38bf75-137",
            "username": "1574696641470062592&1664272625152"
        },
        "1574696641155489792": {
            "password": "GTz80KjkgR8oYfdTPCbdRXpx9JdKfFRJ6/urUvHC7uDKFYvsIUAgQwZRxAV5luDb",
            "clientId": "1574696641155489792", "productCode": "product4", "deviceCode": "ccdc5732-261",
            "username": "1574696641155489792&1664272625185"
        },
        "1574696641310679040": {
            "password": "TQ0tESozMW6Us/NYb8VD57lrVtJR6Lw58NcrctM8zpMv2yI8ocUXDxh134e68Pyh",
            "clientId": "1574696641310679040", "productCode": "product4", "deviceCode": "c97e29d2-284",
            "username": "1574696641310679040&1664272625114"
        },
        "1574696641558142976": {
            "password": "al4v1h8ktIjXxiDlM9oqzExKstwOK0uca2O/TWPA1VA5M/Usd1db5pBYi56ZD8Rs",
            "clientId": "1574696641558142976", "productCode": "product4", "deviceCode": "2d90718b-a70",
            "username": "1574696641558142976&1664272625176"
        },
        "1574696642124374016": {
            "password": "SNgIKzRlMgXldBz5i4rjyUgAvTfYmZFW9VIeMd62waBEgdK5/0W9AjW/XwIxHiHb",
            "clientId": "1574696642124374016", "productCode": "product4", "deviceCode": "3171df8d-ba5",
            "username": "1574696642124374016&1664272625190"
        },
        "1574696641721720832": {
            "password": "vSD1lym+zuQ3rMVG1jF2LZhMYSNQqtsvQpIk6eBTqV02xp7PjiGvAFnkaWkZLCKq",
            "clientId": "1574696641721720832", "productCode": "product4", "deviceCode": "53ac845b-24b",
            "username": "1574696641721720832&1664272625109"
        },
        "1574696641608474624": {
            "password": "CnhkEpX6xaMTdfuZnWIUkc7dBDV/6DNdyMfaH4N8fcwMQP13bFwjVq+DwQGwubmR",
            "clientId": "1574696641608474624", "productCode": "product4", "deviceCode": "c69d656e-89e",
            "username": "1574696641608474624&1664272625182"
        }
    },
    "childrenInfo": {
        "1574696640928997376": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641512005632": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641977573376": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640949968896": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641524588544": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641990156288": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640979329024": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641541365760": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642036293632": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641000300544": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641566531584": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642048876544": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641021272064": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641558142976": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642006933504": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641046437888": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641583308800": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642074042368": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641063215104": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641574920192": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642061459456": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641079992320": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641608474624": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642162122752": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641100963840": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641616863232": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642132762624": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641117741056": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641629446144": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641138712576": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641637834752": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641155489792": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641650417664": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641176461312": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641667194880": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641230987264": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641683972096": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642124374016": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641256153088": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641751080960": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642199871488": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641386176512": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641847549952": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642115985408": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641767858176": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642153734144": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640404709376": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641272930304": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641709137920": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642191482880": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640509566976": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641327456256": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641780441088": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642174705664": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640530538496": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641285513216": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641721720832": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640547315712": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641310679040": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641738498048": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642099208192": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640580870144": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641356816384": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641813995520": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640635396096": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641344233472": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640618618880": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641432313856": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641893687296": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641298096128": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640647979008": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641696555008": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642086625280": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640664756224": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641415536640": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641860132864": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642141151232": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640681533440": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641398759424": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641826578432": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640698310656": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641369399296": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641797218304": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642107596800": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640719282176": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641457479680": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641906270208": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640744448000": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641470062592": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641927241728": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640769613824": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641440702464": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641876910080": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696642183094272": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640790585344": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641482645504": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641944018944": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696640878665728": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641495228416": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}],
        "1574696641960796160": [{"number": 15, "productCode": "product3"}, {"number": 10, "productCode": "product2"}]
    },
    "productModel": {
        "product1": {
            "data":
                {
                    "p1": 50,
                    "p2": "a"
                },
            "event": [
                {"event": "sync-failer", "data": {
                    "cpuAlm": "85",
                }},
                {"event": "async-warn", "data": {
                    "memAlm": "95",
                }}
            ]
        },
        "product2": {
            "data":
                {
                    "p1": 50,
                    "p2": "a"
                },
            "event": [
                {"event": "sync-failer", "data": {
                    "cpuAlm": "85",
                }},
                {"event": "async-warn", "data": {
                    "memAlm": "95",
                }}
            ]
        },
        "product3": {
            "data":
                {
                    "p1": 50,
                    "p2": "a"
                },
            "event": [
                {"event": "sync-failer", "data": {
                    "cpuAlm": "85",
                }},
                {"event": "async-warn", "data": {
                    "memAlm": "95",
                }}
            ]
        },
        "product4": {
            "data":
                {
                    "p1": 50,
                    "p2": "a"
                },
            "event": [
                {"event": "sync-failer", "data": {
                    "cpuAlm": "85",
                }},
                {"event": "async-warn", "data": {
                    "memAlm": "95",
                }}
            ]
        }
    },

}

if __name__ == "__main__":
    with open("device_config.py", "rb") as f:
        print(hashlib.md5(f.read()).hexdigest())
