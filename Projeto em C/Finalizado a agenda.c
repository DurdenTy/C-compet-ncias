
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 1000 //Define o valor máximo de contatos


typedef enum{
	TELA_SAIR = -1,
	TELA_PRINCIPAL,
	TELA_CADASTRAR,
	TELA_DESCADASTRAR,
	LISTAR_TODOS,
} Telas; //Define uma enumeração de escolhas

typedef struct{
	char nome[128];
	int telefone[64];
} Contato; //Cria a variável nova, tipo contato

typedef struct{
	Telas menu;
	int TotalContatos;
	Contato contatos[MAX_CONTATOS];
} AgendaTelefonica; //Chama a variável contato  e define o limite máximo


int main()
{
	AgendaTelefonica Agenda; //Cria a variável Agenda do tipo AgendaTelefonica, usa a estrutura como definição padrão
	memset(&Agenda, 0x0, sizeof(Agenda)); //Zera a agenda e retorna ao tamanho padrão;
    
	Agenda.menu = TELA_PRINCIPAL;// liga a variável Agenda a enumeração de menus;
	
	FILE *memoria = fopen("contatos.bin", "rb");
	if(memoria == NULL){
		printf("Erro, arquivo inexistente, criar (contatos.bin) no local desejado.");
		return 1;
	}
	
	size_t lidos = fread(Agenda.contatos, sizeof(Contato), MAX_CONTATOS, memoria);
	printf("Lidos %zd contatos\n\n\n\n\n", lidos);
	Agenda.TotalContatos = (int)lidos;
	fclose(memoria);
	
	
	while(Agenda.menu != TELA_SAIR){
	
		switch(Agenda.menu){
			case TELA_PRINCIPAL:
			{
				int opcao = -1;
				do{
				printf("\t\t   |================================|\n");
				printf("\t\t   |      Agenda Telefonica         |\n");
				printf("\t\t   |================================|\n\n\n");
				printf("\t\t_______________________________________\n\t\t\t |Selecione sua opcao|\n");
				printf("\t\t |===================================|\n");
				printf("\t\t |Opcao 1 - Tela de cadastro         |\n");
				printf("\t\t |Opcao 2 - Tela de descadastro      |\n");
				printf("\t\t |Opcao 3 - Listar todos os cadastros|\n");
				printf("\t\t |Opcao 0 - Sair da secao            |\n \t\t |===================================|\n\n\n");
				scanf("%d", &opcao);
				int b = 0;
				while((b = getchar()) != '\n' && b != EOF && b != '\n'){ }
				}while(opcao < 0 || opcao > 3);
				
				if(opcao == 0){
					Agenda.menu = TELA_SAIR;
				}
				if(opcao == 1){
					Agenda.menu = TELA_CADASTRAR;
					if(Agenda.TotalContatos >= MAX_CONTATOS){
						printf("\t\t\nAgenda lotada, nao pode adicionar novos contatos\n");
						Agenda.menu = TELA_PRINCIPAL;
					}
				}
				if(opcao == 2){
					Agenda.menu = TELA_DESCADASTRAR;
					if(Agenda.TotalContatos == 0){
						printf("\t\t\nSem contatos para serem apagados\n");
						Agenda.menu = TELA_PRINCIPAL;
					}
				}
				if(opcao == 3){
					Agenda.menu = LISTAR_TODOS;
					if(Agenda.TotalContatos == 0){
						printf("\t\t\nSem contatos para serem mostrados ou foram removidos\n\n");
						Agenda.menu = TELA_PRINCIPAL;
					}
				}	
			}
			break;
	
			case TELA_CADASTRAR:
				{
					printf("\t\t|================================|\n");
					printf("\t\t|   Cadastro de novo contato     |\n");
					printf("\t\t|================================|\n");
					Contato novo;
					char opcao = 's';
					printf("Voce quer adicionar novo contato? Aperte a tecla Enter para continuar");
					int a = 0;
					while((a = getchar()) != '\n' && a != EOF && a != '\n'){ }
					
					do
					{
						memset(&novo, 0x0, sizeof(novo));
						printf("Digite um nome para o contato: \n");
						fgets(novo.nome, 128, stdin);
						int id = 0;
						while(novo.nome[id] != '\0' && novo.nome[id] != '\n')
							id++;
						novo.nome[id] = '\0';
						printf("Digite um telefone para o seu contato:\n ");
						fgets(novo.telefone, 64, stdin);
						id = 0;
						while(novo.telefone[id] != '\n' && novo.telefone[id] != '\n')
							id++;
						novo.telefone[id] = '\0';
						printf("Realmente quer manter seu contato? [s/n]\n");
						opcao = getchar();
						int c = 0;
						while((c = getchar()) != '\n' && c != EOF){ }
			   		} while (opcao == 'n' || opcao == 'N');
			   		Agenda.contatos[Agenda.TotalContatos] = novo;
			    	Agenda.TotalContatos++;
			    	memoria = fopen("contatos.bin", "w+b");
			    	if(memoria == NULL){
			    		printf("Erro no arquivo 'contatos.bin'\n");
			    		return 0;
					}
					size_t salvos = fwrite(Agenda.contatos, sizeof(Contato), Agenda.TotalContatos, memoria);
					if(salvos != (size_t)Agenda.TotalContatos)
					{
						printf("Erro, sem possibilidade de salvar 'contatos,bin' em memoria.\n");
						return 1;
					}
					fclose(memoria);
					
							Agenda.menu = TELA_PRINCIPAL;
				
						}
				
				break;
			case LISTAR_TODOS:
				{
					printf("\t\t|+++++++++++++++++|\n");
					printf("\t\t|CONTATOS LISTADOS|\n");
					printf("\t\t|+++++++++++++++++|\n\n\n");
					
					int i;
					for(i = 0; i < Agenda.TotalContatos; i++){
						printf("\t\t|+++++++++++++++++|\n");
						printf("\t\t|Contato: %d\n", i);
						printf("\t\t|Nome: %s\n", Agenda.contatos[i].nome);
						printf("\t\t|Telefone:%d\n", Agenda.contatos[i].telefone);
						printf("\t\t|+++++++++++++++++|\n\n\n");
					}
					
				
				}
				Agenda.menu = TELA_PRINCIPAL;
				break;
				
			case TELA_DESCADASTRAR:
				{
					printf("\t\t|-----------------------|\n");
					printf("\t\t|DESCADASTRO DE CONTATOS|\n");
					printf("\t\t|-----------------------|\n\n\n");
					
					int i;
					for(i = 0; i < Agenda.TotalContatos; i++){
						printf("\t\t|------------------|\n");
						printf("\t\t|Contato: %d\n", i);
						printf("\t\t|Nome: %s\n", Agenda.contatos[i].nome);
						printf("\t\t|Telefone:%d\n", Agenda.contatos[i].telefone);
						printf("\t\t|------------------|\n\n\n");
						
					}
					
					int indice = -1;
					do{
						printf("Digite o número do contato o qual deseja remover: de 0 a %d", Agenda.TotalContatos - 1);
						scanf("%d", &indice);
						int c = 0;
						while((c = getchar()) != '\n' && c != EOF && c != '\n'){ }
					}while(indice < 0 || indice >= Agenda.TotalContatos);
					
					for(i = 0; i < Agenda.TotalContatos - 1; i++)
						Agenda.contatos[i] = Agenda.contatos[i + 1];
					
					Agenda.TotalContatos--;
					
					
					memoria = fopen("contatos.bin", "w+b");
					if(memoria == NULL){
			    		printf("Erro no arquivo 'contatos.bin'\n");
			    		return 0;
					}
					size_t salvos = fwrite(Agenda.contatos, sizeof(Contato), Agenda.TotalContatos, memoria);
					if(salvos != (size_t)Agenda.TotalContatos)
					{
						printf("Erro, sem possibilidade de salvar 'contatos,bin' em memoria.\n");
						return 1;
					}
					fclose(memoria);
					
					
					Agenda.menu = TELA_PRINCIPAL;
				}
				break;
		}
	}
    return 0;
}
