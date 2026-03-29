import time
import matplotlib.pyplot as plt
import numpy as np

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
    josephus(n, k)
    end = time.time()

    duration = end - start
    times.append(duration)

x = np.array(test_n)
y = np.array(times)

a, b = np.polyfit(x, y, 1)

n_pred = 2_000_000

x_real_line = np.linspace(min(x), max(x), 100)          # до 1M
y_real_line = a * x_real_line + b

x_pred_line = np.linspace(max(x), n_pred, 100)          # после 1M
y_pred_line = a * x_pred_line + b

plt.scatter(x, y, label="Реальные данные")

plt.plot(x_real_line, y_real_line, label="До 1M")

plt.plot(x_pred_line, y_pred_line, linestyle='--', label="Прогноз после 1M")

time_pred = a * n_pred + b
plt.scatter(n_pred, time_pred, marker='x', label="2M")

plt.xlabel("N")
plt.ylabel("Время (сек)")
plt.title("Задача Иосифа — прогноз времени")
plt.legend()
plt.grid()

plt.show()