ngen : y.tab.o lex.yy.o funcoes.o estruturas.h
	gcc -o ngen lex.yy.o y.tab.o funcoes.o -lfl
	./ngen genealogia.txt
	google-chrome Index.html
	
lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.o : y.tab.c y.tab.h estruturas.h funcoes.o
	gcc -c y.tab.c funcoes.c
		
y.tab.c y.tab.h : ngen.y estruturas.h funcoes.o
	yacc -d ngen.y
	
funcoes.o : estruturas.h funcoes.c
	gcc -c funcoes.c

lex.yy.c : ngen.l estruturas.h
	flex ngen.l
	
clean:
	rm lex.yy.c
	rm lex.yy.o
	rm y.tab.h
	rm y.tab.c
	rm *.o
	rm *.html
	rm ngen

install: y.tab.o lex.yy.o funcoes.o estruturas.h
	gcc -o ngen lex.yy.o y.tab.o funcoes.o -lfl
	cp ngen /usr/local/bin
	mkdir -m=rwx -p /usr/local/share/ngen
	cp styles.css /usr/local/share/ngen
	cp paper005.gif /usr/local/share/ngen
	
	

