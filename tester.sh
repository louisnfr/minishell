#!/bin/bash

RED="\033[38;5;203m"
ORANGE="\033[38;5;215m"
YELLOW="\033[38;5;229m"
GREEN="\033[38;5;121m"
LIGHT_BLUE="\033[38;5;123m"
BLUE="\033[1;38;5;33m"
RESET="\033[0m"

make

sum=0
right=0
false=0
total_sum=0
total_right=0
total_false=0
COLS=$(tput cols)
TITLE=".............................  START TEST  ............................"
END="..............................  END TEST  ............................."
COLS=$(tput cols)
printf "\n${BLUE}%*s${RESET}\n" $(((${#TITLE} + $COLS) / 2)) "$TITLE"

function execute_test()
{
	SEP="..................................................................................."

	MY_RESULT=$(echo $@ "; exit" | ./minishell 2>/dev/null | sed '/^minishell/d')
	MY_EXIT_STATUS=$?

	REF_BASH=$(echo $@ "; exit" | bash --posix 2>/dev/null  | sed '/^minishell/d')
	REF_EXIT_STATUS=$?

	if [ "$MY_RESULT" == "$REF_BASH" ] && [ "$MY_EXIT_STATUS" == "$REF_EXIT_STATUS" ]
	then
	   	echo -e "${GREEN}   ✔  $1${RESET}"
		right=`expr $right + 1`
	else
		printf "\n${ORANGE}%*s${RESET}\n\n" $(((${#SEP} + $COLS) / 2)) "$SEP"
		echo -e "${RED}   ✘  $1${RESET}"
		false=`expr $false + 1`

		if [ "$MY_RESULT" != "$REF_BASH" ]
		then
			printf "\n"
	        echo -e "     ${RED}Your result${RESET}\t   :   $MY_RESULT"
	        echo -e "     ${ORANGE}Expected result${RESET}\t   :   $REF_BASH"
		fi
		if [ "$MY_EXIT_STATUS" != "$REF_EXIT_STATUS" ]
		then
			printf "\n"
	        echo -e "     ${RED}Your exit_status${RESET}\t   :  $MY_EXIT_STATUS"
	        echo -e "     ${ORANGE}Expected exit_status${RESET}  :  $REF_EXIT_STATUS"
		fi
		printf "\n${ORANGE}%*s${RESET}\n\n" $(((${#SEP} + $COLS) / 2)) "$SEP"
	fi
}

function run_test()
{
	sum=0
	right=0
	false=0
	TEST=$(echo $1 | cut -c 7- | sed 's/.txt//g' | tr 'a-z' 'A-Z')
	SEP="========================"

	printf "\n${BLUE}%*s\n" $(((${#SEP} + $COLS) / 2)) "$SEP"
	printf "%*s\n" $(((${#TEST} + $COLS) / 2)) "$TEST"
	printf "${BLUE}%*s\n\n" $(((${#SEP} + $COLS) / 2)) "$SEP"

	oldIFS=$IFS
	IFS=$'\n'

	for line in $(<$@)
	do
		execute_test $line
		sum=`expr $sum + 1`
	done

	OK=" ✔ $right/$sum"
	ERROR="  ✘ $false/$sum"
	RESULT=`echo -e "${BLUE}Result $TEST :  ${RESET}${GREEN}$OK${RESET}${RED}$ERROR${RESET}"`
	printf "\n%*s\n" $(((${#RESULT} + $COLS) / 2 + 27)) "$RESULT"
}

if [ -n "$1" ]; then
	for var in "$@"
	do
		FILE=$(find files -type f -name "$var.txt" -print)
		if [ -z "$FILE" ]; then
			printf "${RED}  ⚠️   File not found : $@${RESET}\n\n"
		else
			run_test $FILE
			total_sum=`expr $total_sum + $sum`
			total_right=`expr $total_right + $right`
			total_false=`expr $total_false + $false`
		fi
	done
else
	ALL_FILES=$(find files -type f -name "ex*.txt" -print)
	for FILE in $ALL_FILES
	do
		run_test $FILE
		total_sum=`expr $total_sum + $sum`
		total_right=`expr $total_right + $right`
		total_false=`expr $total_false + $false`
	done
fi

printf "\n${BLUE}%*s${RESET}\n\n" $(((${#END} + $COLS) / 2)) "$END"

OK=" ✔ $total_right/$total_sum"
ERROR="  ✘ $total_false/$total_sum"
RESULT=`echo -e "${BLUE}TOTAL :  ${RESET}${GREEN}$OK${RESET}${RED}$ERROR${RESET}"`
printf "%*s\n\n" $(((${#RESULT} + $COLS) / 2 + 28)) "$RESULT"
