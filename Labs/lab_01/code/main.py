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
    plt.figure(figsize=(10, 8))
    plt.subplots_adjust(left=0.15, bottom=0.15, right=0.95, top=0.9)
    
    plt.plot(x, y, color=color, linewidth=2)
    plt.title(title, fontsize=14, pad=20)
    plt.xlabel(xlabel, fontsize=12, labelpad=10)
    plt.ylabel(ylabel, fontsize=12, labelpad=10)
    plt.grid(True, alpha=0.3)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))
    
    plt.tick_params(axis='both', which='major', labelsize=10)

    plt.savefig(f"{filename_base}.png", dpi=300, bbox_inches='tight', pad_inches=0.5)
    plt.savefig(f"{filename_base}.svg", bbox_inches='tight', pad_inches=0.5)
    plt.close()


def plot_comparison(x, y1, y2, y3, filename_base):
    plt.figure(figsize=(12, 8))
    plt.subplots_adjust(left=0.15, bottom=0.15, right=0.95, top=0.9)
    
    plt.plot(x, y1, color='blue', linestyle='-', linewidth=2, label='Обычный')
    plt.plot(x, y2, color='green', linestyle='--', linewidth=2, label='Виноград')
    plt.plot(x, y3, color='red', linestyle=':', linewidth=2, label='Улучшенный Виноград')
    plt.title("Сравнение алгоритмов умножения матриц", fontsize=14, pad=20)
    plt.xlabel("Размер матрицы", fontsize=12, labelpad=10)
    plt.ylabel("Время (тики)", fontsize=12, labelpad=10)
    plt.legend(fontsize=12)
    plt.grid(True, alpha=0.3)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))
    
    plt.tick_params(axis='both', which='major', labelsize=10)

    plt.savefig(f"{filename_base}.png", dpi=300, bbox_inches='tight', pad_inches=0.5)
    plt.savefig(f"{filename_base}.svg", bbox_inches='tight', pad_inches=0.5)
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