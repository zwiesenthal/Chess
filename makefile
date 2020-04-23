all:
	g++ -std=c++11 chess.cpp -o chess
	./chess

test:
	g++ -std=c++11 test.cpp -o test
	./test

chm:
	chmod 0777 chess.cpp
	chmod 0777 test.cpp
	
clean:
	rm chess
	rm test
