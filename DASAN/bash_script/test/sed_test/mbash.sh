function mfunction()
{
	local tmp_val="li\\ $1"
	
#echo $tmp_val
	
	sed  -i -e "1i\\$1" main.c 

	return 0
}

mfunction $1

cat main.c
