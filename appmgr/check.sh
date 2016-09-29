#!/bin/sh
#cat bcm.need.txt | while read line
cat zte.need.txt | while read line
   do
   #num=`grep $line bcm.has.txt -ric`
   num=`grep $line zte.has.txt -ric`
   if [ "$num" -eq 0 ]; then
      #echo $line  $num
      grep $line appmgr.sh -rin
   fi
   done
