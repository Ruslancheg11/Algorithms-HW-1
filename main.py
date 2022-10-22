import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from scipy.interpolate import interp1d

GlobalPath = 'log/Perf/'


def make_ideal(x_list: list, y_list: list, length: int) -> pd.DataFrame:
    new_x_list = np.array([])
    new_y_list = np.array([])
    for x, y in zip(x_list, y_list):
        for _ in range(length // len(x_list)):
            np.append(new_x_list, x)
            np.append(new_y_list, y)
    return pd.DataFrame(new_x_list, new_y_list)


def smooth_chart(x_list: list, y_list: list) -> np.ndarray:
    spl = interp1d(x_list, y_list, kind='cubic')
    new_data = np.linspace(min(x_list), max(x_list), 100)
    return spl(new_data)


def read_data(filename: str) -> pd.DataFrame:
    with open(file=GlobalPath + filename) as input_file:
        data = pd.read_csv(filepath_or_buffer=input_file, sep=',')
    return data


def main() -> None:
    linear_data = read_data('linear_search.csv')
    binary_data = read_data('binary_search.csv')
    staircase_data = read_data('staircase_search.csv')
    vert_binary_data = read_data('vert_binary_search.csv')

    linear_data.reindex(index=linear_data.index[::-1])
    binary_data.reindex(index=binary_data.index[::-1])
    staircase_data.reindex(index=staircase_data.index[::-1])
    vert_binary_data.reindex(index=vert_binary_data.index[::-1])

    fig, ax = plt.subplots(figsize=(5, 3.5), layout='constrained', dpi=225)

    # rows_by_columns_ratio = [x / y for x, y in zip(linear_data['Rows'].values, linear_data['Columns'])]
    #
    # ax.plot(rows_by_columns_ratio, linear_data['Time'].values,
    #         label='linear search', color='black')
    #
    # ax.plot(rows_by_columns_ratio, binary_data['Time'].values,
    #         label='binary search', color='orange')
    #
    # ax.plot(rows_by_columns_ratio, staircase_data['Time'].values,
    #         label='staircase search', color='purple')
    #
    # ax.plot(rows_by_columns_ratio, vert_binary_data['Time'].values,
    #         label='vertical binary search', color='pink')

    rows_multiply_columns = [x * y for x, y in zip(linear_data['Rows'].values, linear_data['Columns'])]

    ax.plot(rows_multiply_columns, linear_data['Time'].values,
            label='linear search', color='black')

    ax.plot(rows_multiply_columns, binary_data['Time'].values,
            label='binary search', color='orange')

    ax.plot(rows_multiply_columns, staircase_data['Time'].values,
            label='staircase search', color='purple')

    ax.plot(rows_multiply_columns, vert_binary_data['Time'].values,
            label='vertical binary search', color='pink')

    # ax.plot(linear_data['Columns'].values, linear_data['Time'].values,
    #         label='linear search', color='black')
    #
    # ax.plot(binary_data['Columns'].values, binary_data['Time'].values,
    #         label='binary search', color='orange')
    #
    # ax.plot(staircase_data['Columns'].values, staircase_data['Time'].values,
    #         label='staircase search', color='purple')
    #
    # ax.plot(vert_binary_data['Columns'].values, vert_binary_data['Time'].values,
    #         label='vertical binary search', color='pink')

    ax.set_ylabel('Time[ms]')
    ax.set_xlabel('Input data')
    ax.set_yscale('log')
    ax.set_xscale('log')
    ax.legend()
    plt.show()


if __name__ == '__main__':
    main()
