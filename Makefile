main1:
	gcc -Wall -g -o main main.c celula.c forward_list.c matriz.c
main2:
	gcc -Wall -g -o main main2.c celula.c forward_list.c matriz.c
main3:
	gcc -Wall -g -o main main3.c celula.c forward_list.c matriz.c
run:
	./main
val:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./main
clean:
	rm -f main *.txt