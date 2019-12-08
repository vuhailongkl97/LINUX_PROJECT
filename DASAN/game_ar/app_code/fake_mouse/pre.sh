cat /proc/bus/input/devices  | grep mouse
ifconfig wlp2s0 | sed -n "s/.*inet[[:space:]]\([[:digit:]]*\.[[:digit:]]*\.[[:digit:]]\.[[:digit:]]*\).*$/\1/p"
