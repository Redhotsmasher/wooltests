#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
gray=`tput setaf 7`
magenta=`tput setaf 5`
reset=`tput sgr0`
tests=(simple1 simple2 simple3 simple4 simple5 array recursion fibonacci)
#tests=(recursion)
modes=("SC-Source" "SC-Optimal" "TSO-Source")
modeparams=("--sc --source" "--sc --optimal" "--tso --source")
length=0
numreps=$1
numwoolthreads=$2
timeoutval=$3

if [ $# -gt 0 ]
then
    if [ $1 = "--help" -o $1 = "-help" -o $1 = "-h" -o $1 = "-?" -o $1 = "--usage" -o $# -gt 3 ]
    then
        printf "\nUsage:\n"
        printf "\t./runtests.sh <number of runs per test> <number of wool threads> [timeout] \n"
        printf "or\n"
        printf "\t./runtests.sh\n"
        printf "for interactive mode.\n\n"
        exit 0
    fi
else
    while ! (($numreps)) 2>/dev/null || [ $numreps -lt 0 ] ; do
        read -p "Enter number of runs of each test: " numreps
    done

    while ! (($numwoolthreads)) 2>/dev/null || [ $numwoolthreads -lt 0 ] ; do
        read -p "Enter number of wool threads: " numwoolthreads
    done
fi

if [ $# -lt 3 ]
then
    timeoutval="1h"
fi

for string in ${tests[@]} ; do
    if [ ${#string} -gt ${length} ]
    then
        length=${#string}
    fi
done

fail="${red}  FAIL  ${reset}"
pass="${green}  PASS  ${reset}"
timeout="${yellow}TIME OUT${reset}"
skipped="${gray}  SKIP  ${reset}"
error="${magenta} ERROR? ${reset}"

iterper=$(( 3 * $numreps ))
iterx=0
for test in ${tests[@]} ; do
    for i in {0..2} ; do
        itery=$i
        printiter=1
        while [ $itery -lt $iterper ] ; do
            #filename="${test}_${modes[$i]}_${printiter}"
            #echo $filename
            printf "Running test %s in mode %10s (%2d/%2d)..." $test "${modes[$i]}" $printiter $numreps
            timeout $timeoutval taskset -c 0-3 /usr/bin/time nidhugg ${modeparams[$i]} --extfun-no-race=fprintf --extfun-no-race=printf --extfun-no-race=gettimeofday --extfun-no-race=getopt --print-progress-estimate ${test}_u.ll -- -p $numwoolthreads > ./"${test}_${modes[$i]}_${itery}".log 2>&1
            result[$iterx * $iterper + $itery]=$?
            #printf "DEBUG: %d\n" ${result[$iterx * $iterper + $itery]}
            case ${result[$iterx * $iterper + $itery]} in
                0)
                    printf " ${pass}\n"
                    ;;
                42)
                    printf " ${fail}\n"
                    ;;
                124)
                    printf " ${timeout}, skipping...\n"
                    itery=$(( $itery + 3 ))
                    while [ $itery -lt $iterper ] ; do
                        result[$iterx * $iterper + $itery]=9
                        itery=$(( $itery + 3 ))
                    done
                    continue
                    ;;
                *)
                    printf " ${error}\n"
                    ;;
            esac
            printiter=$(( $printiter + 1 ))
            itery=$(( $itery + 3 ))
        done
    done
    iterx=$(( $iterx + 1 ))
done

printf "\nSummary:\n\n"
printf "╔"
for ((i=1;i<=length;++i)); do
    printf "═"
done
printf "╤════════╤════════╤════════╗\n"
printf "║%${length}s│Source  │Optimal │TSO     ║\n" ""

total=$(( $iterper * ${#tests[@]} ))
iter=0
for test in ${tests[@]} ; do
    printf "╟"
    for ((i=1;i<=length;++i)); do
        printf "─"
    done
    printf "┼────────┼────────┼────────╢\n"
    for ((i=1;i<=numreps;++i)); do
        printf "║%${length}s" $test
        for n in {0..2} ; do
            #printf "DEBUG: %d\n" ${result[$iter]}
            case ${result[$iter]} in
                0)
                    printf "│${pass}"
                    ;;
                42)
                    printf "│${fail}"
                    ;;
                124)
                    printf "│${timeout}"
                    ;;
                9)
                    printf "│${skipped}"
                    ;;
                *)
                    printf "│${error}"
                    ;;
            esac
            iter=$(( $iter + 1 ))
        done
        printf "║\n"
    done
done

printf "╚"
for ((i=1;i<=length;++i)); do
    printf "═"
done

printf "╧════════╧════════╧════════╝\n"
