import json
import pandas as pd

from charts_info import *


def read_data(filename: str) -> pd.DataFrame:
    with open(file=GlobalPathRow + filename) as input_file:
        if 'csv' in filename:
            data = pd.read_csv(filepath_or_buffer=input_file, sep=',')
        if 'json' in filename:
            data = pd.read_json(path_or_buf=input_file)
    return data


def parse_benchmark_report(filename: str) -> None:
    data = json.load(open(GlobalPathRow + filename))
    df = pd.DataFrame(data['benchmarks'])
    for target_type in TargetTypes.keys():
        for search_type in SearchTypes.keys():
            for generator_type in GeneratorTypes.keys():
                filename = get_chart_name(generator_type, target_type, search_type, sep='_', ext='csv')
                with open(GlobalPathParsed + filename, "w") as f:
                    f.write(f'Rows,Columns,Time\n')
                    for name, cpu_time, run_type in zip(df['name'], df['cpu_time'], df['run_type']):
                        # if run_type == 'iteration':
                        #     continue
                        # if 'median' in name:
                        if target_type in name and generator_type in name and search_type in name:
                            attr = dict((x.split(':')) for x in name.split('/')[2::])
                            f.write(f"{attr['Rows']},{attr['Columns']},{cpu_time}\n")


def main() -> None:
    parse_benchmark_report('Overall.json')


if __name__ == '__main__':
    main()
