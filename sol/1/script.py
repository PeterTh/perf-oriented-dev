import os
import subprocess
from statistics import mean, variance
import csv

def run_benchmark(benchmark, repetitions):
    """
    Runs a benchmark program for a specified number of repetitions and returns
    a dictionary containing the average performance metrics.
    """
    elapsed_times = []
    user_times = []
    system_times = []

    for _ in range(repetitions):
        args = [f"./{benchmark[0]}"] + benchmark[1].split()
        result = subprocess.run(["/bin/time"] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output_lines = result.stderr.decode().strip().split("\n")
        
        # Extracting time information from the first line
        time_info = output_lines[0].split()
        print(time_info)
        user_time = float(time_info[0][:-4])
        system_time = float(time_info[1][:-6])
        elapsed_time = time_info[2][:-8]
        minutes, seconds = elapsed_time.split(":")
        elapsed_time = float(minutes) * 60 + float(seconds)

        elapsed_times.append(elapsed_time)
        user_times.append(user_time)
        system_times.append(system_time)

    avg_elapsed_time = mean(elapsed_times)
    avg_user_time = mean(user_times)
    avg_system_time = mean(system_times)
    var_elapsed_time = variance(elapsed_times)
    var_user_time = variance(user_times)
    var_system_time = variance(system_times)

    return {
        "Benchmark": benchmark[0],
        "Avg Elapsed Time (s)": avg_elapsed_time,
        "Avg User Time (s)": avg_user_time,
        "Avg System Time (s)": avg_system_time,
        "Var Elapsed Time (s^2)": var_elapsed_time,
        "Var User Time (s^2)": var_user_time,
        "Var System Time (s^2)": var_system_time
    }

def main():
    # Define benchmarks and repetitions
    benchmarks = [("delannoy", "10"), ("nbody", ""), ("mmul", ""), ("filesearch", ""), ("filegen", "100 100 500 700 1")]
    repetitions = 5

    # System information
    print("System Configuration:")
    os.system("uname -a")
    os.system("free -m")

    results_list = []
    for benchmark in benchmarks:
        results = run_benchmark(benchmark, repetitions)
        results_list.append(results)
        print(f"{results['Benchmark']}:\t\nAvg Elapsed Time - {results['Avg Elapsed Time (s)']:.4f}s, Avg User Time - {results['Avg User Time (s)']:.4f}s, Avg System Time - {results['Avg System Time (s)']:.4f}s,\t\nVar Elapsed Time - {results['Var Elapsed Time (s^2)']:.4f}s^2, Var User Time - {results['Var User Time (s^2)']:.4f}s^2, Var System Time - {results['Var System Time (s^2)']:.4f}s^2")

    # Write results to CSV
    with open("benchmark_results.csv", "w", newline="") as csvfile:
        fieldnames = ["Benchmark", "Avg Elapsed Time (s)", "Avg User Time (s)", "Avg System Time (s)", "Var Elapsed Time (s^2)", "Var User Time (s^2)", "Var System Time (s^2)"]
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for result in results_list:
            writer.writerow(result)

if __name__ == "__main__":
    main()
