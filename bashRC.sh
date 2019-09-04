#!/bin/bash
#$PS1="\u@\h \w> "
#$PS1="[\u@\h \w]\$"
#echo -en "$PS1"
source ~/.oh-my-git/prompt.sh
for d in dir1 dir2...
do cd "$d"
   pwd
   bash_prompt      # recalculate PS1 value
   echo -en "$PS1"
done
