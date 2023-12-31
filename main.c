#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int i, k, adicConv;
int hora;
int escolha;
char fechar;

struct FichaConvenio {
	int codigo;
	char  nome[50];
	int valor;
};
struct FichaConvenio convenio[20];

struct FichaMedica {
   int hora;
   char  nome[50];
   char  celular[50];
   int codigo;
   struct FichaConvenio fichaC;
};

struct FichaMedica ficha[12];

void bancoDadosConvenio () {
	convenio[0].codigo = 100;
 	strcpy(convenio[0].nome, "Unimed");
 	convenio[0].valor = 30;

 	convenio[1].codigo = 101;
 	strcpy(convenio[1].nome, "Porto");
 	convenio[1].valor = 40;

 	convenio[2].codigo = 102;
 	strcpy(convenio[2].nome, "Particular");
 	convenio[2].valor = 400;

 	convenio[3].codigo = 103;
 	strcpy(convenio[3].nome, "Outro");
 	convenio[3].valor = 0;

 }

void mostrar(struct FichaMedica *paciente) {
   	if (paciente->hora!=0){
		printf( "|%-10i| %-10s| %-15s| %-8i| %-15s| %-10i|\n",
                  paciente->hora,
                  paciente->nome,
                  paciente->celular,
                  paciente->codigo,
                  paciente->fichaC.nome,
                  paciente->fichaC.valor);
		}
	}


void autopreencher(int atual){
      int codigoConvenio = ficha[atual].codigo;
          for (i=0; i<20; i++){
	    if (convenio[i].codigo == codigoConvenio) {
		 strcpy (ficha[atual].fichaC.nome, convenio[i].nome);
		 ficha[atual].fichaC.valor = convenio[i].valor;
		 break;
	 }
      }
    }

void visualizar () {
	printf("|%-10s| %-10s| %-15s| %-8s| %-15s| %-10s|\n", 
		"Hora", 
		"Nome", 
		"Celular", 
		"Código", 
		"Convênio", 
		"Valor");
}
	// Exibição das informações da consulta
	for (k = 0; k < 12; k++){
		mostrar(&ficha[k]);
			}
}

void excluirConvenio(char nome[]) {
    int encontrado = 0;

    // 20 por causa do horario
    for (int i = 0; i < 20; i++) {
        if (strcmp(nome, convenio[i].nome) == 0) {
            encontrado = 1;
                for (int j = i; j < 20; j++) {
                convenio[j] = convenio[j + 1];
            }
          
	    convenio[20].codigo = 0;
            strcpy(convenio[20].nome, "");
            convenio[20].valor = 0;

            printf("Convênio removido com sucesso!\n");
            break;
        }
    } if (!encontrado) {
         printf("Convênio não encontrado!\n");
    }
}

void adicionarConvenio(int adicConv) {
    int novoCodigo;

    printf("Digite o código do convênio: ");
    scanf("%d", &novoCodigo);

    // Verifica se o código já existe
    for (int j = 0; j < adicConv; j++) {
        if (convenio[j].codigo == novoCodigo) {
            printf("Um convênio com esse código já existe. Escolha um código diferente.\n");
            return; // Retorna sem adicionar o convênio
        }
    }

    if (adicConv < 21) {
        struct FichaConvenio novoConvenio;

        novoConvenio.codigo = novoCodigo;

        printf("Digite o nome do convênio: ");
        scanf("%s", novoConvenio.nome);

        printf("Digite o valor do convênio: ");
        scanf("%d", &novoConvenio.valor);

        // Verifica se a posição 20 do vetor já está ocupada
        for (int i = 0; i < adicConv; i++) {
            if (convenio[20].codigo != 0) {
                printf("Escolha outro código novo convênio.\n");
                return;
            }
        }

        convenio[4] = novoConvenio; // Adiciona o novo convênio no final do vetor
        adicConv++;

        printf("Convênio adicionado com sucesso!\n");
    } else {
        printf("Limite de convênios atingido!\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    bancoDadosConvenio ();


    do {
    	system ("cls");
        printf("MENU\n");
        printf("1. Visualizar\n");
        printf("2. Incluir\n");
        printf("3. Apagar\n");
        printf("4. Alterar\n");
        printf("5. adicionar convenio\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        
	system ("cls");
  
	switch (escolha) {
            case 1:
                printf("Você escolheu Visualizar.\n\n");
                visualizar ();
		printf("Tecle algo para voltar");
		scanf("%c%c", &fechar, &fechar);
		break;

             case 2:
                printf("Você escolheu Incluir.\n\n");
                printf("_________________________________________________\n");
                printf("|Planos  | Código   |  Plano       | Valor (R$) |\n");
                printf("|_______________________________________________|\n");

                for(int i = 0; i < 5; i++){
                printf("|  %2i    |%5d     |  %-12s| %5d      |\n", i+1, 
			convenio[i].codigo, 
			convenio[i].nome, 
			convenio[i].valor); }
                printf("|_______________________________________________|\n");

                int horarioValido = 0;
                int horarioDisponivel;

                while (!horarioValido) {
                        printf("\n\nHora: \n");
                        scanf("%i", &hora);

                 if (hora < 7 || hora > 19){ printf("*Horário de atendimento indisponível*\n"); }
                 
		 else {
                        int horarioDisponivel = 1;

                        for(int i = 0; i < 13; i++){
                            if(ficha[i].hora == hora){
                            horarioDisponivel = 0;
                            break;}
                      }

                 if (horarioDisponivel){
                        horarioValido = 1;  // O horário é válido, podemos sair do loop
                        hora = hora - 7;
                        ficha[hora].hora = hora + 7;

                        printf("Digite o nome: ");
                        scanf("%s", ficha[hora].nome);

                        printf("Digite o celular: ");
                        scanf("%s", ficha[hora].celular);

                        printf("Digite o código: ");
                        scanf("%i", &ficha[hora].codigo);
                        autopreencher(hora);
                 } else {
			 printf("Horário já cadastrado.\n"); } }

                 while (getchar() != '\n');}
                 //o loop infinito getchar leitura char até a novo char da prox linha, por isso != \n
                 break;

            case 3:
               // Case 3 não chama a função pois todos os outros cases já estão ocupados, então
               // é chamado automaticamente
                printf("Você escolheu Apagar.\n");
		visualizar ();

                printf("\nhora \n ");
                scanf("%i", &hora);
                hora=hora -7;
                ficha[hora].hora = 0;
                strcpy (ficha[hora].nome, "");
                strcpy (ficha[hora].celular, "");
                ficha[hora].codigo = 0;
                autopreencher(hora);
                break;

            case 4:
                printf("Você escolheu Alterar.\n");

                int escolha;

                printf("\nSelecione o convênio que deseja alterar o valor:\n");

                for(int i = 0; i < 4; i++){
                   printf("%d. %s - %d\n", i+1, convenio[i].nome, convenio[i].codigo);
                }

                printf("Escolha: ");
                scanf("%d", &escolha);

                if(escolha >= 1 && escolha <= 4) {

                int novoValor;

                printf("Novo valor: ");
                scanf("%d", &novoValor);

                //[escolha - 1]  por causa da indexação causada de 1 a 4 e não de 0 a 3!
                convenio[escolha - 1].valor = novoValor;

                printf("Valores do convênio %s alterados com sucesso!\n", convenio[escolha - 1].nome);}

                else { printf("Opção inválida.\n");
                     } break;

                break;

            case 5:
                 adicionarConvenio(adicConv);
                 break;

            case 6:
                printf("Saindo do programa.\n");
                break;
                default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }


    } while (escolha != 6);

   return 0;}
