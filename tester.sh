#!/bin/bash

RED="\033[38;5;203m"
ORANGE="\033[38;5;215m"
YELLOW="\033[38;5;229m"
GREEN="\033[38;5;121m"
LIGHT_BLUE="\033[38;5;123m"
BLUE="\033[1;38;5;33m"
RESET="\033[0m"


printf "Compilation :\n"
make

printf "\n${GREEN}..................... START TEST ......................${RESET}\n\n"

function execute_test
{
	echo -en "${BLUE}[TEST CASE]  $1 : ${RESET}"

	MY_RESULT=$(echo $@ "; exit/; | ./minishell 2>&-)
	MY_EXIT_STATUS=$(echo $?)

	REF_BASH=$(echo $@ "; exit" | bash --posix 2>&-)
	REF_EXIT_STATUS=$?

	if [ "$MY_EXIT_STATUS" == "$REF_EXIT_STATUS" ] && [ "$MY_EXIT_STATUS" == "$REF_EXIT_STATUS" ]
	then
	   	echo -e "\t✅  "
	else
	   	echo -e "\t❌ "
	fi
	if [ "$MY_RESULT" != "$REF_BASH" ]
	then
		printf "\n"
        echo -e "\t${ORANGE}Your result\t\t:\t$MY_RESULT${RESET}"
        echo -e "\t${YELLOW}Expected result\t\t:\t$REF_BASH${RESET}"
	fi
#	if [ "$MY_EXIT_STATUS" != "$REF_EXIT_STATUS" ]
#	then
		printf "\n"
        echo -e "\t${ORANGE}Your exit_status\t:\t$MY_EXIT_STATUS${RESET}"
        echo -e "\t${YELLOW}Expected exit_status\t:\t$REF_EXIT_STATUS${RESET}"
#    fi   		

	printf "\n\n"
}


execute_test 'pwd; ls -z'
execute_test 'ls||pwd'


printf "${GREEN}...................... END TEST ......................${RESET}\n\n"
