import asyncio

import aioconsole
import websockets

messages = ({"nodeId": "jetlinks-platform-cgj:8845", "subType": "cpu", "msgType": "sub"},)


async def hello():
    ipaddress = 'ws://localhost:8845/messaging/realtime?agioe_sso_sessionid=117_806aae07b1904141a49b70f58ca74950'
    async with websockets.connect(ipaddress) as websocket:
        await asyncio.gather(send(websocket), receive(websocket))
        # name = input("input ")
        # await websocket.send(name)
        # await receive(websocket)


async def send(websocket):
    while True:
        # python 自带的input不支持协程
        msg = await aioconsole.ainput()
        await websocket.send(msg)


async def receive(websocket):
    while True:
        greeting = await websocket.recv()
        print(f"< {greeting}")
        # logging.info(f"< {greeting}")


if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(hello())
