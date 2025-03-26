#!/bin/sh -e
# Se invoca así:
# python3 rx_apt.py --freq=137.1e6 --path="/home/mdoallo/" --rfgain=30 --timeout=900
#
# NOAA-15 137,62 MHz AGC Off, --rfgain=45
# NOAA-18 137,9125 MHz
# NOAA-19 137,1
#
cd /home/mdoallo/operaciones/rx/
# Para NOAA-18
python3 /usr/local/src/rx/rx_apt.py --freq=137.9125e6 --path="/mnt/pasadas/wav/" --file-name="NOAA-18_pass_" --rfgain=30 --timeout=900
