#/bin/bash

N=$(./generator $1 > .temp_map && cat .temp_map | tee /dev/tty | ./lem-in -s > .temp_out && wc -l < .temp_out)
echo "#Here is the number of lines received:" $N
