import subprocess

result = subprocess.run(
    ["bash", "tests/cli/bash/repl.sh"],
    capture_output=True,
    text=True
)

print("stdout: ", result.stdout)
print("stderr: ", result.stderr)
print("exitcode: ", result.returncode)