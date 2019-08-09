#! /bin/bash

source ../../lib_bash.sh

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
	add_lib_flag $1 $2
	if [[ $? != 0 ]]; then 
		echo "error at add_lib_flag for $1"
		return 127
	fi
	
}
function test_add_semicolon()
{
	add_semicolon $1
	
	if [[ $? != 0 ]]; then 
		echo "add semicolon failed"
	fi

}

prepare_header $db_file
if [[ $? != 0 ]]; then 
	echo "prepare header failed"
else 
	echo "complete get db.txt"
fi

test_add_lib_flag "main.c" "SIGINT"


#test_add_semicolon  $1

