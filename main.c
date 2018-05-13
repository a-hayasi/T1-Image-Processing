#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int R, G, B;
} pixel;

void input_matrix(int rows, int columns, pixel matrix[rows][columns]){
  /* Inicializa a matrix de pixels,
     adicionando valores para o RGB de cada pixel */

  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++)
      scanf("%d %d %d", &matrix[i][j].R, &matrix[i][j].G, &matrix[i][j].B);
  }
}

void print_matrix(int rows, int columns, pixel matrix[rows][columns]) {
  /* Imprime a matriz na tela na forma de um vetor
     (para facilitar o teste) */

  int i, j;
  printf("%d %d\n", rows, columns);
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      if(j==0 && i==0)
        printf("%d %d %d", matrix[i][j].R, matrix[i][j].G, matrix[i][j].B);
      else
        printf(" %d %d %d", matrix[i][j].R, matrix[i][j].G, matrix[i][j].B);
    }
  }
  printf("\n");
}

void fix_matrix(int rows, int columns, pixel matrix[rows][columns]){
  /* Metodo para verificar os valores RGB da matrix de pixels.
   * Caso algum valor exceda 255, então é ajustado para 255.
   * Caso algum valor seja menor que 0, então é ajustado para 0. */

  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      if(matrix[i][j].R < 0) matrix[i][j].R = 0;
      else if(matrix[i][j].R > 255) matrix[i][j].R = 255;

      if(matrix[i][j].G < 0) matrix[i][j].G = 0;
      else if(matrix[i][j].G > 255) matrix[i][j].G = 255;

      if(matrix[i][j].B < 0) matrix[i][j].B = 0;
      else if(matrix[i][j].B > 255) matrix[i][j].B = 255;
    }
  }
}

