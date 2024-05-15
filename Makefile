tabuleiro: main.c
	gcc -o tabuleirogame perguntas.c perguntas.h ranking.c ranking.h tabuleiro.c tabuleiro.c main.c

clean:
	rm -f tabuleirogame

