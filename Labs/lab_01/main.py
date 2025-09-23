import matplotlib.pyplot as plt
import os
import matplotlib.ticker as ticker


def read_data(filename):
    sizes = []
    time_standard = []
    time_winograd = []
    time_improved = []

    with open(filename, "r") as f:
        for line in f:
            parts = line.split()
            if len(parts) == 4:
                size = int(parts[0])
                t1 = int(parts[1])
                t2 = int(parts[2])
                t3 = int(parts[3])

                sizes.append(size)
                time_standard.append(t1)
                time_winograd.append(t2)
                time_improved.append(t3)

    return sizes, time_standard, time_winograd, time_improved


def plot_graph(x, y, title, xlabel, ylabel, filename_base, color='blue'):
    plt.figure(figsize=(8,6))
    # Убрали marker='o'
    plt.plot(x, y, color=color)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))

    plt.savefig(f"{filename_base}.png", dpi=300)
    plt.savefig(f"{filename_base}.svg")
    plt.close()


def plot_comparison(x, y1, y2, y3, filename_base):
    plt.figure(figsize=(10,6))
    # Убрали marker='o'
    plt.plot(x, y1, color='blue', label='Обычный')
    plt.plot(x, y2, color='green', label='Виноград')
    plt.plot(x, y3, color='red', label='Улучшенный Виноград')
    plt.title("Сравнение алгоритмов умножения матриц")
    plt.xlabel("Размер матрицы")
    plt.ylabel("Время (тики)")
    plt.legend()
    plt.grid(True)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))

    plt.savefig(f"{filename_base}.png", dpi=300)
    plt.savefig(f"{filename_base}.svg")
    plt.close()



def main():
    filename = "results.txt"
    output_dir = "plots"
    os.makedirs(output_dir, exist_ok=True)

    sizes, time_standard, time_winograd, time_improved = read_data(filename)

    plot_graph(sizes, time_standard, "Время выполнения обычного умножения",
               "Размер матрицы", "Время (тики)",
               os.path.join(output_dir, "standard"), color='blue')

    plot_graph(sizes, time_winograd, "Время выполнения алгоритма Винограда",
               "Размер матрицы", "Время (тики)",
               os.path.join(output_dir, "winograd"), color='green')

    plot_graph(sizes, time_improved, "Время выполнения улучшенного алгоритма Винограда",
               "Размер матрицы", "Время (тики)",
               os.path.join(output_dir, "improved_winograd"), color='red')

    plot_comparison(sizes, time_standard, time_winograd, time_improved,
                    os.path.join(output_dir, "comparison"))


if __name__ == "__main__":
    main()
