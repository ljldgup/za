import asyncio
import random

import aioconsole


async def async_test(n: int):
    # asyncio.sleep必须await 否则不生效
    # await 必须在async 函数内
    await asyncio.sleep(random.random() * 10)
    print(n)


# 通过gather在async内部执行多个任务
async def nest_test(n: int):
    coroutines_list = [async_test(i) for i in range(10)]
    await asyncio.gather(*coroutines_list)


# python input 不支持协程，需要 aioconsole.ainput
async def input_test():
    while True:
        num = await aioconsole.ainput()
        await asyncio.gather(async_test(int(num)))


if __name__ == '__main__':
    # for i in range(10):
    #     async_test(i)
    # # 直接sleep无效, 用await+asyncio.sleep报错
    # time.sleep(10)

    # for i in range(10):
    #     asyncio.run(async_test(i))

    # loop = asyncio.get_event_loop()
    # for i in range(10):
    #     loop.create_task(async_test(i))
    # loop.run_forever()

    # asyncio.run(nest_test(10))

    asyncio.run(input_test())
