# Copyright 2022 by Artem Ustsov

import os
import subprocess


right_result = """database
my_cstring
5
253.656
20.3322
0"""

def system_run_command(command, ignore_stderr=True, additional_env=dict()):
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
    result = system_run_command("./program_options -i 5 -f 253.656 --storage=database -d 20.33215669 --boolean=false")
    assert result == right_result, f"\nright: {right_result.split()}\ngiven: {result.split()}"
