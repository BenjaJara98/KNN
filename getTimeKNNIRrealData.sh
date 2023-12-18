TEST="test"

## Tests are with: 100, 500, 1000, 5000, 10000 points
for ((E=1;E<=6;E++));
do	
	./getTimeKNNIR tests/real/$TEST$E 25 40 10
done

for ((E=1;E<=6;E++));
do	
	./getTimeKNNIR tests/real/$TEST$E 25 40 30
done

for ((E=1;E<=6;E++));
do	
	./getTimeKNNIR tests/real/$TEST$E 25 40 30
done

for ((E=1;E<=6;E++));
do	
	./getTimeKNNIR tests/real/$TEST$E 25 40 50
done
