#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int R, G, B;
} pixel;

void input_matrix(int rows, int columns, pixel matrix[rows][columns]){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++)
      scanf("%d %d %d", &matrix[i][j].R, &matrix[i][j].G, &matrix[i][j].B);
  }
}

void print_matrix(int rows, int columns, pixel matrix[rows][columns]) {
  int i, j;
  printf("%d %d\n", rows, columns);
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      if(j+1 == columns)
        printf("%d %d %d ", matrix[i][j].R, matrix[i][j].G, matrix[i][j].B);
      else
        printf("%d %d %d ", matrix[i][j].R, matrix[i][j].G, matrix[i][j].B);
    }
    printf("\n");
  }
}

void fix_matrix(int rows, int columns, pixel matrix[rows][columns]){
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
  fix_matrix(rows, columns, matrix);
}

void invert_colors(int rows, int columns, pixel matrix[rows][columns]){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = 255-matrix[i][j].R;
      matrix[i][j].G = 255-matrix[i][j].G;
      matrix[i][j].B = 255-matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix);
}

void threshold(int rows, int columns, pixel matrix[rows][columns], int l){
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
  fix_matrix(rows, columns, matrix);
}

void brush_smoothing(int rows, int columns, pixel matrix[rows][columns]){
  int i, j;
  int g_aux, g;
  for (i = 1; i < rows-1; i++){
    for (j = 1; j < columns-1; j++){
      matrix[i][j].R = 1/9*(matrix[i-1][j-1].R + matrix[i][j].R + matrix[i+1][j+1].R);
      matrix[i][j].G = 1/9*(matrix[i-1][j-1].G + matrix[i][j].G + matrix[i+1][j+1].G);
      matrix[i][j].B = 1/9*(matrix[i-1][j-1].B + matrix[i][j].B + matrix[i+1][j+1].B);
    }
  }
  fix_matrix(rows, columns, matrix);
}

void constrat(int rows, int columns, pixel matrix[rows][columns], float g){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = g*matrix[i][j].R;
      matrix[i][j].G = g*matrix[i][j].G;
      matrix[i][j].B = g*matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix);
}

void brightness(int rows, int columns, pixel matrix[rows][columns], int g){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = matrix[i][j].R+g;
      matrix[i][j].G = matrix[i][j].G+g;
      matrix[i][j].B = matrix[i][j].B+g;
    }
  }
  fix_matrix(rows, columns, matrix);
}

void sepia(int rows, int columns, pixel matrix[rows][columns]){
  int i, j;
  for (i = 0; i < rows; i++){
    for (j = 0; j < columns; j++){
      matrix[i][j].R = 0.393*matrix[i][j].R + 0.769*matrix[i][j].G + 0.189*matrix[i][j].B;
      matrix[i][j].G = 0.349*matrix[i][j].R + 0.686*matrix[i][j].G + 0.168*matrix[i][j].B;
      matrix[i][j].B = 0.272*matrix[i][j].R + 0.534*matrix[i][j].G + 0.131*matrix[i][j].B;
    }
  }
  fix_matrix(rows, columns, matrix);
}


int main() {
  int L, C;
  scanf("%d %d", &L, &C);
  pixel matrix[L][C];
  pixel matrix_backup[L][C];
  input_matrix(L, C, matrix);

  printf("Inversao\n");
  sepia(L, C, matrix);
  print_matrix(L, C, matrix);

  return 0;
}
