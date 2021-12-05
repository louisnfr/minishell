#!/bin/bash

#########################      COLORS CODE     ##########################

EXPAND_BG="\033[K"
RED="\033[38;5;203m"
RED_B="\033[40;1;38;2;255;65;65m"
RED_E="\033[48;5;203;1;38;5;16m"
ORANGE="\033[38;5;215m"
YELLOW="\033[38;5;229m"
GREEN="\033[38;5;121m"
GREEN_B="\033[40;1;38;5;83m"
LIGHT_BLUE="\033[38;5;123m"
BLUE="\033[1;38;5;33m"
BLUE_B="\033[40;1;38;5;33m"
WHITE_B="\033[40;1;37m"
RESET="\033[0m"


#########################     INITIALISATION    ##########################

make
sum=0
right=0
false=0
total_sum=0
total_right=0
total_false=0
ERRORS_FILE="files/errors.txt"
touch "$ERRORS_FILE"
COLS=$(tput cols)
TITLE=".............................  START TEST  ............................"
END="..............................  END TEST  ............................."
COLS=$(tput cols)
printf "\n${BLUE}%*s${RESET}\n" $(((${#TITLE} + $COLS) / 2)) "$TITLE"


###########################   TEST FUNCTION   ###########################

function execute_test()
{
	SEP="..................................................................................."

	# MY_RESULT=$(echo $@ "; exit" | ./minishell 2>/dev/null | sed '/^minishell>/d')
	MY_RESULT=$(./minishell 2>/dev/null << END_HEREDOC
$@
exit
END_HEREDOC
)
	MY_RESULT=$(sed '/^minishell>/d' <<< "$MY_RESULT")
	MY_EXIT_STATUS=$?

	# REF_BASH=$(echo $@ "; exit" | bash --posix 2>/dev/null | sed '/^minishell>/d')
 	REF_BASH=$(bash --posix 2>/dev/null << END_HEREDOC
$@
exit
END_HEREDOC
)
	REF_BASH=$(sed '/^minishell>/d'<<< "$REF_BASH")
	REF_EXIT_STATUS=$?

	if [ "$MY_RESULT" == "$REF_BASH" ] && [ "$MY_EXIT_STATUS" == "$REF_EXIT_STATUS" ]
	then
	   	echo -e "${GREEN}   ✔  $1${RESET}"
		right=`expr $right + 1`
	else
		echo -e "${RED}   ✘  $1${RESET}"
		false=`expr $false + 1`

		echo -e "${RED_E} ➞ $1 : ${RESET}" >> "$ERRORS_FILE"
		if [ "$MY_RESULT" != "$REF_BASH" ]
		then
	        echo -e "     ${RED}Your result${RESET}\t   :   $MY_RESULT" >> "$ERRORS_FILE"
	        echo -e "     ${ORANGE}Expected result${RESET}\t   :   $REF_BASH" >> "$ERRORS_FILE"
		fi
		if [ "$MY_EXIT_STATUS" != "$REF_EXIT_STATUS" ]
		then
	        echo -e "     ${RED}Your exit_status${RESET}\t   :  $MY_EXIT_STATUS" >> "$ERRORS_FILE"
	        echo -e "     ${ORANGE}Expected exit_status${RESET}  :  $REF_EXIT_STATUS" >> "$ERRORS_FILE"
		fi
		echo "" >> "$ERRORS_FILE"
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


#############################       MAIN      ############################

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
	ALL_FILES=$(find files -type f -name "*.txt" -print)
	for FILE in $ALL_FILES
	do
		run_test $FILE
		total_sum=`expr $total_sum + $sum`
		total_right=`expr $total_right + $right`
		total_false=`expr $total_false + $false`
	done
fi

printf "\n${BLUE}%*s${RESET}\n\n" $(((${#END} + $COLS) / 2)) "$END"

PRINT_ERRORS=`echo -e "${RED}❌  SUMMARY ERRORS ❌${RESET}"`
NO_ERROR="----- No errors -----"
printf "\n%*s\n\n" $(((${#PRINT_ERRORS} + $COLS) / 2 + 10)) "$PRINT_ERRORS"
if [ -s "$ERRORS_FILE" ]; then
	cat "$ERRORS_FILE"
else
	printf "\n%*s\n\n" $(((${#NO_ERROR} + $COLS) / 2)) "$NO_ERROR"
fi
rm "$ERRORS_FILE"

OK="$total_right"
ERROR="$total_false"
#RESULT=`echo -e "${WHITE_B}   TOTAL :  ${RESET}${GREEN_B}$OK ${RESET}${RED_B}$ERROR   ${RESET}"`
RESULT=`echo -e "${GREEN_B}  $OK passed,${RESET}${RED_B}  $ERROR failed,${RESET}${WHITE_B}  $total_sum total  ${RESET}"`
printf "\n%*s\n\n" $(((${#RESULT} + $COLS) / 2 + 29)) "$RESULT"
