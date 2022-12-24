import logging
import os
import subprocess


right_result = """0 A0 Error: Cycle vertex
1 B2 Error: Cycle vertex
2 A1 Error: Cycle vertex
3 A3 Error: Cycle vertex
4 A4 Error: Cycle vertex
5 A5 Value: 10
6 A6 Value: 100
7 A7 Value: 202
8 A8 Value: 2
9 G9 Error: Vertex is not defined
10 G10 Error: Vertex is not defined
11  Error: Vertex is not defined"""

def system_run_command(command, ignore_stderr = True, additional_env=dict()):
    logging.debug('Run command %s', command)
    cmd_env = os.environ.copy()
    cmd_env.update(additional_env)
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                         env=cmd_env)
    output, errors = p.communicate()
    if p.returncode or (not ignore_stderr and errors):
        raise IOError("CMD = [{}]\nErrors: {}".format(command, errors if errors else "[]"))
    p.wait()
    result = output.decode("utf-8").strip()
    return result


if __name__ == "__main__":
    result = system_run_command("./build/solution ./inp/test.txt")
    assert result == right_result
