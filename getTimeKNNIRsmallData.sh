TEST="test"

## Tests are with: 100, 500, 1000, 5000, 10000 points
for ((E=1;E<=10;E++));
do	
	./getTimeKNNIR tests/small/$TEST$E 3 4 1
done

for ((E=1;E<=10;E++));
do	
	./getTimeKNNIR tests/small/$TEST$E 3 4 3
done

for ((E=1;E<=10;E++));
do	
	./getTimeKNNIR tests/small/$TEST$E 3 4 5
done
