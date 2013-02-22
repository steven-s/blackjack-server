blackjack: main.o cardq.o card.o hand.o player.o shoe.o dealer.o fdio.o mysock.o
	gcc -Wall main.o cardq.o card.o hand.o player.o dealer.o fdio.o shoe.o mysock.o -o bjack
main.o: main.c
	gcc -Wall -c main.c
player.o: player.c
	gcc -Wall -c player.c
dealer.o: dealer.c
	gcc -Wall -c dealer.c
hand.o: hand.c
	gcc -Wall -c hand.c
card.o: card.c
	gcc -Wall -c card.c
cardq.o: cardq.c
	gcc -Wall -c cardq.c
shoe.o: shoe.c
	gcc -Wall -c shoe.c
fdio.o: fdio.c
	gcc -Wall -c fdio.c
mysock.o: mysock.c
	gcc -Wall -c mysock.c
clean:
	rm -f *.o bjack
