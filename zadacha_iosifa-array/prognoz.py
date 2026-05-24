import matplotlib.pyplot as plt
import numpy as np

# Real measurements (k=2)
n_values = [1000, 5000, 10000, 50000, 100000, 500000, 1000000]
times    = [0.001, 0.020, 0.017, 0.340, 1.302, 32.355, 131.406]

# O(n^2) complexity fit
def f(n):
    return n ** 2

c = times[-1] / f(n_values[-1])

n_predict = 2_000_000
t_predict = c * f(n_predict)

n_theory = np.geomspace(1000, n_predict, 200)
t_theory = c * f(n_theory)

plt.figure(figsize=(12, 8))

plt.plot(n_theory, t_theory, 'r-', alpha=0.6, linewidth=2, label=r'$f(n) = O(n^2)$')
plt.plot(n_values, times, 'b-o', markersize=8, label='Real measurements')
plt.plot(n_predict, t_predict, 'rs', markersize=10,
         label=f'Forecast (N=2M): {t_predict:.1f}s')

for n, t in zip(n_values, times):
    plt.text(n, t * 1.6, f"{t}s", color='blue', ha='center',
             fontsize=9, fontweight='bold')
plt.text(n_predict, t_predict * 1.6, f"{t_predict:.1f}s", color='red',
         ha='center', fontsize=10, fontweight='bold')

plt.xscale('log')
plt.yscale('log')
plt.grid(True, which="both", ls='--', alpha=0.5)

plt.title('Josephus Problem — Algorithm Complexity Analysis (Array)', fontsize=14)
plt.xlabel('Number of elements N', fontsize=12)
plt.ylabel('Execution time (sec)', fontsize=12)

all_n = n_values + [n_predict]
plt.xticks(all_n, [str(v) for v in all_n], rotation=45)
plt.legend()
plt.tight_layout()
plt.savefig('prognoz.png', dpi=150)
plt.show()
print(f"Forecast for N=2,000,000: {t_predict:.1f} sec")
