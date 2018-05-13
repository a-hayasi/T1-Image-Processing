/*
 * Conversao de PPM para a versao RAW
 * Jander 2018
 *
 * CAP: trabalho 1
 */
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
	char nomearquivo[500];
	FILE *arquivo;
	int linhas, colunas, profundidade;
	int i, j;
	char magic[3]; // magic number = P6
	unsigned char byte;

	// parametros
	if(argc != 2){
		fprintf(stderr, "Uso: %s arquivo.ppm\n", argv[0]);
		return 1;
	}
	strcpy(nomearquivo, argv[1]);
	arquivo = fopen(nomearquivo, "rb");
	if(arquivo == 0){
		perror("Erro ao abrir arquivo");
		return 1;
	}

	// leitura do magic number
	fscanf(arquivo, "%s", magic);
	if(strcmp(magic, "P6") != 0){
		fprintf(stderr, "Erro de formato de arquivo\n");
		return 2;
	}

	// leitura das dimensoes e profundidade
	fscanf(arquivo, "%d %d", &colunas, &linhas);
	fscanf(arquivo, "%d%*c", &profundidade);
	if(linhas < 0 || colunas < 0 || profundidade != 255){
		fprintf(stderr, "Erro de formato de arquivo\n");
		return 3;
	}
	printf("%d %d\n", linhas, colunas);

	for(i = 0; i < linhas*colunas*3; i++){
		fread(&byte, sizeof byte, 1, arquivo);
		printf("%hhu ", byte);
	}

	printf("\n");

	fclose(arquivo);

	return 0;
}
