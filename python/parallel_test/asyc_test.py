import asyncio
import random


async def async_test(i):
    # asyncio.sleep必须await 否则不生效
    # await 必须在async 函数内
    await asyncio.sleep(random.random()*10)
    print(i)

if __name__ == '__main__':
    # for i in range(10):
    #     async_test(i)
    # # 直接sleep无效, 用await+asyncio.sleep报错
    # time.sleep(10)


    for i in range(10):
        asyncio.run(async_test(i))


    # loop = asyncio.get_event_loop()
    # for i in range(10):
    #     loop.create_task(async_test(i))
    # loop.run_forever()


