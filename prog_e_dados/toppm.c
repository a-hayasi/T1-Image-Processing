/*
 * Conversao de RAW para PPM
 * Jander 2018
 *
 * CAP: trabalho 1
 */
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
	char nomearquivo[500];
	FILE *arquivo;
	int linhas, colunas;
	int i, j, c;
	char magic[3]; // magic number = P6
	unsigned char byte;

	//printf("Arquivo de saida (use extensao .ppm): ");
	fgets(nomearquivo, sizeof nomearquivo, stdin);
	nomearquivo[strlen(nomearquivo) - 1] = 0;
	arquivo = fopen(nomearquivo, "wb");
	if(arquivo == 0){
		perror("Erro ao criar arquivo");
		return 1;
	}
	//printf("Numero de linhas: ");
	scanf("%d", &linhas);
	//printf("Numero de colunas: ");
	scanf("%d", &colunas);

	// saida do cabecalho
	fprintf(arquivo, "P6\n");
	fprintf(arquivo, "%d %d\n", colunas, linhas);
	fprintf(arquivo, "255\n"); 

	// saida dos dados
	for(i = 0; i < linhas; i++)
		for(j = 0; j < colunas; j++)
			for(c = 0; c < 3; c++){   // R, G e B
				scanf("%hhd", &byte);
				fwrite(&byte, sizeof byte, 1, arquivo);
				}
	printf("\n");

	fclose(arquivo);

	return 0;
}
