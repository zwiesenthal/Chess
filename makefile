all:
	g++ -std=c++11 chess.cpp -o chess
	./chess

test:
	g++ test.cpp -o test
	./test
	
clean:
	rm chess
	rm test
	rm a.out
