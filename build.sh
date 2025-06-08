#!/bin/bash

# Author : Tosin Daudu
# todo backup all c files
# add in sys info project name / build version / mode

red=$(tput setaf 1)
bold=$(tput bold)
reset=$(tput sgr0)
green=$(tput setaf 2)
blue=$(tput setaf 6)


info1=$(date)
info2=$(pwd)
info3=$(uname -n)
echo "${bold}${blue}System Info [$info1] { $info3, $info2 }${reset}"
echo "${bold}${blue}[ Building Project with GNC Compiler ]${reset}"


# Get all .c and .h files in the current directory
source_files=$(ls *.c 2>/dev/null)

# Check if there are any source files
if [ -z "$source_files" ]; then
    echo "No .c or .h files found in the current directory."
    exit 1
fi

gcc $source_files -o exec -Wall -Wpedantic -Wextra -Werror -Wshadow -Wformat=2 -Wconversion -Wunused-parameter -lm
exitcode=$?
backupBool=true

echo "${bold}${blue}[ Script Compilation Finished ]${reset}"

if [ "$1" = 'no-run' ]; then
    echo "${bold}${blue}[ Done ]${reset}"
    if [ "$exitcode" = 0 ]; then
        echo "${bold}${green}[ Compiled Successfully ]${reset}"
    else
        echo "${bold}${red}[ Build Failed ]${reset}"
        echo $'\a'
    fi
    exit
elif [ "$1" = 'no-backup' ]; then
    backupBool=false
fi

if [ -d backupsrc ]; then # build history temp storage to revert files
    echo "${bold}${blue}[ Backing up files ] ${reset}"
    cp main.c backupsrc/"main-$(date '+%Y-%m-%d').c.save";
else
    mkdir backupsrc
    echo "${bold}${blue}[ Backing up files ] ${reset}"
    cp main.c backupsrc/"main-$(date '+%Y-%m-%d').c.save";
fi

echo $"${bold}${blue}[ Runnning Target Executable ]${reset}"
echo ""

if [ "$exitcode" = 0 ]; then
    time valgrind --leak-check=yes --read-var-info=yes ./exec
    exitcode=$?
    if [ "$exitcode" = 0 ]; then 
        echo "${bold}${green}[ Build ran Successfully ]${reset}"
    else
        echo "${bold}${red}[ Program Runtime Error ]${reset}"
        echo $'\a'
    fi
else
    echo "${bold}${red}[ Compilation Failed ]${reset}"
    echo $'\a' # Alert Sound
fi


# fix sudo issue

    #learn grep/nano
    #uptime + time

    # =>PS1="[\u@\h \w]\$"
    # [root@ip-72-167-112-17 /var/www/tutorialspoint/unix]$
    # [root@ip-72-167-112-17 /var/www/tutorialspoint/unix]$

    # 1	
    # \t

    # Current time, expressed as HH:MM:SS

    # 2	
    # \d

    # Current date, expressed as Weekday Month Date


    # 4	
    # \s

    # Current shell environment

    # 5	
    # \W

    # Working directory

    # 6	
    # \w

    # Full path of the working directory

    # 7	
    # \u

    # Current user’s username

    # 8	
    # \h

    # Hostname of the current machine




    # You can't use + for string concatenation.
    # for i in `seq 1 50`; do echo -e "\e[1;${i}m This is colored text \e[0m${i}"; done

    # dpkg-reconfigure tzdata



    # https://www.tutorialspoint.com/unix/unix-pipes-filters.htm
    # https://www.tutorialspoint.com/unix/unix-special-variables.htm
    # https://www.tutorialspoint.com/unix/unix-decision-making.htm
    # https://www.tutorialspoint.com/unix/unix-shell-functions.htm
