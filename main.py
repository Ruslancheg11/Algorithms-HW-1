import pandas as pd
import scipy.interpolate
from matplotlib import pyplot as plt
from scipy.interpolate import interp1d
import numpy as np

GlobalPath = "log/Perf/"


def smooth_chart(x_list: list, y_list: list) -> np.ndarray:
    spl = interp1d(x_list, y_list, kind='cubic')
    new_data = np.linspace(min(x_list), max(x_list), 500)
    return spl(new_data)


def read_data(filename: str) -> pd.DataFrame:
    with open(file=GlobalPath + filename) as input_file:
        data = pd.read_csv(filepath_or_buffer=input_file, sep=",")
    return data


def main() -> None:
    linear_data = read_data("FinderPerfTestlinear_search.csv")
    binary_data = read_data("FinderPerfTestbinary_search.csv")

    fig, ax = plt.subplots(figsize=(5, 2.7), layout='constrained', dpi=250)

    smooth_linear_data = smooth_chart(linear_data["Columns"].values, linear_data["Time"].values)
    smooth_binary_data = smooth_chart(binary_data["Columns"].values, binary_data["Time"].values)
    ax.plot(smooth_linear_data, label="linear search", color='red')
    ax.plot(smooth_binary_data, label="binary search", color='orange')
    ax.set_xlabel("time in ms")
    ax.set_ylabel('Input data')
    ax.set_yscale('log')
    ax.set_xscale('log')
    ax.legend()
    plt.show()


if __name__ == '__main__':
    main()
