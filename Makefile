cap3:
	@gcc -c funcAtivacao.c -o funcAtivacao.o -lm
	@gcc -c ./aux/extrair_dados.c -o extrair_dados.o
	@gcc -c ./capitulo3/perceptron_simples.c -o perceptron_simples.o
	@gcc -o cap3.exe  funcAtivacao.o extrair_dados.o perceptron_simples.o
	@./cap3.exe

clean:
	@rm *.o
	@rm *.exe
