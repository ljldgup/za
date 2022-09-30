import asyncio
import random

async def compute(x, y):
    print("Compute %s + %s ..." % (x, y))
    # await 后sleep，各种io等系统开销，会自动切到别的协程运行，这是协程主要的优势，但是需要手动调度
    await asyncio.sleep(random.randint(1,3))
    return x + y

async def print_sum(x, y):
    result = await compute(x, y)
    print("%s + %s = %s" % (x, y, result))

loop = asyncio.get_event_loop()

# print_sum(1, 2)不会直接运行，而是返回async对象
# 这种写法每次都等待
loop.run_until_complete(print_sum(1, 2))
loop.run_until_complete(print_sum(3, 4))

print('-----------------------------------------------------')
# 一次性等待多个
loop.run_until_complete((asyncio.wait([print_sum(1, 2), print_sum(3, 2)])))

 # gather可以进行分组
tasks1=[print_sum(11, 22),print_sum(33, 44)]
tasks2=[print_sum(55, 66),print_sum(77, 88)]
group1 = asyncio.gather(*tasks1)
group2 = asyncio.gather(*tasks2)
loop.run_until_complete(asyncio.gather(group1, group2))
loop.close()
