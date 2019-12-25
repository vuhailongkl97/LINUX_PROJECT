echo "MQTT BROKER IP: $(ifconfig wlp2s0 | sed -n "s/.*inet[[:space:]]\([[:digit:]]*\.[[:digit:]]*\.[[:digit:]]\.[[:digit:]]*\).*$/\1/p")"
echo "Keyboard file : $(cat /proc/bus/input/devices | grep -A 5 keyboard | grep Handlers | sed -n "s/.*\(event[[:digit:]]*\).*$/\1/p")"
echo "mouse file : $(cat /proc/bus/input/devices  | grep -A 5 mousek |sed -n "s/.*\(event[[:digit:]]*\).*$/\1/p")"

make clean &> /dev/null
echo "start make fake mouse"
make &> /dev/null
test="$(lsmod | grep mousek)"

if [ -z "$test" ]; then 
        echo "insmode module"
        sudo insmod mousek.ko
else
        echo "module is exits . I will remove this module"
        sudo rmmod mousek
        sudo insmod mousek.ko
	if [ $? -ne 0 ]; then  
		echo "insmode failed"
	else 
		echo "insmode successfully"
	fi
fi
