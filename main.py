import pandas as pd
from matplotlib import pyplot as plt
from scipy.ndimage import gaussian_filter1d

GlobalPath = 'log/Perf/'


def smooth_chart(data_x: list, data_y: list, intensity: float = 0.1) -> pd.DataFrame:
    new_y = gaussian_filter1d(data_y, sigma=intensity)
    return pd.DataFrame(new_y, data_x)


def read_data(filename: str) -> pd.DataFrame:
    with open(file=GlobalPath + filename) as input_file:
        data = pd.read_csv(filepath_or_buffer=input_file, sep=',')
    return data


def show_by_columns(time_kind: str, intensity: float = 0.1) -> None:
    fig, ax = plt.subplots(num='Chart', layout='constrained', dpi=225)

    x_max = int(linear_data['Columns'].max())
    x_min = int(linear_data['Columns'].min())

    column_min = linear_data['Columns'].min()
    column_max = linear_data['Columns'].max()

    assert (linear_data["Rows"].max() == linear_data["Rows"].min())
    row = linear_data["Rows"][0]
    x_cross_point = row

    smooth_horizontal_binary = smooth_chart(horizontal_binary_data['Columns'].values,
                                            horizontal_binary_data[time_kind].values,
                                            intensity)

    smooth_vertical_binary = smooth_chart(vertical_binary_data['Columns'].values,
                                          vertical_binary_data[time_kind].values,
                                          intensity)

    smooth_linear_data = smooth_chart(linear_data['Columns'].values,
                                      linear_data[time_kind].values,
                                      intensity)

    smooth_staircase_data = smooth_chart(staircase_data['Columns'].values,
                                         staircase_data[time_kind].values,
                                         intensity)

    y_max = max(max(smooth_horizontal_binary.values),
                max(smooth_vertical_binary.values),
                max(smooth_staircase_data.values),
                max(smooth_linear_data.values))

    ax.plot(smooth_linear_data,
            label='linear search', color='black')
    ax.plot(smooth_staircase_data,
            label='staircase search', color='purple')
    ax.plot(smooth_vertical_binary,
            label='vertical binary search', color='pink')
    ax.plot(smooth_horizontal_binary,
            label='horizontal binary search', color='orange')

    ax.set_ylabel('ms', rotation=0, loc='bottom')
    ax.set_xlabel(f'Input data: Matrix [{column_min}..{column_max}]x{row}')
    ax.set_yticks(ax.get_yticks(), ax.get_yticklabels(), rotation=0)
    ax.set_xticks(ax.get_xticks(), ax.get_xticklabels(), rotation=-45)
    ax.axvline(x=x_cross_point, linestyle='-', label='Columns = Rows', color='cyan')
    ax.fill_between((x_min, x_cross_point), y_max, label='Columns < Rows', color='brown')
    ax.fill_between((x_cross_point, x_max), y_max, label='Columns > Rows', color='olive')

    ax.legend(loc='upper right')

    ax.set_yscale('symlog')
    # ax.set_xscale('symlog')

    plt.title(time_kind)
    plt.show()


def show_by_rows_and_columns_ratio(time_kind: str, intensity: float = 0.1) -> None:
    fig, ax = plt.subplots(num='Chart', layout='constrained', dpi=225)

    rows_by_columns_ratio = [row / column for row, column in zip(linear_data['Rows'], linear_data['Columns'])]

    x_max = max(rows_by_columns_ratio)
    x_min = min(rows_by_columns_ratio)

    assert (linear_data["Rows"].max() == linear_data["Rows"].min())
    row = linear_data["Rows"][0]
    x_cross_point = 1.0

    smooth_horizontal_binary = smooth_chart(rows_by_columns_ratio,
                                            horizontal_binary_data[time_kind].values,
                                            intensity)

    smooth_vertical_binary = smooth_chart(rows_by_columns_ratio,
                                          vertical_binary_data[time_kind].values,
                                          intensity)

    smooth_linear_data = smooth_chart(rows_by_columns_ratio,
                                      linear_data[time_kind].values,
                                      intensity)

    smooth_staircase_data = smooth_chart(rows_by_columns_ratio,
                                         staircase_data[time_kind].values,
                                         intensity)

    y_max = max(max(smooth_horizontal_binary.values),
                max(smooth_vertical_binary.values),
                max(smooth_staircase_data.values),
                max(smooth_linear_data.values))

    ax.plot(smooth_linear_data,
            label='linear search', color='black')

    ax.plot(smooth_horizontal_binary,
            label='horizontal binary search', color='orange')

    ax.plot(smooth_staircase_data,
            label='staircase search', color='purple')

    ax.plot(smooth_vertical_binary,
            label='vertical binary search', color='pink')

    column_min = linear_data['Columns'].min()
    column_max = linear_data['Columns'].max()
    ax.set_ylabel('ms', rotation=0, loc='bottom')
    ax.set_xlabel(f'Input data: [{column_min}..{column_max}]/{row}')

    ax.set_yticks(ax.get_yticks(), ax.get_yticklabels(), rotation=0)
    ax.set_xticks(ax.get_xticks(), ax.get_xticklabels(), rotation=-45)

    ax.axvline(x=x_cross_point, linestyle='-', label='Columns = Rows', color='cyan')

    ax.fill_between((x_min, x_cross_point), y_max, label='Columns < Rows',
                    color='brown')
    ax.fill_between((x_cross_point, x_max), y_max, label='Columns > Rows',
                    color='olive')

    ax.legend(loc='upper right')

    ax.set_yscale('symlog')
    # ax.set_xscale('symlog')

    plt.title(time_kind)
    plt.show()


linear_data = read_data('GCC' + 'linear_search.csv')
horizontal_binary_data = read_data('GCC' + 'horizontal_binary_search.csv')
staircase_data = read_data('GCC' + 'staircase_search.csv')
vertical_binary_data = read_data('GCC' + 'vertical_binary_search.csv')


def main() -> None:
    show_by_columns(time_kind="Avg", intensity=1)
    show_by_rows_and_columns_ratio(time_kind="Avg", intensity=2)


if __name__ == '__main__':
    main()
