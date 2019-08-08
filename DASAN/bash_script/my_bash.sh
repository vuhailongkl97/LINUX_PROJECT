#! /bin/bash

db_file="db.txt"
prefix_name="longkl_"
prefix_flag="longkl_flag_"
current_header="stdio.h"
FLAGS="-Wall"
OUTPUT_FILE="output.c"


function prepare_header()
{
	local is_header="true"
	local input=$1;

	if [ -z $input ]; then 
		echo "missing input file"
		exit 127
	fi

	while IFS= read -r line
	do
		if [ -z "$line" ] || [[ "$line" == [[:space:]]* ]]; then 
	
			#echo "null line prepare for header"
			is_header="true"
	
		else 
	
			if [[ "$is_header" == "true" ]] ; then 
				is_header="false";
	
				current_header="$line"
	
				IFS=' ' read -r -a array <<< "$line"
	
				if [ -z "${array[1]}" ]; then 
					array[1]="None"
				fi
	
				current_header=$(echo "${array[0]}" |  awk '{gsub(/\./, "_");} 1')
				eval ${prefix_flag}${current_header}="${array[1]}"
	
			else 
				#echo "this $line use $current_header"
				
				 for val in $line; do  
	
					  eval ${prefix_name}${val}="${current_header}"
	
				 done
			fi
		fi
	
	done < "$input"

	return 0
}

function get_library_flag_from_name()
{
	local lib_val tmp flag_val func_name func_name_in_db

	if [ -z $1 ]; then 
#echo "missing argument for add_library_header function"
		return 127
	fi

	func_name=$1
	func_name_in_db=${prefix_name}${func_name}

	if [ -z $func_name_in_db ]; then 
#echo "function name is not exits in db"
		return 127
	fi

	tmp_lib_val=$(echo ${!func_name_in_db}| awk '{gsub(/\_/, ".");} 1')

	if [ -z $tmp_lib_val ]; then 

#echo "$func_name have not library in db , please add to db.txt"
		return 127
	fi

	lib_val="#include\"$tmp_lib_val\""
	flag_val_in_db=${!func_name_in_db}
	flag_val="${prefix_flag}${flag_val_in_db}"

#echo "library of $func_name is $lib_val with flag is ${!flag_val}"
	echo "$lib_val ${!flag_val}"

	return 0
}

function add_header_to_source()
{
#echo "adding library $1 to make file"
	sed -e "1i\\$1" main.c  >& $OUTPUT_FILE
	return $? 
}

function add_flag_to_make_file()
{
#	echo "adding option $1 to make file"
	FLAGS="$FLAGS $1"

	echo "$FLAGS"

	return 0
}

function add_lib_flag()
{

	local ret_header ret_option
	local tmp array

	tmp=$(get_library_flag_from_name $1)

	if [[ $? != 0 ]]; then 
		return 127
	fi
	
	IFS=' ' read -r -a array <<< "$tmp"

#for element in ${array[@]}
#	do
#		echo $element
#	done 
	
	ret_header=$(add_header_to_source ${array[0]})
	ret_option=$(add_flag_to_make_file ${array[1]})

	if [[ ret_header == "failed"  || ret_option == "failed" ]]; then 
		echo "add lib flag failed"
		return 127 
	else 
#	echo "$ret_header"

		echo "make FLAGS=$ret_option"
		make FLAGS="$ret_option" FILE_IN=$OUTPUT_FILE
	fi
	return 0
}

function test_get_lib_flag()
{
	get_library_flag_from_name "printk"
	get_library_flag_from_name "printf"
	get_library_flag_from_name "kill"
	get_library_flag_from_name "SIGINT"
	get_library_flag_from_name "memset"
	get_library_flag_from_name "pthread_join"

}
function test_add_lib_flag()
{
	local ret 
	add_lib_flag $1
	if [[ $? != 0 ]]; then 
		echo "error at add_lib_flag for $1"
		return 127
	fi
	
}

#prepare_header $db_file
#if [[ $? != 0 ]]; then 
#	echo "prepare header failed"
#else 
#	echo "complete get db.txt"
#fi

#test_add_lib_flag "pthread_join"

#test_add_lib_flag "printf"
#test_add_lib_flag "SIGINT"
#echo ${database["kill"]}

