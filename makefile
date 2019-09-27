all:
	g++ chess.cpp -o chess
	./chess

test:
	g++ test.cpp -o test
	./test
	
clean:
	rm chess
	rm test
