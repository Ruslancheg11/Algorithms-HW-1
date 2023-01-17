from matplotlib import pyplot as plt

from general import *


def plot_chart(log: bool = False, title: str = None, png_prefix: str = '', **kwargs) -> None:
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
            lines.append(read_data(GlobalPathParsed + run_report))
        name = (run_report.split('_')[-1]).split('.')[0]
        names.append(name)

    gen = chart_files[0].split('_')[0]
    target = chart_files[0].split('_')[1]

    title = f"Generator:{gen} Target:{target}" if title is None else title
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
    for target_name, target_key in TargetTypes.items():
        for generator_name, generator_key in GeneratorTypes.items():
            for Logarithmic in [True, False]:
                lines = []
                for search_name, search_key in SearchTypes.items():
                    lines.append(get_parsed_name(generator_key, target_key, search_key,
                                                 ext='csv'))

                plot_chart(log=Logarithmic, png_prefix='First',
                           binary=lines[0],
                           staircase=lines[1],
                           staircase_bin=lines[2],
                           staircase_exp=lines[3])

    first = get_parsed_name(GeneratorTypes['A'], TargetTypes['2N'], SearchTypes['Staircase_exp'],
                            ext='csv')
    second = get_parsed_name(GeneratorTypes['B'], TargetTypes['16N'], SearchTypes['Staircase_exp'],
                             ext='csv')

    for Logarithmic in [True, False]:
        plot_chart(log=Logarithmic, title='Generators A, B, Targets 2N, 16N', png_prefix='Second',
                   staircase_exp_A_2N=first,
                   staircase_exp_B_16N=second)


if __name__ == '__main__':
    main()
