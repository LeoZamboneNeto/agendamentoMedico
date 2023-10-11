#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int i, k;
int hora;
int escolha;
char fechar;

// MUDANÇAS:
// Definição da struct para representar uma consulta médica
// void Mostrar: Mudança de estrutura para beleza e visibilidade
// void visualizar: Mudança de beleza estrutural
// Incluir: Adição de visualização sobre códigos e planos
// Incluir: Horário de funcionamento 7 às 20
// Incluir:adição de loop para retornar ao cadastro
// Horários em ordem crescente

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

    //Adição para pacientes outros
 	convenio[3].codigo = 0;
 	strcpy(convenio[3].nome, "Outro");
 	convenio[3].valor = 0;
}

void mostrar(struct FichaMedica *paciente) {
    //Mudança de estrutura para beleza e visibilidade

	if (paciente->hora!=0){
		printf( "|%2i       |%4s      | %9s   |  %i       |%7s       |%5i      |\n", paciente->hora, paciente->nome, paciente->celular,paciente->codigo, paciente->fichaC.nome, paciente->fichaC.valor);

    	//printf ("\n-------------------------\n");
		}
	}

void autopreencher(int atual){
for (i=0; i<20; i++){
	if (convenio[i].codigo == ficha[atual].codigo) {
		strcpy (ficha[atual].fichaC.nome, convenio[i].nome);
		ficha[atual].fichaC.valor = convenio[i].valor;
		break;
	}
}
}

void visualizar () {
    //modificação table para beleza estrutural

	   for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12-i; j++) {
             if (ficha[j].hora > ficha[j+1].hora) {
                // Troca as entradas

		struct FichaMedica temp = ficha[j];
                ficha[j] = ficha[j+1];
                ficha[j+1] = temp;
            }
        }
    }

	printf("\n\n|Hora     | Nome     | Celular       | Código     | Convênio     | Valor     |\n");
	
	for (k = 0; k < 12; k++){
        mostrar(&ficha[k]);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    bancoDadosConvenio ()  ;


    do {
    	system ("cls");
        printf("MENU\n");
        printf("1. Visualizar\n");
        printf("2. Incluir\n");
        printf("3. Apagar\n");
        printf("4. Alterar\n");
        printf("5. Sair\n");
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

                //Adição: Visualização dos códigos do plano
                printf("_________________________________________________\n");
                printf("|Planos  | Código   |  Plano       | Valor (R$) |\n");
                printf("|_______________________________________________|\n");

                for(int i = 0; i < 4; i++){
                printf("|  %2i    |%5d     |  %-12s| %5d      |\n", i+1, convenio[i].codigo, convenio[i].nome, convenio[i].valor);}
                printf("|_______________________________________________|\n");

                 // 22 12 leo 1998276xxxx 101
                 //
                 //adição de loop para retornar ao cadastro
               
                  
                //------------------------------------------------------------------

                 //Perguntar sobre %4d que seja fixa para esquerda e para direita
                 // perguntar do for(j= 0....)
                
                 int horarioValido = 0;
                 int j;
                 
                 while (!horarioValido) {
                        printf("\n\n|Hora    | Nome     | Celular      | Código     |\n");
                        scanf("%i", &hora);

                    for(j = 7; j < 20; j++){
                       if(j == hora) {printf("Existe cliente cadastrado, horário indisponível\n");
                       break;}
                    }
                    
                    if (hora < 7 || hora > 19){ printf("*Horário de atendimento indisponível*\n"); }
                    
                    else {
                          horarioValido = 1;  // O horário é válido, podemos sair do loop
                          hora = hora - 7;
                          ficha[hora].hora = hora + 7;
                          scanf("%s", ficha[hora].nome);
                          scanf("%s", ficha[hora].celular);
                          scanf("%i", &ficha[hora].codigo);
                          autopreencher(hora);
                         } 
                         while (getchar() != '\n');} //o loop infinito getchar leitura char
                         break;                      //até a novo char da prox linha, por isso != \n


                 

            case 3:
                printf("Você escolheu Apagar.\n");
                // Coloque o código para apagar aqui.
                visualizar ();
                printf("hora \n ");
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
                // Coloque o código para alterar aqui.
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (escolha != 5);

   return 0;}
