# Copyright 2022 by Artem Ustsov

import os
import subprocess

right_result_1 = """database
 my_cstring
 10
 253.656
 20.3322
 1"""

right_result_2 = """my_storage
 my_cstring
 5
 253.656
 20.3322
 0"""

right_result_3 = """too few arguments, need at least 2, <prog> <--param=value> or <prog> <-pos> <value>"""

def system_run_command(command, ignore_stderr=True, additional_env=dict()):
    cmd_env = os.environ.copy()
    cmd_env.update(additional_env)
    p = subprocess.Popen(
        command,
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        env=cmd_env,
    )

    output, errors = p.communicate()
    if p.returncode or (not ignore_stderr and errors):
        return errors.decode("utf-8").strip()

    p.wait()
    result = output.decode("utf-8").strip()
    return result


if __name__ == "__main__":
    result_1 = system_run_command("./program_options -i 10 -f 253.656 --storage=database -d 20.33215669")
    assert result_1 == right_result_1, f"\nTEST_1 FAULT\nright: {right_result_1.split()}\ngiven: {result_1.split()}"

    result_2 = system_run_command("./program_options -f 253.656 -d 20.33215669 --boolean=false")
    assert result_2 == right_result_2, f"\nTEST_2 FAULT\nright: {right_result_2.split()}\ngiven: {result_2.split()}"

    result_3 = system_run_command("./program_options", ignore_stderr=False)
    assert result_3 == right_result_3, f"\nTEST_3 FAULT\nright: {right_result_3.split()}\ngiven: {result_3.split()}"
