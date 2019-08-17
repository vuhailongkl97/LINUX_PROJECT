#!/bin/bash

source ../../lib_bash.sh

declare -a data
data=(0 0 0 0 0)
error_type=(0 0 0 0 0)
input_file_check=$1
output_file_check="output.txt"
output_file_check_after_find="output2.txt"

if [ -z "$input_file_check" ] ; then 
	echo "failed"	
	exit 0
fi

function_search()
{
   result=0;
   
   input="$output_file_check_after_find"
	#store err
   	j=0
   	for i in $@;
      	do
	      err_type[$j]=$i
	      j=($j+1);
      	done

	#handler_err
	while read line;
	do
		local check_turn
		for i in ${err_type[@]};
		do
			local err_input=$i
			local check_available=0
		      	check_available=$(echo $line|grep "$err_input"|wc -l)
			if [ $check_available == 1 ];
			then
				# echo "available $err_input"
				# unknown type name error
                        	header=$(echo $line|awk '{print $2}'|cut -d':' -f1)
                        	ps=$(echo $line|awk '{print $0}'|cut -d':' -f2)

				# check unknown

                        	er=$(echo $line|awk '{for ( i = 1; i <= NF; i++ )
                        	if ( $i=="name" ) print $(i+1)}')

				# check implicit

                        	er1=$(echo $line|awk '{for ( i = 1; i <= NF; i++ )
                        	if ( $i=="function" ) print $(i+1)}')

                        	# variable detect missing pthread flags

                        	er2=$(echo $line|awk '{for ( i = 1; i <= NF; i++ )
                        	if ( $i=="reference" ) print $(i+2)}')
                        	if [ -z $er2 ]; then
                        	        temp=10;
                        	else
                        	        err_input="reference";
                        	        ps="0"
                        	fi

				# undeclared MACRO or variable

				if [ $err_input == "undeclared" ];
				then
					er=$(echo $line|awk -v mvar=$err_input '{for ( i = 1; i <= NF; i++ )
					if ( $i==mvar ) print $(i-1)}')
				fi
				if [ $err_input == "expected" ];
				then
				er=$(echo $line|awk -v mvar=$err_input '{for ( i = 1; i <= NF; i++ )
				if ( $i==mvar ) print $(i+1)}')
				fi

                        	# output > 4 fields return

                        	out_data=$(echo "$header $err_input $er $er1 $er2 $ps"|wc -w)
                        	if [ $out_data -gt 4 ]; then
                        	        echo "None None None None"
                        	        return 127
                        	else
                        	        echo "$header $err_input $er $er1 $er2 $ps"
                        	fi
							check_turn=1
			else
				out=$(echo "unavailable $err_input")
				check_turn=0
			fi
		if (( $check_turn == 1 ));
		then
			return 0
		fi
			
		done
	done < "$input"
	echo "None None None None"
        return 127
}

function_handler_input() 
{
     local err_type_processed
     j=0
     for i in $@;
     do
	      err_type_processed[$j]=$i
	      err_type_processed[$j]=$(echo $i|sed 's/_/ /')
	      j=($j+1);
     done

     local leg=$(echo $@|wc -w)
     leg=$(($leg-2))

    if [ $1 == "error:" ];
    then
	    	#echo "error handling"

		local check_line=0;
		check_line=$(grep "undefined reference" output.txt|wc -l)
			
		#[ -f $output_file_check ] && echo " file is not exist"  && exit 1
		if [ $check_line -ge 1 ];
		then
			awk '/undefined reference/ {print NR,$0}' $output_file_check &> $output_file_check_after_find
		else
			awk '/error:/ {print NR,$0}' $output_file_check &> $output_file_check_after_find
		fi

     		for (( i=0;i<=$leg;i++ ))
     		do
     		        err_type_processed[$i]=${err_type_processed[$i+1]}
 			err_type_processed[$i+1]=""
     		done
	    	function_search ${err_type_processed[@]}
    elif [ $1 == "warning:" ];
    then
	    	#echo "warning handling"
	    	awk '/warning:/ {print NR,$0}' $output_file_check > $output_file_check_after_find 
	    	for (( i=0;i<=$leg;i++ ))
     		do
     		        err_type_processed[$i]=${err_type_processed[$i+1]}
			err_type_processed[$i+1]=""
     		done
		function_search ${err_type_processed[@]}
    else
	    	echo note
    fi
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

	add_lib_flag $1 $2
	if [[ $? != 0 ]]; then 
		echo "error at add_lib_flag for $1"
		return 127
	fi
	return 0
}

function test_add_semicolon()
{
	add_semicolon $1
	
	if [[ $? != 0 ]]; then 
		echo "add semicolon failed"
	fi

}

function check_un_ex_und()
{
	local ret ret2
	local array_issue_error=("unknown" "expected" "undeclared" "undefined_reference" )
	local array_issue_warning=("implicit")
	if [[ $1 == "warning" ]]; then 
		ret=$(function_handler_input warning: ${array_issue_warning[@]})
	elif [[ $1 == "error" ]]; then 
		ret=$(function_handler_input error: ${array_issue_error[@]})
	
	fi
#cat "$output_file_check_after_find"
	#echo checking this $ret

	if [[ $ret != "None None None None" ]]; then 

		IFS=' ' read -r -a array <<< "$ret"
		
		local length=${#array[2]} 
		(( length -=2 ))	
		local tmp_var=$(echo ${array[2]:1:$length})

		test_add_lib_flag "${array[0]}" $tmp_var
		ret2=$?
		echo $ret is 
#echo "r	et from test_add_lib_flag is $?"

		if [[ $ret2 != 0 ]]; then 
#echo "f	ailed in check un ex und"
			return 127	
		else 
			return 0;
		fi
	else 
		return 127;
	fi

}

function rebuild()
{   
	local input_file=$1
#echo "$oFLAG"
	make FLAGS="$oFLAGS" FILE_IN="$input_file" &> "$output_file_check"
}

prepare_header $db_file
if [[ $? != 0 ]]; then 
	echo "prepare header failed"
else 
	echo "complete get db.txt"
fi

function mloop()
{
	local ret
	rebuild "$input_file_check"
	array=( "error"  "warning" "handler" )
	for i in "${array[@]}"
	do
		while : ; do 
		echo "starting scan $i"
		check_un_ex_und "$i"
		ret=$?
#echo "ret after check un_ex_und is $?"
		if [[ $ret != 0 ]]; then 
	#		echo "skip this warning, this warning have supported yet"		
			break
		fi

#head -n 3 output.c
		rebuild "$input_file_check"
		done ;	
	done

	rm  -f $output_file_check_after_find 
	make clean_trash

}
mloop
cat $input_file_check 
#array_issue_error=("unknown" "expected" "undeclared" "undefined_reference" )
#function_handler_input error: ${array_issue_error[@]}
