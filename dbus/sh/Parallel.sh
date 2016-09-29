#/bin/sh
if test "$1" = ""; then
exit;
fi
./$1 -nc -instance
sleep 3
./$1 -nc -parallel_no_redundancy 1 &
sleep 3
./$1 -nc -parallel_no_redundancy 2 &
sleep 3
./$1 -nc -parallel_no_redundancy 3 &
sleep 3
./$1 -nc -parallel_no_redundancy 4 &
sleep 3
./$1 -nc -parallel_no_redundancy 5 &
