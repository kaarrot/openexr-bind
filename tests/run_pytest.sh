#!/bin/bash

# set -u

this_file=$(readlink -f "${BASH_SOURCE[0]}")
this_dir=$(dirname $this_file)

export LD_LIBRARY_PATH=${this_dir}/../install_dir/lib:$LD_LIBRARY_PATH
export PYTHONPATH="${PYTHONPATH}:${this_dir}/../install_dir/lib/python2.7/site-packages/"
exec python2.7 -m pytest ${this_dir}/unit.py
