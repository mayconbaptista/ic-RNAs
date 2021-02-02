cap3:
	@gcc -c funcAtivacao.c -o funcAtivacao.o
	@gcc -c ./aux/extrair_dados.c -o extrair_dados.o
	@gcc -c ./capitulo3/perceptron_simples.c -o perceptron_simples.o
	@gcc -o cap3.exe  funcAtivacao.o extrair_dados.o perceptron_simples.o
	@echo "use ./cap3.exe para executar"

cap4:
	@gcc -c funcAtivacao.c -o funcAtivacao.o 
	@gcc -c ./aux/extrair_dados.c -o extrair_dados.o
	@gcc -c ./capitulo4/perceptron_adaline.c -o perceptron_adaline.o 
	@gcc -o cap4.exe funcAtivacao.o extrair_dados.o perceptron_adaline.o -lm
	@echo "use ./cap4.exe para executar"

test:
	@gcc -c ./aux/extrair_dados.c -o extrair_dados.o
	@gcc -c ./aux/test.c -o test.o
	@gcc -o test.exe extrair_dados.o test.o

clean:
	@rm *.o
	@rm *.exe

