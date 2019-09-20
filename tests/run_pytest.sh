#!/bin/bash

export PYTHONPATH="${PYTHONPATH}:`pwd`/../install_dir/lib/python2.7/site-packages/"
exec python2.7 -m pytest unit.py
