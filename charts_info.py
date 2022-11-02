GlobalPathRow = 'log/benchmark/'
GlobalPathParsed = 'log/benchmark/parsed_runs/'
GlobalPathCharts = 'log/charts/'

TargetTypes = {
    'Target:0': '2N',
    'Target:1': '16N'}

GeneratorTypes = {
    'Generator:0': 'A',
    'Generator:1': 'B'}

SearchTypes = {
    'Search:0': 'Linear',
    'Search:1': 'Binary',
    'Search:2': 'Staircase',
    'Search:3': 'Staircase(Bin)',
    'Search:4': 'Staircase(Exp)'
}


def get_chart_name(generator_type: GeneratorTypes = '',
                   target_type: TargetTypes = '',
                   search_type: SearchTypes = '',
                   sep: str = '',
                   ext: str = '') -> str:
    generator_type_name = GeneratorTypes[generator_type] if generator_type else ''
    target_type_name = TargetTypes[target_type] if target_type else ''
    search_type_name = SearchTypes[search_type] if search_type else ''
    extension_name = f'.{ext}' if ext else ''

    return f"{generator_type_name}{sep}{target_type_name}{sep}{search_type_name}{extension_name}"
