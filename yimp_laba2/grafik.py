import matplotlib.pyplot as plt
import pandas as pd
import glob

# Находим все CSV-файлы с именами output_eq*.csv
csv_files = glob.glob("output_eq*.csv")

for file in csv_files:
    data = pd.read_csv(file)

    x = data["x"]
    y_approx = data["y_approx"]
    y_exact = data["y_exact"]
    error = data["error"]

    # График приближенного и точного решения
    plt.figure(figsize=(8, 6))
    plt.plot(x, y_approx, 'o-', label="y_approx (Runge-Kutta 3)", markersize=6, markerfacecolor='none')
    plt.plot(x, y_exact, 's-', label="y_exact (аналитическое)", markersize=6)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title(f"Сравнение численного и точного решения ({file})")
    plt.legend()
    plt.grid(True)
    plt.show()

    # График ошибки
    plt.figure(figsize=(8, 6))
    plt.plot(x, error, 'r.-', label="Ошибка |y_approx - y_exact|")
    plt.xlabel("x")
    plt.ylabel("Ошибка")
    plt.title(f"График ошибки ({file})")
    plt.legend()
    plt.grid(True)
    plt.show()
