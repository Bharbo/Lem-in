#/bin/sh

echo "So it begins" > log.txt
for filename in $(find $1); do
	echo "\n\n\n=======\n" $filename >> log.txt
	cat $filename | valgrind ./lem-in > /dev/null 2>> log.txt
done
cat log.txt | grep "definitely lost"
