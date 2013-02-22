blackjackd: main.o cardq.o card.o hand.o player.o shoe.o dealer.o fdio.o mysock.o
	gcc -Wall main.o cardq.o card.o hand.o player.o dealer.o fdio.o shoe.o mysock.o -o blackjackd
main.o: main.c
	gcc -Wall -c main.c
player.o: player.c player.h
	gcc -Wall -c player.c
dealer.o: dealer.c dealer.h
	gcc -Wall -c dealer.c
hand.o: hand.c hand.h
	gcc -Wall -c hand.c
card.o: card.c card.h
	gcc -Wall -c card.c
cardq.o: cardq.c cardq.h
	gcc -Wall -c cardq.c
shoe.o: shoe.c shoe.h
	gcc -Wall -c shoe.c
fdio.o: fdio.c fdio.h
	gcc -Wall -c fdio.c
mysock.o: mysock.c mysock.h
	gcc -Wall -c mysock.c
clean:
	rm -f *.o blackjackd
