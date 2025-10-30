import matplotlib.pyplot as plt
import os
import matplotlib.ticker as ticker


def read_data(filename):
    sizes = []
    time_iterative = []
    time_recursive = []

    with open(filename, "r") as f:
        for line in f:
            if line.startswith('#'):
                continue
            parts = line.split()
            if len(parts) == 3:
                size = int(parts[0])
                t_iter = int(parts[1])
                t_rec = int(parts[2])

                sizes.append(size)
                time_iterative.append(t_iter)
                time_recursive.append(t_rec)

    return sizes, time_iterative, time_recursive


def plot_iterative(x, y_iter, filename_base):
    plt.figure(figsize=(12, 8))
    plt.subplots_adjust(left=0.15, bottom=0.15, right=0.95, top=0.9)

    plt.plot(x, y_iter, color='blue', linestyle='-', linewidth=2)
    plt.title("Зависимость времени выполнения итеративного алгоритма от длины последовательности", fontsize=14, pad=20)
    plt.xlabel("Длина последовательности", fontsize=12, labelpad=10)
    plt.ylabel("Время (тики)", fontsize=12, labelpad=10)
    plt.grid(True, alpha=0.3)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))

    plt.tick_params(axis='both', which='major', labelsize=10)

    plt.savefig(f"{filename_base}.png", dpi=300, bbox_inches='tight', pad_inches=0.5)
    plt.savefig(f"{filename_base}.svg", bbox_inches='tight', pad_inches=0.5)
    plt.close()


def plot_recursive(x, y_rec, filename_base):
    plt.figure(figsize=(12, 8))
    plt.subplots_adjust(left=0.15, bottom=0.15, right=0.95, top=0.9)

    plt.plot(x, y_rec, color='red', linestyle='-', linewidth=2)
    plt.title("Зависимость времени выполнения рекурсивного алгоритма от длины последовательности", fontsize=14, pad=20)
    plt.xlabel("Длина последовательности", fontsize=12, labelpad=10)
    plt.ylabel("Время (тики)", fontsize=12, labelpad=10)
    plt.grid(True, alpha=0.3)

    plt.gca().yaxis.set_major_locator(ticker.AutoLocator())
    plt.gca().yaxis.set_major_formatter(ticker.StrMethodFormatter("{x:.0f}"))

    plt.tick_params(axis='both', which='major', labelsize=10)

    plt.savefig(f"{filename_base}.png", dpi=300, bbox_inches='tight', pad_inches=0.5)
    plt.savefig(f"{filename_base}.svg", bbox_inches='tight', pad_inches=0.5)
    plt.close()


def plot_both_algorithms(x, y_iter, y_rec, filename_base):
    plt.figure(figsize=(12, 8))
    plt.subplots_adjust(left=0.15, bottom=0.15, right=0.95, top=0.9)

    plt.plot(x, y_iter, color='blue', linestyle='-', linewidth=2, label='Итеративный')
    plt.plot(x, y_rec, color='red', linestyle='--', linewidth=2, label='Рекурсивный')
    plt.title("Сравнение времени выполнения итеративного и рекурсивного алгоритмов", fontsize=14, pad=20)
    plt.xlabel("Длина последовательности", fontsize=12, labelpad=10)
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
    filename = "time_measurements.txt"
    output_dir = "plots"
    os.makedirs(output_dir, exist_ok=True)

    sizes, time_iterative, time_recursive = read_data(filename)
    plot_iterative(sizes, time_iterative, os.path.join(output_dir, "iterative"))
    plot_recursive(sizes, time_recursive, os.path.join(output_dir, "recursive"))
    plot_both_algorithms(sizes, time_iterative, time_recursive,
                         os.path.join(output_dir, "comparison"))


if __name__ == "__main__":
    main()