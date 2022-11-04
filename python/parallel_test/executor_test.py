import random
from concurrent.futures import wait
from concurrent.futures.thread import ThreadPoolExecutor
from time import sleep

def random_sleep():
    sleep_seconds = random.random()
    sleep(sleep_seconds)
    print(sleep_seconds)

if __name__ == '__main__':
    futures = []
    with ThreadPoolExecutor(max_workers=80) as executor:
        for i in range(1000):
            futures.append(executor.submit(random_sleep))
        wait(futures)
