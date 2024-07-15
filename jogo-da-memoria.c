#include <stdio.h> //biblioteca padrão
#include <stdlib.h> //biblioteca padrão
#include <locale.h> // configura o programa para a linguagem do sistema
#include <conio.h> //para iniciar o jogo a partir do "enter" do usuário
#include <windows.h> // para usar system("cls") e a função sleep()
#include <time.h> // para usar srand
 
#define NUM_SIMBOLOS 20 //define a quantidade de caracteres que serão usados como "bibilioteca" para gerar caracteres especiais (símbolos) aleatórios
 
//essa estrutura armazena um símbolo e um número aleatório

typedef struct {
	char simbolo;
	int numero;
} DadoAleatorio;
 
//essa função serve para gerar 5 caracteres aleatórios de 20 e retornar para o programa principal
char gerarSimboloAleatorio(){
	int i;
	//vou criar a "biblioteca" de símbolos.
	char simbolos[NUM_SIMBOLOS] = {'!', '@', '#', '$', '%', ':', '&', '*', '(', ')', '-', '+', '=', '/', '<', '>', '|', '[', 'º', '?'};

	//gerar um símbolo aleatório
	i = rand()%19; 

	return simbolos[i];
}
 
int gerarNumeroAleatorio() {
	return rand()%10;  //gera um número aleatório entre 0 e 10
}
 
//essa função serve para guardar os símbolos e numeros gerados em "gerarSimboloAleatorio" e "gerarNumeroAleatorio" em um vetor do tipo DadoAleatorio
void guardarSimbolosNumeros(DadoAleatorio vetor[10]){
	int i;

	//guardar de forma intercalada
	for (i = 0; i < 10; i++) {
		  if (i % 2 == 0) {  
		  //guarda simbolos em posições pares
			vetor[i].simbolo = gerarSimboloAleatorio();
		  //quando é número, inicializa com -1
			vetor[i].numero = -1; 
		  } else { 
		  //guarda numeros em posições ímpares
			vetor[i].simbolo = '\0'; 
		  // quando é símbolo, usa o caracter "nulo" pra falar que não tem símbolo
			vetor[i].numero = gerarNumeroAleatorio();
		  }
	}
}
 
//essa função imprime o vetor de símbolos e números (até max - se foi até o final da sequência de 10, o jogo acaba).
//enquanto está na sequência, sem erros, o max é a posição da sequência que o user está agora e que vai pro próximo
//enquanto está na sequência, com erros, o max é a posição da sequência que o user conseguiu ir e o jogo acaba.
void imprimirVetor(DadoAleatorio v[10], int max){
	for (int i = 0; i < max; i++) {
	//usando os critérios da função "guardarSimbolosNumeros" para guardar de forma intercalada (!"\0" ou se é par)
	  if (v[i].simbolo != '\0') {
		  printf("%c ", v[i].simbolo);
	  } else {
		  printf("%d ", v[i].numero);
	  }
	}
}
 
//essa função verifica se o elemento do round que o usuário está e escreveu como resposta é o elemento do sequência gerada referente àquele round
int verificarSequencia(DadoAleatorio sequencia[10], DadoAleatorio resposta[10], int round){
	int acertos = 0;
	//usando o critério que verifica se naquela posição no tipo símbolo tem '\0' ou não.
	//de acordo com isso -> se tem, é número. se não, é símbolo.
	for (int i = 0; i < round; i++){
		if (sequencia[i].simbolo != '\0'){
			if (sequencia[i].simbolo == resposta[i].simbolo){
				acertos++;
			}
		} else {
			if (sequencia[i].numero == resposta[i].numero){
				acertos++;
			}
		}
	}
	return acertos;
}
 
//essa função verifica se o usuário acertou toda a sequência ou não, e imprime o resultado
//retorna 0 se o jogo deve continuar, 1 caso contrário
int scoreUser(int qntdAcertos, int round, DadoAleatorio vet[10]){
	if (qntdAcertos == 10){
		printf("\t\t\tParábens!!! Você tem uma ótima memória! Verifique a sequência gerada:\n\n");
		imprimirVetor(vet, 10);
		return 1;
	} else if (qntdAcertos == round){
		printf("\t\t\tExcelente, você passou deste round. Verifique a sequência até o momento:\n\n");
		imprimirVetor(vet, round);
		return 0;
	} else {
		printf("\t\t\tQue pena! Sua memória não é muito boa :( Verifique a sequência gerada:\n\n");
		imprimirVetor(vet, 10);
		return 1;
	}
}
 
int main(){
	DadoAleatorio vetorDados[10];
	DadoAleatorio vetorRespostas[10];
	int round, timer, fimDoJogo;
	int acertos = 0;
	int opcao = 0;
	char c;
	setlocale(LC_ALL, "");

	do {
		system("cls");
		//iniciar a função rand()
		srand(time(NULL));
		printf("\t\t\t\t\tBem-Vindo ao Jogo da Memória!\t\t\t\t\t\n\n");
		printf("Serão gerados 5 símbolos (caracteres especiais do teclado) e 5 números (entre 0 e 10).\n");
		printf("Você deve memorizar a sequência de símbolos e números gradualmente.\n");
		printf("Primeiro será mostrado o primeiro elemento, você terá que lembrá-lo, depois o segundo, e você terá que digitar os dois primeiros, etc...\n");
		printf("Pressione ENTER para iniciar. Boa sorte!\n");

		do {
			//recebe o ENTER do usuário
			c = getch();
			//enquanto ele não digitar o ENTER, não se inicia o jogo. "c" está verificando se a tecla pressionada é o Enter (código 13 na tabela ASCII).
		} while (c != 13);

		//o jogo começa aqui
		guardarSimbolosNumeros(vetorDados);
		round = 1, fimDoJogo = 0;

		while (round <= 10 && !fimDoJogo){
			timer = 2; 
			while (timer > 0){
				system("cls");
				if (timer > 1){
					printf("Memorize o %dº elemento abaixo em %d segundos\n\n", round, timer);
				} else {
					printf("Memorize o %dº elemento abaixo em %d segundo\n\n", round, timer);
				}
				//usando o critério de par ou ímpar para símbolo ou número
				if ((round-1)%2 == 0){ 
					printf("%c", vetorDados[round-1].simbolo);
				} else {
					printf("%d", vetorDados[round-1].numero);
				}
				timer--;
				Sleep(1000);
			}
 
			system("cls");
			printf("Informe a sequência dada até o momento:\n> ");
			fflush(stdin);

			for (int i = 0; i < round; i++){
				//usando o critério de par ou ímpar para símbolo ou número
				if (i%2 == 0){ 
					scanf("%c", &vetorRespostas[i].simbolo);
					printf("Lido: %c\n", vetorRespostas[i].simbolo);
				} else { 
					scanf("%d", &vetorRespostas[i].numero);
					printf("Lido: %d\n", vetorRespostas[i].numero);
					getchar();
				}
			}
	
			acertos = verificarSequencia(vetorDados, vetorRespostas, round);
			fimDoJogo = scoreUser(acertos, round, vetorDados);
			timer = 4; 

			while (timer > 0){
				timer--;
				Sleep(700); 
			}
			round++;
		}

		fflush(stdin);
		// fim do jogo
		printf("\n\nGostaria de tentar novamente? Digite 1 para 'sim' ou 2 para não':");
		scanf("%d", &opcao);
	} while (opcao == 1);
 
	return 0;

}
