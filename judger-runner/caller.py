import argparse
import runner

def main():
    parser = argparse.ArgumentParser(description="Compile and run a file using runner.")
    parser.add_argument("--filename", type=str, default="main.py", help="The filename to compile and run.")
    args = parser.parse_args()

    result = runner.auto_compile_and_run(args.filename)
    print(result)

if __name__ == "__main__":
    main()