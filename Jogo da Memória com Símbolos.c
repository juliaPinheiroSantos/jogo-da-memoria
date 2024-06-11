#include <stdio.h> //biblioteca padr�o
#include <stdlib.h> //biblioteca padr�o
#include <locale.h> // configura o programa para a linguagem do sistema
#include <conio.h> //para iniciar o jogo a partir do "enter" do usu�rio
#include <windows.h> // para usar system("cls") e a fun��o sleep()
#include <time.h> // para usar srand

#define NUM_SIMBOLOS 20 //define a quantidade de caracteres que ser�o usados como "bibilioteca" para gerar caracteres especiais (s�mbolos) aleat�rios 

//essa estrutura armazena um s�mbolo e um n�mero aleat�rio
typedef struct {
    char simbolo;
    int numero;
} DadoAleatorio;

//essa fun��o serve para gerar 5 caracteres aleat�rios de 10 e retornar para o programa principal
char gerarSimboloAleatorio(){
	int i;
	//vou criar a "biblioteca" de s�mbolos.
	char simbolos[NUM_SIMBOLOS] = {'!', '@', '#', '$', '%', ':', '&', '*', '(', ')', '-', '+', '*', '/', '<', '>', '�', '�', '�', '?'};
	
	//gerar um s�mbolo aleat�rio entre 0 e 5
	i = rand()%6; //6 porque o rand vai de 0 a 5, n�o de 1 a 5.
	
	return simbolos[i];
}

int gerarNumeroAleatorio() {
    return rand() % 11;  //gera um n�mero aleat�rio entre 0 e 10
}

//essa fun��o serve para guardar os s�mbolos e numeros gerados em "gerarSimboloAleatorio" e "gerarNumeroAleatorio" em um vetor do tipo DadoAleatorio
void guardarSimbolosNumeros(DadoAleatorio vetor[10]){
	int i;
	//guardar de forma intercalada
	for (i = 0; i < 10; i++) {
        if (i % 2 == 0) {  //guarda simbolos em posi��es pares
            vetor[i].simbolo = gerarSimboloAleatorio();
            vetor[i].numero = 0; //quando � n�mero, inicializa com 0
        } else { 
            vetor[i].simbolo = '\0'; //guarda numeros em posi��es �mpares
            vetor[i].numero = gerarNumeroAleatorio();// quando � s�mbolo, usa o caracter "nulo" pra falar que n�o tem s�mbolo
        }
    }
}

//essa fun��o imprime o vetor de s�mbolos e n�meros
void imprimirVetor(DadoAleatorio v[10]){
	for (int i = 0; i < 10; i++) {
        if (v[i].simbolo != '\0') {
            printf("%c ", v[i].simbolo);//usando os crit�rios da fun��o "guardarSimbolosNumeros" para guardar de forma intercalada
        } else {
            printf("%d ", v[i].numero);
        }
    }
}

//essa fun��o verifica se a sequ�ncia que o usu�rio escreveu como resposta � igual � sequ�ncia gerada
int verificarSequencia(DadoAleatorio sequencia[10]){
	int acertos = 0;
	DadoAleatorio resposta[10]; 
	for (int i = 0; i < 10; i++){
		if (i%2 == 0){ //a sequ�ncia tem s�mbolos na posi��o par e n�meros na posi��o �mpar. logo, j� que "resposta[10]" � uma estrutura com n�meros e s�mbolos, � preciso verificar qual a posi��o para ler um dado char ou int.
			printf("%d� elemento: \n", i+1);
			scanf(" %c", &resposta[i].simbolo);//o scanf l� o caractere de nova linha ao inv�s de ler um caractere ap�s um n�mero, a partir da segunda vez do loop. Ent�o, ao colocar um espa�o antes de %c, instrui o sancf a ignorar qualquer espa�o em branco antes de ler o caractere 
			getchar(); //limpar o buffer para o pr�ximo s�mbolo da sequ�ncia 
			fflush(stdin);//limpar o buffer para, se o usu�rio quiser jogar de novo, n�o ter nada da jogada anterior no buffer
		} else {
			printf("%d� elemento: \n", i+1);
			scanf("%d", &resposta[i].numero);
			fflush(stdin); //limpar o buffer para, se o usu�rio quiser jogar de novo, n�o ter nada da jogada anterior no buffer
		}
	}
		
	/*/printf("\n\nSua resposta: ");
	for (int i = 1; i <= 10; i++){
		if (resposta[i].simbolo != '\0') {
            printf("%c ", resposta[i].simbolo);//usando os crit�rios da fun��o "guardarSimbolosNumeros" para guardar de forma intercalada
        } else {
            printf("%d ", resposta[i].numero);
        }
	}
	
	printf("\n\n");/*/
		
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

//essa fun��o verifica se o usu�rio acertou toda a sequ�ncia ou n�o, e imprime o resultado
void scoreUser(int qntdAcertos, DadoAleatorio vet[10]){
	if (qntdAcertos == 10){
		printf("\t\t\tPar�bens!!! Voc� tem uma �tima mem�ria! Verifique a sequ�ncia exibida:\n\n");
		imprimirVetor(vet);
	} else {
		printf("\t\t\tQue pena! Sua mem�ria n�o � muito boa :( Verifique a sequ�ncia exibida:\n\n");
		imprimirVetor(vet);
	}
}
int main(){
	DadoAleatorio vetorDados[10];
	DadoAleatorio vetorRespostas[10];
	int i, j;
	int acertos = 0;
	int opcao = 0;
	char c;
	
	setlocale(LC_ALL, "Portuguese");
	
	do {
		system("cls");
		//iniciar a fun��o rand()
    	srand(time(NULL));
    	
    	printf("\t\t\t\t\tBem-Vindo ao Jogo da Mem�ria!\t\t\t\t\t\n\n");
    	printf("Ser�o gerados 5 s�mbolos (caracteres especiais do teclado) e 5 n�meros (entre 0 e 10).\n");
    	printf("Voc� deve memorizar a sequ�ncia de s�mbolos e n�meros em 20 segundos e depois escrev�-la na ordem em que foi exibida.\n");
    	printf("Pressione ENTER para iniciar. Boa sorte!\n");
    	
    	do {
    		c = getch(); //recebe o ENTER do usu�rio
		}while (c != 13); //enquanto ele n�o digitar o ENTER, n�o se inicia o jogo. "c" est� verificando se a tecla pressionada � o Enter (c�digo 13 na tabela ASCII).
    	guardarSimbolosNumeros(vetorDados);
    	
    	j = 20; //o usu�rio deve memorizar a sequ�ncia de s�mbolos e n�meros em 20 segundos.
    	
    	do {
    		system("cls"); //limpar a tela do console a cada itera��o do j.
    		if (j > 1){
    			printf("Memorize a sequ�ncia abaixo em %d segundos\n\n", j);
			} else {
				printf("Memorize a sequ�ncia abaixo em %d segundo\n\n", j);
			}
    		
			j--; 
			imprimirVetor(vetorDados);
			
			Sleep(1000);//essa fun��o recebe um valor positivo que representa a quantidade de milissegundos que � necess�rio esperar;
		} while (j > 0);
		
		system("cls");
		printf("Informe a sequ�ncia de s�mbolos e n�meros exibida: \n\n"); 
		acertos = verificarSequencia(vetorDados);
		scoreUser(acertos, vetorDados);  
		printf("\n\nGostaria de tentar novamente? Digite 1 para 'sim' ou 2 para n�o':");
		scanf("%d", &opcao);
		
	} while (opcao == 1);

	return 0;
}
