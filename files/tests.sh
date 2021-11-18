#                      ------  TESTS  ------

##########################  ECHO TESTS  #########################

echo test tout
echo test      tout
echo -n test tout
echo -n -n -n test tout
echo
echo echo
eCho
eChO
eCHO
ECHO
echo rhobebou
echo stop barking
echo "bonjour"
echo bonjour
echo 'bonjour'
echo -n bonjour
echo -nn bonjour
echo -n -n -n bonjour
echo -n -n -n bonjour
echo "-n" bonjour
echo -n"-n" bonjour
echo "-nnnn" bonjour
echo "-n -n -n"-n bonjour
echo "-n '-n'" bonjour
echo ~
echo "~"
echo '~'
echo ~123
echo 123~
echo ~/123
echo ~/123/456
echo $USER
echo "$USER"
echo "'$USER'"
echo " '$USER' "
echo text"$USER"
echo text"'$USER'" ' $USER '
echo "text"   "$USER"    "$USER"
echo '              $USER          '
echo               text "$USER"            "$USER"text
echo ''''''''''$USER''''''''''
echo """"""""$USER""""""""
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
echo $USER '' $USER $USER '' $USER '' $USER -n $USER
echo "$USER""$USER""$USER"
echo text"$USER"test
echo '$USER' "$USER" "text \' text"
echo '$USER'
echo $USER " "
echo "$USER""Users/$USER/file""'$USER'"'$USER'
echo "$USER$USER$USER"
echo '$USER'"$USER"'$USER'
echo '"$USER"''$USER'"""$USER"
echo " $USER  "'$PWD'
echo " $USER  \$ "'$PWD'
echo $USER=4
echo $USER=thallard
echo $USER
echo $?
echo $USER213
echo $USER$12USER$USER=4$USER12
echo $USER $123456789USER $USER123456789
echo $USER $9999USER $8888USER $7777USER
echo $USER $USER9999 $USER8888 $USER7777
echo $USER $USER9999 $USER8888 $USER7777 "$USER"
echo "$USER=12$USER"
echo "$9USER" "'$USER=12$SOMETHING'"
echo $PWD/file
echo "$PWD/file"
echo "text" "text$USER" ... "$USER"
echo $PWD


##########################  CD TESTS  #########################

cd .. ; pwd
cd /Users ; pwd
cd ; pwd
mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd
cd
cd ..
cd .
cd /Users
cd //
cd '//'
cd //////
cd ./././
cd /
cd '/////' 2>/dev/null
cd '/etc'
cd '/var'
cd "$PWD/file_tests"
cd "doesntexist"
cd "doesntexist" 2>/dev/null
cd ../../..
cd "wtf" 2>/dev/null
cd ..
cd ..
cd ?
cd +
cd _
cd woof
cd bark bark
cd '/'
cd $PWD/file_tests
cd $OLDPWD/something


##########################  PIPE TESTS  #########################

cat tests/lorem.txt | grep arcu | cat -e
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e
cat /dev/random | head -c 100 | wc -c
ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls
ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls
env | grep "_="
env | grep "SHLVL"
echo oui | cat -e
echo oui | echo non | echo something | grep oui
echo oui | echo non | echo something | grep non
echo oui | echo non | echo something | grep something
cd .. | echo "something"
cd .. | echo "something"
cd / | echo "something"
cd .. | pwd
ifconfig | grep ":"
ifconfig | grep nothing
whoami | grep $USER
whoami | grep $USER > tmp/file
whoami | cat -e | cat -e > tmp/file
cat Makefile | grep "FLAGS"
cat Makefile | cat -e | cat -e
cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e
export TEST=123 | cat -e | cat -e
unset TEST | cat -e
echo test | cat -e | cat -e | cat -e
whereis ls | cat -e | cat -e > test
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e
ls -la | grep "."
whereis grep > tmp/file
whereis grep > tmp/file
ls -la > tmp/file
ls -la > tmp/file
© 2021 GitHub, Inc.
Terms
Privacy
export a | echo lala ; export' 'grep -v _=
export | echo lala
unset PWD | echo lala ; export' 'grep -v _=
cd .. | echo lala ; export' 'grep -v _=
echo test | echo lala
pwd | echo lala
env | echo lala
cat bible.txt | grep testifieth
find / | grep cores
echo test | cat | cat | cat | cat | cat | grep test


#######################  ENV EXPANSIONS  #######################

echo $TEST
echo "$TEST"
"echo '$TEST'"
echo "$TEST$TEST$TEST"
echo "$TEST$TEST=lol$TEST"
echo "   $TEST lol $TEST"
echo $TEST$TEST$TEST
echo $TEST$TEST=lol$TEST""lol
echo    $TEST lol $TEST
echo test "" test "" test
echo "\$TEST"
echo "$=TEST"
echo "$"
echo "$?TEST"
echo $TEST $TEST
echo "$1TEST"
echo "$T1TEST"
export test=lala ; echo $test ; export $test=10 ; echo $lala
export test=lala ; export $test=a10 ; export $lala=test ; unset $lala ; export' 'grep -v _=
export a b c ; unset a c ; export' 'grep -v _=
export test=echo val=lala ; $test $lala ; export' 'grep -v _=
echo $TEST$TEST=lala
echo $TEST=lala$TEST
echo $TEST$TEST=lala$TEST
echo $TEST$TEST=$TEST=$TEST=$TEST=$TEST=$TEST
echo $1TEST
echo $10000TEST
echo $99TEST
echo $=TEST
echo $1 "" $9 "" $4 "" $7
echo $?TEST$?
echo "$PWD"
echo "$LALA"

#######################  EXPORT TESTS  #######################

ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
export =
export 1TEST= ; $ENV_SHOW
export TEST ; $EXPORT_SHOW
export ""="" ;  $ENV_SHOW
export TES=T="" ; $ENV_SHOW
export TE+S=T="" ; $ENV_SHOW
export TEST=LOL ; echo $TEST ; $ENV_SHOW
export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST
export TEST=LOL; export TEST+=LOL ; echo $TEST ; $ENV_SHOW
$ENV_SHOW
$EXPORT_SHOW
export TEST="ls       -l     - a" ; echo $TEST ; $LS ; $ENV_SHOW
env | grep "_="
export | grep "SHLVL"
export | grep "OLDPWD"
export | grep "PWD"
export $?
export TEST
export TEST=
export TEST=123
export ___TEST=123
export --TEST=123
export ""=""
export ''=''
export "="="="
export '='='='
export TE\\\ST=100
export TE-ST=100
export -TEST=100
export TEST-=100
export _TEST=100
export | grep "SHLVL"
export TEST
export ==========
export 1TEST=
export TEST
export ""=""
export TES=T=""
export TE+S=T=""
export TES\\\\T=123
export TES.T=123
export TES\\\$T=123
export TES\\\\T
export TES.T=123
export TES+T=123
export TES=T=123
export TES}T=123
export TES{T=123
export TES-T=123
export -TEST=123
export _TEST=123
export TES_T=123
export TEST_=123
export TE*ST=123
export TES#T=123
export TES@T=123
export TES!T=123
export TES$?T=123
export =============123
export +++++++=123
export ________=123
export export
export echo
export pwd
export cd
export export
export unset
export sudo
export TES^T=123
export TES!T=123
export TES\~T=123
export TEST+=100


#######################  UNSET TESTS  #######################

unset
export TEST=100
unset doesntexist
unset PWD
unset PWD
unset OLDPWD
unset PATH
unset PATH
unset PATH
unset TES\\\\T
unset TES;T
unset TES.T
unset TES+T
unset TES=T
unset TES}T
unset TES{T
unset TES-T
unset -TEST
unset _TEST
unset TES_T
unset TEST_
unset TE*ST
unset TES#T
unset TES@T
unset TES!T
unset TES$?T
unset ============
unset +++++++
unset ________
unset export
unset echo
unset pwd
unset cd
unset unset
unset sudo
unset TES^T
unset TES!T
unset TES\~T

#########################  REDIRECTIONS  #########################

echo test > ls ; cat ls
echo test > ls >> ls >> ls ; echo test >> ls; cat ls
> lol echo test lol; cat lol
>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test
cat < ls
cat < ls > ls
echo test > a ; cat < a
echo lala >a ; cat <a
echo test>a ; cat<a
echo lala> a ; cat< a
echo test >a ; cat <a
echo lala> a ; cat< a
echo test        >a ; cat<        a
echo lala            >     a ; cat        <       a
echo test > test_files/a ; cat < test_files/a
echo lala >test_files/a ; cat <test_files/a
echo test > b ; echo test add >> b ; cat < b
echo test > b ; rm b ; echo test add >> b ; cat < b
echo test > a ; echo test2 > b ; <a >b ; cat a b
echo test > a ; echo test2 > b ; >a >b <error; cat a b
echo test > a ; echo test2 > b ; rm a ; rm b ; >a >b <error; cat a b
echo test > a ; echo test2 > b ; >a <error b; cat a b
echo test > a ; echo test2 > b ; rm a ; rm b ; >a <error >b ; cat a b
cat <error
echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b
echo test > test_files/a ; echo test2 > test_files/b ; rm test_files/a ; rm test_files/b ; >test_files/a >test_files/b <error; cat test_files/a test_files/b
echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >test_files/b; cat test_files/a test_files/b
echo test > test_files/a ; echo test2 > test_files/b ; rm test_files/a ; rm test_files/b ; >test_files/a <error >test_files/b ; cat test_files/a test_files/b
cat <test_files/error
echo test > ../a ; echo test2 > ../b ; >../a >../b <error ; cat ../a ../b
echo test > ../a ; echo test2 > ../b ; rm ../a ; rm ../b ; >../a >../b <error; cat ../a ../b
echo test > ../a ; echo test2 > ../b ; >../a <error >../b ; cat ../a ../b
echo test > ../a ; echo test2 > ../b ; rm ../a ; rm ../b ; >../a <error >../b ; cat ../a ../b
cat <../error
<error
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a >>test_files/b <error; cat test_files/a test_files/b
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >>test_files/a >test_files/b <error; cat test_files/a test_files/b
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >>test_files/a >>test_files/b <error; cat test_files/a test_files/b
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >>test_files/b ; cat test_files/a test_files/b
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; >test_files/a <error >>test_files/b ; cat test_files/a test_files/b
run_test 'echo test > test_files/a ; echo test2 > test_files/b ; <error >>test_files/a >>test_files/b ; cat test_files/a test_files/b
delete_file "test_files/a test_files/b"
echo test > test_files/a ; echo lala > test_files/b ; >test_files/a >>test_files/b <error; cat test_files/a test_files/b
delete_file "test_files/a test_files/b"
echo test > test_files/a ; echo lala > test_files/b ; >>test_files/a >>test_files/b <error; cat test_files/a test_files/b
delete_file "test_files/a test_files/b"
>test_files/a <error >>test_files/b ; cat test_files/a test_files/b
delete_file "test_files/a test_files/b"
>test_files/a <error >>test_files/b ; cat test_files/a test_files/b
delete_file "test_files/a test_files/b"
<error >>test_files/a >>test_files/b ; cat test_files/a test_files/b
echo lala > a >> a >> a ; echo test >> a ; cat < a
echo lala > a >> a >> a ; echo test >> a ; echo lala > a >> a >> a ; cat < a
echo lala >> a >> a > a ; echo test >> a ; cat < a
echo lala >> a >> a > a ; echo test >> a ; echo lala >> a >> a > a ; cat < a
echo test > a ; echo lala >> a >> a >> a ; echo test >> a ; cat < a
echo test > a ; echo lala >> a >> a >> a ; echo test >> a ; echo lala >> a >> a >> a ; cat < a
echo test > a ; echo lala > b ; rm b ; >>a >>b <error; cat a b
echo test > a ; echo lala > b ; rm b ; >>a <error >> b ; cat a b
echo test > a ; echo lala > b ; rm a ; rm b ; >>a >>b <error; cat a b
echo test > a ; echo lala > b ; rm a ; rm b ; >>a <error >> b ; cat a b
echo <a <b
echo <b <a
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a > b > a ; cat a b
echo test > a ; echo test > b ; echo lala > a > b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a >> b > a ; cat a b
echo test > a ; echo test > b ; echo lala > a >> b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a > b >> a ; cat a b
echo test > a ; echo test > b ; echo lala > a > b >> a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala >> a > b > a ; cat a b
echo test > a ; echo test > b ; echo lala >> a > b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala >> a >> b >> a ; cat a b
echo test > a ; echo test > b ; echo lala >> a >> b >> a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a > b > a ; cat a b
echo test > a ; echo test > b ; echo lala > a > b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a >> b > a ; cat a b
echo test > a ; echo test > b ; echo lala > a >> b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala > a > b >> a ; cat a b
echo test > a ; echo test > b ; echo lala > a > b >> a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala >> a > b > a ; cat a b
echo test > a ; echo test > b ; echo lala >> a > b > a ; cat a b
echo lala > a ; rm a ; echo lala > b ; rm b ; echo lala >> a >> b >> a ; cat a b
echo test > a ; echo test > b ; echo lala >> a >> b >> a ; cat a b


#########################  MULTI $?  #########################

export a ; echo $?
export % ; echo $?
echo "test" > a && run_test 'cat a ; echo $?' && rm a
cat a ; echo $?
pwd ; echo $?
export a | echo $?
echo lala ; echo $?
echo lala | echo $?
pwd ; echo $?
pwd | echo $?
cd / ; echo $?
 cd / | echo $?
cd ~/ ; echo $?
 cd ~/ | echo $?
cd /error ; echo $?
cd ~/error ; echo $?
export a ; unset a ; echo $?
export a | unset a | echo $?
unset a ; echo $?
unset a | echo $?
echo $? ; echo $? ; echo $?
echo $? | echo $? | echo $?
cd error ; echo $?
cd error error ; echo $?
./error ; echo $?
<error ; echo $?
cat <error ; echo $?
cat < ; echo $?
echo test > ; echo $?
echo test >> ; echo $?

#########################  MULTI TESTS  #########################

echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem


#########################  SYNTAX ERROR #########################

;; test
| test
echo > <
echo | |
<
test
| test
echo > <
echo | |
<
|
| | |
hello world
||||||||

cat wouaf wouaf
>
>>>>>>>>
<<<<<<<<<
> > > >
>> >> >> >>
~
<<
/Users

.
..
/
\\\
EechoE
.echo.
>echo>
<echo<
>>echo>>
echo
|echo|
echo -n
echo -n
echo
echo something
rm -f something
cat something
| echo -n oui
echo -n oui
trying to destroy your minishell
trying something again echo if you see this message thats not a good new
qewew
wtf
hi im thallard
nice to meet you if these tests are green
your minishell is perfect

###########################  EXIT  ###########################

exit 42
exit 42 53 68
exit 259
exit 9223372036854775807
exit -9223372036854775808
exit 9223372036854775808
exit -9223372036854775810
exit -4
exit wrong
exit wrong_command
exit 0 0
exit 42 42
exit -42 -24
exit 42
exit 42 53 68
exit 259
exit -12030
exit --1239312
exit ++++1203020103
exit +0
exit ++++++0
exit -----0
exit azerty
exit kewkwqke
exit a
exit z
exit "1"
exit "2"
exit "+102"
exit "1230"
exit "+++1230"
exit "1"23
exit "2"32"32"
exit "'42'"
exit '42'"42"42
exit +'42'"42"42
exit -'42'"42"42
exit 9223372036854775807
exit 9223372036854775808
exit -4
exit wrong
exit wrong_command
exit something
exit 1
exit -1
exit 42
exit 0
exit --000
exit +++++++000
exit ++++3193912939
exit ---31232103012
exit "something"
exit q
exit help
exit export
exit echo
exit cd ..
exit 0 0
exit something somethingv2
exit 42 42 42 42 42
exit echo something
exit exit

##########################  CMD ERROR  ##########################

gdagadgag
ls -Z
cd gdhahahad
ls -la | wtf


##########################  CMD BONUS  ##########################

ls *
ls *.*
ls .*
cat M*le
cat M*ee
cat Make*file
cp [A-Z]* dir2
cd files && cat ex*.txt
(cd ../.. && pwd) ; pwd
ls -z || (cd ../../..&&pwd)


# PROBLEMES AVEC TESTER :

cat /dev/random | head -c 100 | wc -c
find / | grep cores
echo "\s" ; echo "\\s"
echo "12\""
echo "bip | bip ; coyotte > < \" "
echo \>
echo $USER$var\$USER$USER\$USERtest$USER
echo bonjour \; ls
export var=te"st ; echo $var
cat < ; echo $?
echo test > ; echo $?
echo test >> ; echo $?
| echo bonjour; |
echo bonjour > > out
echo bonjour > $test
echo bonjour >>> test
echo bonjour | |
echo bonjour |;
