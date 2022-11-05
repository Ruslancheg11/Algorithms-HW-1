from general import *


def parse_benchmark_report(filename: str) -> None:
    data = read_data(GlobalPathRow + filename)
    df = pd.DataFrame(data['benchmarks'])
    for target_name, target_key in TargetTypes.items():
        for search_name, search_key in SearchTypes.items():
            for generator_name, generator_key in GeneratorTypes.items():
                filename = get_parsed_name(generator_key, target_key, search_key, ext='csv')
                buffered_string = ''
                for name, cpu_time, repetitions in zip(df['name'], df['cpu_time'], df['repetitions']):
                    if repetitions == 1 or 'median' in name:
                        if target_key in name and generator_key in name and search_key in name:
                            attr = dict((x.split(':')) for x in name.split('/')[2::])
                            buffered_string += f"{attr['Rows']},{attr['Columns']},{cpu_time}\n"
                if buffered_string:
                    with open(GlobalPathParsed + filename, "w") as f:
                        f.write('Rows,Columns,Time\n')
                        f.write(buffered_string)


def main() -> None:
    parse_benchmark_report('Overall.json')


if __name__ == '__main__':
    main()
