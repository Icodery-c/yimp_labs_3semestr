import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
from pathlib import Path

def read_data(filename):
    """Чтение данных из файла с автоматическим определением формата"""
    try:
        # Сначала пробуем прочитать с разными разделителями
        for delimiter in ['\t', ',', ';', ' ']:
            try:
                df = pd.read_csv(filename, delimiter=delimiter, skipinitialspace=True)
                if len(df.columns) >= 3:  # Если есть хотя бы 3 столбца
                    print(f"Файл {filename} прочитан с разделителем '{delimiter}'")
                    print(f"Столбцы: {list(df.columns)}")
                    return df
            except:
                continue

        # Если не получилось, пробуем чтение с заголовком
        df = pd.read_csv(filename, delim_whitespace=True, skipinitialspace=True)
        print(f"Файл {filename} прочитан с пробельным разделителем")
        print(f"Столбцы: {list(df.columns)}")
        return df

    except Exception as e:
        print(f"Ошибка при чтении файла {filename}: {e}")
        return None

def detect_column_names(df, filename):
    """Автоматическое определение имен столбцов"""
    cols = list(df.columns)
    print(f"Обнаружены столбцы в {filename}: {cols}")

    # Сопоставление столбцов с ожидаемыми именами
    column_mapping = {}

    # Поиск столбца с x координатами
    x_candidates = ['x', 'X', 'x_0', '0']
    for cand in x_candidates:
        if cand in cols:
            column_mapping['x'] = cand
            break
    if 'x' not in column_mapping and len(cols) > 0:
        column_mapping['x'] = cols[0]  # Первый столбец по умолчанию

    # Поиск столбца с численным решением
    num_candidates = ['y_approx', 'y_Adams', 'y_RK3', 'y_RK4', 'y_numeric', 'y1', 'y']
    for cand in num_candidates:
        if cand in cols:
            column_mapping['y_approx'] = cand
            break
    if 'y_approx' not in column_mapping and len(cols) > 1:
        column_mapping['y_approx'] = cols[1]  # Второй столбец по умолчанию

    # Поиск столбца с точным решением
    exact_candidates = ['y_exact', 'y_analytic', 'y_exact_solution', 'y2']
    for cand in exact_candidates:
        if cand in cols:
            column_mapping['y_exact'] = cand
            break
    if 'y_exact' not in column_mapping and len(cols) > 2:
        column_mapping['y_exact'] = cols[2]  # Третий столбец по умолчанию

    # Поиск столбца с ошибкой
    error_candidates = ['error', 'Error', 'delta', 'diff']
    for cand in error_candidates:
        if cand in cols:
            column_mapping['error'] = cand
            break
    if 'error' not in column_mapping and len(cols) > 3:
        column_mapping['error'] = cols[3]  # Четвертый столбец по умолчанию

    print(f"Сопоставление столбцов для {filename}: {column_mapping}")
    return column_mapping

def plot_comparison(df, title, filename=None):
    """Построение графиков сравнения численного и точного решения"""
    # Определяем имена столбцов
    column_mapping = detect_column_names(df, filename if filename else "данные")

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

    try:
        # График решений
        x_col = column_mapping['x']
        y_approx_col = column_mapping['y_approx']

        ax1.plot(df[x_col], df[y_approx_col], 'b-', linewidth=2, label='Численное решение')

        # Если есть точное решение, строим его
        if 'y_exact' in column_mapping:
            y_exact_col = column_mapping['y_exact']
            ax1.plot(df[x_col], df[y_exact_col], 'r--', linewidth=2, label='Точное решение')

        ax1.set_xlabel('x')
        ax1.set_ylabel('y')
        ax1.set_title(f'{title} - Сравнение решений')
        ax1.legend()
        ax1.grid(True, alpha=0.3)

        # График ошибки
        if 'error' in column_mapping:
            error_col = column_mapping['error']
            ax2.plot(df[x_col], df[error_col], 'g-', linewidth=2, label='Ошибка')
            ax2.set_xlabel('x')
            ax2.set_ylabel('Ошибка')
            ax2.set_title(f'{title} - Ошибка')
            ax2.legend()
            ax2.grid(True, alpha=0.3)
        else:
            # Если нет столбца с ошибкой, вычисляем ее
            if 'y_exact' in column_mapping:
                error = np.abs(df[y_approx_col] - df[column_mapping['y_exact']])
                ax2.plot(df[x_col], error, 'g-', linewidth=2, label='Ошибка')
                ax2.set_xlabel('x')
                ax2.set_ylabel('Ошибка')
                ax2.set_title(f'{title} - Ошибка')
                ax2.legend()
                ax2.grid(True, alpha=0.3)
            else:
                ax2.text(0.5, 0.5, 'Нет данных об ошибке',
                        ha='center', va='center', transform=ax2.transAxes)
                ax2.set_title(f'{title} - Нет данных об ошибке')

        plt.tight_layout()

        if filename:
            plot_filename = f"plot_{Path(filename).stem}.png"
            plt.savefig(plot_filename, dpi=300, bbox_inches='tight')
            print(f"График сохранен как: {plot_filename}")

        plt.show()

    except KeyError as e:
        print(f"Ошибка: не найден столбец {e}")
        print(f"Доступные столбцы: {list(df.columns)}")
        plt.close()

def main():
    """Основная функция"""
    print("=== Визуализация результатов численных методов ===\n")

    # Поиск файлов с данными
    data_files = list(Path('.').glob('*.txt')) + list(Path('.').glob('*.dat'))

    if not data_files:
        print("Не найдены файлы с данными (*.txt или *.dat)")
        return

    print("Найдены файлы:")
    for i, file in enumerate(data_files):
        print(f"{i+1}. {file}")

    while True:
        print("\nВыберите действие:")
        print("1. Построить график для одного файла")
        print("2. Обработать все файлы")
        print("0. Выход")

        choice = input("Ваш выбор: ").strip()

        if choice == '0':
            break
        elif choice == '1':
            print("\nДоступные файлы:")
            for i, file in enumerate(data_files):
                print(f"{i+1}. {file}")
            try:
                file_idx = int(input("Выберите файл: ")) - 1
                if 0 <= file_idx < len(data_files):
                    df = read_data(data_files[file_idx])
                    if df is not None:
                        title = input("Введите заголовок графика: ")
                        save_plot = input("Сохранить график? (y/n): ").lower() == 'y'
                        filename = str(data_files[file_idx]) if save_plot else None
                        plot_comparison(df, title, filename)
            except ValueError:
                print("Неверный ввод!")

        elif choice == '2':
            print("\nОбработка всех файлов...")
            for file in data_files:
                print(f"\nОбработка {file}...")
                df = read_data(file)
                if df is not None:
                    plot_comparison(df, f"Данные - {file.stem}", str(file))

        else:
            print("Неверный выбор!")

if __name__ == "__main__":
    main()
