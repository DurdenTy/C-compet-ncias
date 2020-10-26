#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main()
{
FILE *f = fopen("arq.txt", "r");
char c;
if(f == NULL){
	printf("O arquivo nao pode ser executado");
	return(EXIT_FAILURE);
}
	fputs("**************************\n", f);
	while((c = getchar()) != EOF)
		fputs(c, f);
	fputs("**************************\n", f);
	fclose(f);
	
    
    return 0;
}
