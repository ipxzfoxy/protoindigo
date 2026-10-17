from pathlib import Path
import subprocess

TESTS = Path("tests/scripts")

def dodir(path):
    print("============== NEW DIR ==============")
    for file in Path(path).iterdir():
        if file.is_dir():
            dodir(file)
            continue
        print("============== RUNNING ", file, " ==============")
        result = subprocess.run(
            ["./build/Debug/indigo.exe", file],
            capture_output=True,
            text=True
        )
        print("stdout: ", result.stdout, "\n----------------------------------------------------------")
        print("stderr: ", result.stderr, "\n----------------------------------------------------------")
        print("exitcode: ", result.returncode, "\n----------------------------------------------------------")

dodir(TESTS)