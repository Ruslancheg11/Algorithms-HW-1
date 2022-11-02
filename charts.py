import pandas as pd
from matplotlib import pyplot as plt

from charts_info import *


def read_data(filename: str) -> pd.DataFrame:
    with open(file=GlobalPathParsed + filename) as input_file:
        if 'csv' in filename:
            data = pd.read_csv(filepath_or_buffer=input_file, sep=',')
        if 'json' in filename:
            data = pd.read_json(path_or_buf=input_file)
    return data


def plot_charts(log: bool = False, png_prefix: str = '', **kwargs) -> None:
    plt.close('all')
    fig, ax = plt.subplots(num='Chart', layout='constrained', dpi=225)

    x_min, x_max = float('inf'), float('-inf')
    const_columns = 8192

    names = []
    lines = []

    chart_names = list(kwargs.keys())
    chart_files = list(kwargs.values())

    for run_report in chart_files:
        with open(GlobalPathParsed + run_report) as f:
            lines.append(read_data(run_report))
        name = (run_report.split('_')[-1]).split('.')[0]
        names.append(name)

    gen = chart_files[0].split('_')[0]
    target = chart_files[0].split('_')[1]

    title = f"Generator:{gen} Target:{target}"
    png_name = f"{png_prefix}_{gen}_{target}_Log.png" if log else f"{png_prefix}_{gen}_{target}_Linear.png"

    for file in lines:
        x_data = file['Rows'].values
        y_data = file['Time'].values

        x_min = min(min(x_data), x_min)
        x_max = max(max(x_data), x_max)

        ax.plot(x_data,
                y_data)

    ax.set_ylabel('ns', rotation=90)
    ax.set_xlabel(f'Input data: Matrix [{x_min}..{x_max}]x{const_columns}')

    ax.set_xticks(ax.get_xticks(), ax.get_xticklabels(), rotation=-45)
    if log:
        # ax.set_ylim(0)
        # ax.set_xlim(x_min)

        ax.set_yscale('log')
        ax.set_xscale('log')
    if not log:
        ax.set_ylim(0)
        ax.set_xlim(-500)

    ax.legend(chart_names, loc='upper right')
    plt.title(title)

    plt.savefig(GlobalPathCharts + png_name, dpi=300)
    # plt.show()


def main() -> None:
    for gen in GeneratorTypes.keys():
        for tar in TargetTypes.keys():
            staircase = get_chart_name(gen, tar, 'Search:2', sep='_', ext='csv')
            staircase_bin = get_chart_name(gen, tar, 'Search:3', sep='_', ext='csv')
            staircase_exp = get_chart_name(gen, tar, 'Search:4', sep='_', ext='csv')
            plot_charts(log=False, png_prefix='First',
                        staircase=staircase,
                        staircase_bin=staircase_bin,
                        staircase_exp=staircase_exp)

    first = get_chart_name('Generator:0', 'Target:0', 'Search:4', sep='_', ext='csv')
    second = get_chart_name('Generator:1', 'Target:1', 'Search:4', sep='_', ext='csv')
    plot_charts(log=False, png_prefix='Second',
                staircase_exp_A_A=first,
                staircase_exp_B_B=second)


if __name__ == '__main__':
    main()