void grayscale(int rows, int columns, pixel matrix[rows][columns]){
  /* Metodo "Niveis de Cinza" */

  int i, j;
  int g;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      g = (0.2126*matrix[i][j].R + 0.7152*matrix[i][j].G + 0.0722*matrix[i][j].B);
      matrix[i][j].R = g;
      matrix[i][j].G = g;
      matrix[i][j].B = g;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void invert_colors(int rows, int columns, pixel matrix[rows][columns]){
  /* Metodo "Inversao" */

  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = 255-matrix[i][j].R;
      matrix[i][j].G = 255-matrix[i][j].G;
      matrix[i][j].B = 255-matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void threshold(int rows, int columns, pixel matrix[rows][columns], int l){
  /* Metodo "Limiar" */

  int i, j;
  int g_aux, g;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      g_aux = 0.2126*matrix[i][j].R + 0.7152*matrix[i][j].G + 0.0722*matrix[i][j].B;
      g = ((g_aux < l) ? 0 : 255);
      matrix[i][j].R = g;
      matrix[i][j].G = g;
      matrix[i][j].B = g;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void brush_smoothing(int rows, int columns, pixel matrix[rows][columns]){
  /* Metodo "Suavização" */

  int i, j;
  int g_aux, g;
  for (i = 1; i < rows-1; i++){
    for (j = 1; j < columns-1; j++){
      matrix[i][j].R = 1/9*(matrix[i-1][j-1].R + matrix[i][j].R + matrix[i+1][j+1].R);
      matrix[i][j].G = 1/9*(matrix[i-1][j-1].G + matrix[i][j].G + matrix[i+1][j+1].G);
      matrix[i][j].B = 1/9*(matrix[i-1][j-1].B + matrix[i][j].B + matrix[i+1][j+1].B);
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void constrat(int rows, int columns, pixel matrix[rows][columns], float g){
  /* Metodo "Contraste" */

  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = g*matrix[i][j].R;
      matrix[i][j].G = g*matrix[i][j].G;
      matrix[i][j].B = g*matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void brightness(int rows, int columns, pixel matrix[rows][columns], int g){
  /* Metodo "Brilho" */
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = matrix[i][j].R+g;
      matrix[i][j].G = matrix[i][j].G+g;
      matrix[i][j].B = matrix[i][j].B+g;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}

void sepia(int rows, int columns, pixel matrix[rows][columns]){
  /* Metodo "Sepia" */

  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = 0.393*matrix[i][j].R + 0.769*matrix[i][j].G + 0.189*matrix[i][j].B;
      matrix[i][j].G = 0.349*matrix[i][j].R + 0.686*matrix[i][j].G + 0.168*matrix[i][j].B;
      matrix[i][j].B = 0.272*matrix[i][j].R + 0.534*matrix[i][j].G + 0.131*matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix); //Correcao de possiveis valores fora do intervalo 0-255.
}


int main(){
  printf("[LINHA DE COMANDO] Escolha os efeitos/filtros a serem aplicados.\n"
         "[CIN] - Níveis de cinza.\n"
         "[INV] - Inversão.\n"
         "[LIM] - Limiar.\n"
         "[MED] - Suavização.\n"
         "[CON] - Contraste.\n"
         "[BRI] - Brilho.\n"
         "[SEP] - Sepia.\n");

  /* choices[7[4] e um vetor de strings para identificacao de quais
   * metodos o usuario esta requisitando
   *
   * filter_choices[28] e um vetor de caracteres para armazenar a
   * entrada de comandos dados pelo usuario
   NOTA: Nao e permitido a inserção de mais de 7 opcoes! */

  char choices[7][4] = {"CIN", "INV", "LIM", "MED", "CON", "BRI", "SEP"};
  char filter_choices[28];

  if(fgets(filter_choices, 28, stdin)==NULL){ //fgets e utilizada para leitura
      printf("Algo deu errado!\n"); //dos comandos inseridos pelo usuario
      return 0;
  }

  printf("Deseja inserir valor aos parametros dos filtros?\n"
         "[1] - Sim.\n"
         "[0] - Nao.\n");

  /* Caso o usuario deseje inserir parametros, o mesmo deve informa-los na ordem
   * LIM, CON e BRI, de forma que os parametros que nao devem ser utilizados sejam
   * atribuidos ao valor 256.
   * Por exemplo, caso o unico comando dado na entrada seja BRI, entao a linha de
   * parametros deve estar na forma 256 256 X (onde X é o valor do brilho dado
   * pelo usuario) */

  int i, cond, parameters[3];
  scanf("%d", &cond);
  switch(cond){
    case 1:
      printf("[LINHA DE PARAMETROS(OPCIONAL)] Escolha os parâmetros dos filtros.\n"
             "[LIM, L]: Onde, l 0 a 255 (N) - (Default = 50).\n"
             "[CON, C]: Onde, c 0 a 255 (R) - (Default = 2).\n"
             "[BRI, B]: Onde, b -255 a 255 (Z) - (Default = 50).\n"
             "Os parametros que nao deseja adicionar, coloque o valor 256.\n");
      for(i=0; i<3; i++)
        scanf("%d", &parameters[i]);
    break;
    case 0:
      parameters[0] = 50;
      parameters[1] = 2;
      parameters[2] = 50;
    break;
  }

  /* Criacao e atribuicao dos valores à matriz de pixels */
  printf("Insira a matriz\n");
  int L, C;
  scanf("%d %d", &L, &C);
  pixel matrix[L][C];
  input_matrix(L, C, matrix);

  /* A partir daqui, são verificados os parametros dados pelo usuario
   * e se eles correspondem a algum metodo. Caso positivo, o metodo e
   * chamado. Caso contrario, a matriz inserida é impressa. */

  int cont;
  for(i=0, cont=0; i<7; i++){
    if(strstr(filter_choices, choices[i])){
      if (strcmp(choices[i], choices[0]) == 0){
          printf("Aplicando filtro [CIN] - Niveis de Cinza!\n");
          grayscale(L, C, matrix);
      }
      else if (strcmp(choices[i], choices[1]) == 0){
          printf("Aplicando filtro [INV] - Inversão!\n");
          invert_colors(L, C, matrix);
      }
      else if (strcmp(choices[i], choices[2]) == 0){
          printf("Aplicando filtro [LIM] - Limiar com limiar %d!\n", parameters[0]);
          threshold(L, C, matrix, parameters[0]);
      }
      else if (strcmp(choices[i], choices[3]) == 0){
          printf("Aplicando filtro [MED] - Suavização!\n");
          brush_smoothing(L, C, matrix);
      }
      else if (strcmp(choices[i], choices[4]) == 0){
          printf("Aplicando filtro [CON] - Contraste com valor de ganho%d!\n", parameters[1]);
          constrat(L, C, matrix, parameters[1]);
      }
      else if (strcmp(choices[i], choices[5]) == 0){
          int value;
          if (parameters[2] == 256) value = 2;
          else value = parameters[2];
          printf("Aplicando filtro [BRI] - Brilho com valor de ganho%d!\n", parameters[2]);
          brightness(L, C, matrix, parameters[2]);
      }
      else if (strcmp(choices[i], choices[6]) == 0){
          printf("Aplicando filtro [SEP] - Sépia!\n");
          brush_smoothing(L, C, matrix);
      }
    }
  }

  print_matrix(L, C, matrix);

  return 0;
}
