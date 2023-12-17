TEST="test_"

## Tests are with: 100, 500, 1000, 5000, 10000 points
for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 10
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 20
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 30
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 50
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 100
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 200
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 500
done

for ((E=1;E<=5;E++));
do	
	./getTimeKNNPQ tests/sintetic/$TEST$E 750 1250 1000
done
