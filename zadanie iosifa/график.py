import time
import matplotlib.pyplot as plt

def josephus(n, k):
    res = 0
    for i in range(1, n + 1):
        res = (res + k) % i
    return res + 1

test_n = [1000, 5000, 10000, 50000, 100000, 500000, 1000000]
k = 3

times = []

for n in test_n:
    start = time.time()
    result = josephus(n, k)
    end = time.time()

    duration = end - start
    times.append(duration)

    print(f"N: {n} | Answer: {result} | Time: {duration:.6f} sec")

plt.plot(test_n, times, marker='o')
plt.xlabel("N (количество людей)")
plt.ylabel("Время выполнения (сек)")
plt.title("Задача Иосифа (k = 3)")
plt.grid()

plt.show()