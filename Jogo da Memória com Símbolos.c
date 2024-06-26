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
	char simbolos[NUM_SIMBOLOS] = {'!', '@', '#', '$', '%', ':', '&', '*', '(', ')', '-', '+', '*', '/', '<', '>', '§', 'ª', 'º', '?'};
	
	//gerar um símbolo aleatório entre 0 e 5
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
		  //quando é número, inicializa com 0
              vetor[i].numero = -1; 
          } else { 
		  //guarda numeros em posições ímpares
              vetor[i].simbolo = '\0'; 
		  // quando é símbolo, usa o caracter "nulo" pra falar que não tem símbolo
              vetor[i].numero = gerarNumeroAleatorio();
          }
	}
}


//essa função imprime o vetor de símbolos e números
void imprimirVetor(DadoAleatorio v[10]){
	int i = 0;
	for (i = 0; i < 10; i++) {
//usando os critérios da função "guardarSimbolosNumeros" para guardar de forma intercalada (!"\0" ou se é par)
      if (v[i].simbolo != '\0') {
          printf("%c ", v[i].simbolo)
      } else {
          printf("%d ", v[i].numero);
      }
    }
}

void imprimirProxPosVetor(int posUsuario, DadoAleatorio seqPerguntas[10]){
	for (int i = 0; i < 10; i++){
		if (i == posUsuario){
			if (i%2 != 0){
				printf(" %c ", seqPerguntas[i+1].numero);
			} else {
				printf(" %d ", seqPerguntas[i+1].simbolo);
			}
		}
	}
}

//essa função verifica se a sequência que o usuário escreveu como resposta é igual à sequência gerada
int verificarSequencia(DadoAleatorio sequencia[10]){
	int acertos = 0;
	int i = 0;
	DadoAleatorio resposta[10];

	for (i = 0; i < 10; i++){
		//a sequência tem símbolos na posição par e números na posição ímpar. 
		//logo, já que "resposta[10]" é uma estrutura com números e símbolos, 
		//é preciso verificar qual a posição para ler um dado char ou int.
		if (i%2 == 0){ 
			printf("%dº elemento: \n", i+1);
			//o scanf lê o caractere de nova linha ao invés de ler um caractere após um número, 
			//a partir da segunda vez do loop. Então, ao colocar um espaço antes de %c, 
			//instrui o scanf a ignorar qualquer espaço em branco antes de ler o caractere 
			scanf(" %c", &resposta[i].simbolo);
			resposta[i].numero = -1;
			//limpar o buffer para o próximo símbolo da sequência 
			getchar(); 
			//limpar o buffer para, se o usuário quiser jogar de novo, não ter nada da jogada anterior no buffer
			fflush(stdin);
		} else {
			printf("%dº elemento: \n", i+1);
			scanf("%d", &resposta[i].numero);
			resposta[i].simbolo = '\0';
			//limpar o buffer para, se o usuário quiser jogar de novo, não ter nada da jogada anterior no buffer
			fflush(stdin); 
		}
	}
		
	for (int i = 0; i < 10; i++){
		if (sequencia[i].simbolo != '\0'){
			if(sequencia[i].simbolo == resposta[i].simbolo){
				acertos++;
			}
		} else {
			if(sequencia[i].numero == resposta[i].numero){
				acertos++;
			}
		}
	}
	
	return acertos;
}

//essa função verifica se o usuário acertou toda a sequência ou não, e imprime o resultado
void scoreUser(int qntdAcertos, DadoAleatorio vet[10]){
	if (qntdAcertos == 10){
		printf("\t\t\tParábens!!! Você tem uma ótima memória! Verifique a sequência exibida:\n\n");
		imprimirVetor(vet);
	} else {
		printf("\t\t\tQue pena! Sua memória não é muito boa :( Verifique a sequência exibida:\n\n");
		imprimirVetor(vet);
	}
}
int main(){
	DadoAleatorio vetorDados[10];
	DadoAleatorio vetorRespostas[10];
	int i, j, k;
	int acertos = 0;
	int opcao = 0;
	char c;
	
	setlocale(LC_ALL, "Portuguese");
	
	do {
		system("cls");
		//iniciar a função rand()
		srand(time(NULL));
		printf("\t\t\t\t\tBem-Vindo ao Jogo da Memória!\t\t\t\t\t\n\n");
		printf("Serão gerados 5 símbolos (caracteres especiais do teclado) e 5 números (entre 0 e 10).\n");
		printf("Você deve memorizar a sequência de símbolos e números em 20 segundos e depois escrevê-la na ordem em que foi exibida.\n");
		printf("Pressione ENTER para iniciar. Boa sorte!\n");
    	
		do {
			//recebe o ENTER do usuário
			c = getch();
			//enquanto ele não digitar o ENTER, não se inicia o jogo. "c" está verificando se a tecla pressionada é o Enter (código 13 na tabela ASCII).
		} while (c != 13); 
		guardarSimbolosNumeros(vetorDados);
		//o usuário deve memorizar a sequência de símbolos e números em 20 segundos.
		j = 20; 
		k = 2;
		do {
			//limpar a tela do console a cada iteração do j.
			system("cls");
			if (j > 1){
				printf("Memorize a sequência abaixo em %d segundos\n\n", j);
			} else {
				printf("Memorize a sequência abaixo em %d segundo\n\n", j);
			}
    		
			j--; 
			//imprimirVetor(vetorDados);
			imprimirProxPosVetor(pos, )
			
			Sleep(1000);//essa função recebe um valor positivo que representa a quantidade de milissegundos que é necessário esperar;
		} while (j > 0);

		//limpar tela
		system("cls");
		printf("Informe a sequência de símbolos e números exibida: \n\n"); 
		acertos = verificarSequencia(vetorDados);
		scoreUser(acertos, vetorDados);  
		printf("\n\nGostaria de tentar novamente? Digite 1 para 'sim' ou 2 para não':");
		scanf("%d", &opcao);
		
	} while (opcao == 1);

	return 0;
}
