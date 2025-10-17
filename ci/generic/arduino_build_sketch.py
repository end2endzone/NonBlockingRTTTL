import os
import sys
import subprocess

import functools
print = functools.partial(print, flush=True)

# Boards to compile for
BOARDS = {
    "atmega328": "arduino:avr:nano:cpu=atmega328",
    "nodemcuv2": "esp8266:esp8266:nodemcuv2",
    "esp32": "esp32:esp32:esp32",
    "esp32wroverkit": "esp32:esp32:esp32wroverkit"
}

def find_product_source_dir():
    env_dir = os.environ.get("PRODUCT_SOURCE_DIR")
    if env_dir:
        return env_dir
    script_dir = os.path.dirname(os.path.abspath(__file__))
    return os.path.abspath(os.path.join(script_dir, "..", ".."))

def check_arduino_cli():
    cli_path = os.environ.get("ARDUINO_CLI_INSTALL_DIR", "")
    if cli_path:
        os.environ["PATH"] += os.pathsep + cli_path
    try:
        subprocess.run(["arduino-cli", "version"],
            stdout=sys.stdout,
            check=True
        )
    except FileNotFoundError:
        print("arduino-cli not found in PATH.")
        sys.exit(1)

def is_board_compatible(board, boards_file):
    try:
        with open(boards_file, "r") as f:
            lines = [line.strip() for line in f.readlines()]
            return "all" in lines or board in lines
    except FileNotFoundError:
        print(f"No boards.txt found at {boards_file}")
        return False

def compile_sketch(sketch_name):
    product_dir_path = find_product_source_dir()
    sketch_dir_path = os.path.join(product_dir_path, "examples", sketch_name)
    ino_file_path = os.path.join(sketch_dir_path, f"{sketch_name}.ino")
    boards_file_path = os.path.join(sketch_dir_path, "boards.txt")
    ino_file_name = os.path.basename(ino_file_path)

    if not os.path.isfile(ino_file_path):
        print(f"Sketch file not found: {ino_file_path}")
        sys.exit(1)

    if not os.path.isfile(boards_file_path):
        print(f"No boards.txt found at {boards_file_path}")
        sys.exit(1)

    print(f"Found boards.txt at {boards_file_path}\n")

    for board, fqbn in BOARDS.items():
        print("=" * 100)
        print(f"Compiling {ino_file_name} for ({board})")
        print("=" * 100)

        if is_board_compatible(board, boards_file_path):
            try:
                subprocess.run(
                    ["arduino-cli", "compile", "--fqbn", fqbn, ino_file_path],
                    stdout=sys.stdout,
                    cwd=sketch_dir_path,
                    check=True
                )
            except subprocess.CalledProcessError as e:
                print(f"Compilation failed for {board} with error code {e.returncode}")
                sys.exit(e.returncode)
        else:
            print(f"Skipping sketch compilation for {board} which is incompatible according to it's boards.txt file.")
        print("\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python compile_sketch.py <sketch_name>")
        sys.exit(1)

    check_arduino_cli()

    sketch_name = sys.argv[1]
    compile_sketch(sketch_name)
