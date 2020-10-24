#include <stdio.h>
#include <stdlib.h>


int main(){
	
                          
	struct Ser{
		int Idade;
		char Nome[40];
		int Altura;
	};
	
	struct Ser Vulcano{161, "Spock", 182};
	struct Ser humano{177, "J.T. Kirk", 70};
	
	
	printf("The human named %s, captured in the forbidden planet, age %d, height %d, will be judge with together with the other subject,they was against our most severe rule, of course.\n", humano.Nome, humano.Idade, humano.Altura);
	printf("He was fighting with a Vulcan, they trying get some object, his name is %s, age %d, height %d, of course the human was losing... Proced de judgement", Vulcano.Nome, Vulcano.Idade, Vulcano.Altura);
	
	
	return 0;
}
