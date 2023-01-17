import json

import pandas as pd

GlobalPathRow = 'log/benchmark/'
GlobalPathParsed = 'log/benchmark/parsed_runs/'
GlobalPathCharts = 'log/charts/'

TargetTypes = {
    '2N': 'Target:0',
    '16N': 'Target:1'}

GeneratorTypes = {
    'A': 'Generator:0',
    'B': 'Generator:1'}

SearchTypes = {
    # 'Linear': 'Search:0',
    'Binary': 'Search:1',
    'Staircase': 'Search:2',
    'Staircase_bin': 'Search:3',
    'Staircase_exp': 'Search:4'
}


def read_data(absolute_path: str) -> pd.DataFrame:
    with open(absolute_path) as input_file:
        if 'csv' in absolute_path:
            data = pd.read_csv(filepath_or_buffer=input_file, sep=',')
        if 'json' in absolute_path:
            data = json.load(open(absolute_path))
    return data


def get_parsed_name(generator_type: GeneratorTypes,
                    target_type: TargetTypes,
                    search_type: SearchTypes,
                    ext: str = 'csv',
                    sep: str = '_') -> str:
    generator_name = list(GeneratorTypes.keys())[list(GeneratorTypes.values()).index(generator_type)]
    target_name = list(TargetTypes.keys())[list(TargetTypes.values()).index(target_type)]
    search_name = list(SearchTypes.keys())[list(SearchTypes.values()).index(search_type)]
    extension_name = f'.{ext}' if ext else ''

    return f"{generator_name}{sep}{target_name}{sep}{search_name}{extension_name}"
