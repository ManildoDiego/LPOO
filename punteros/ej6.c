#include <stdio.h>

#define N 10

void cargarMatriz(int matriz[][N], int filas, int columnas) {
  printf("Ingrese los elementos de la matriz:\n");
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      printf("Ingrese el elemento en la posicion [%d][%d]: ", i, j);
      scanf("%d", &matriz[i][j]);
    }
  }
}

void escribirMatriz(int matriz[][N], int filas, int columnas) {
  for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
		  printf("%d ", matriz[i][j]);
		}
		printf("\n");
  }
}

void sumarMatrices(int matriz1[][N], int matriz2[][N], int resultado[][N], int filas, int columnas) {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      resultado[i][j] = matriz1[i][j] + matriz2[i][j];
    }
  }
}

void multiplicarMatrices(int matriz1[][N], int matriz2[][N], int resultado[][N], int filas1, int columnas1, int columnas2) {
  for (int i = 0; i < filas1; i++) {
    for (int j = 0; j < columnas2; j++) {
      resultado[i][j] = 0;
      for (int k = 0; k < columnas1; k++) {
        resultado[i][j] += matriz1[i][k] * matriz2[k][j];
      }
    }
  }
}

int calcularDeterminante(int matriz[][N], int orden) {
	if (orden == 1) {
	  return matriz[0][0];
	} else if (orden == 2) {
	  return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
	} else {
	  int determinante = 0;
	  for (int i = 0; i < orden; i++) {
      int submatriz[N][N];
      int subfilas = 0, subcolumnas = 0;
      for (int j = 1; j < orden; j++) {
        for (int k = 0; k < orden; k++) {
          if (k != i) {
            submatriz[subfilas][subcolumnas++] = matriz[j][k];
            if (subcolumnas == orden - 1) {
                subfilas++;
                subcolumnas = 0;
            }
          }
        }
      }
      determinante += matriz[0][i] * calcularDeterminante(submatriz, orden - 1) * (i % 2 == 0 ? 1 : -1);
	  }
	  return determinante;
	}
}

void calcularTranspuesta(int matriz[][N], int filas, int columnas) {
  int transpuesta[N][N];
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      transpuesta[j][i] = matriz[i][j];
    }
  }
  escribirMatriz(transpuesta, columnas, filas);
}

int main() {
  int matriz1[N][N], matriz2[N][N], resultado[N][N];
  int filas1, columnas1, filas2, columnas2;
  int opcion;

  while (1) {
		printf("\nMenu:\n");
		printf("1. Cargar matriz\n");
		printf("2. Escribir matriz\n");
		printf("3. Sumar matrices\n");
		printf("4. Multiplicar matrices\n");
		printf("5. Calcular determinante\n");
		printf("6. Calcular transpuesta\n");
		printf("7. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
		  case 1:
	      printf("Ingrese el numero de filas y columnas de la matriz 1: ");
	      scanf("%d %d", &filas1, &columnas1);
	      cargarMatriz(matriz1, filas1, columnas1);
	      printf("Ingrese el numero de filas y columnas de la matriz 2: ");
	      scanf("%d %d", &filas2, &columnas2);
	      cargarMatriz(matriz2, filas2, columnas2);
	      break;
		  case 2:
	      printf("Matriz 1:\n");
	      escribirMatriz(matriz1, filas1, columnas1);
	      printf("Matriz 2:\n");
	      escribirMatriz(matriz2, filas2, columnas2);
	      break;
		  case 3:
	      if (filas1 == filas2 && columnas1 == columnas2) {
          sumarMatrices(matriz1, matriz2, resultado, filas1, columnas1);
          printf("Resultado de la suma:\n");
          escribirMatriz(resultado, filas1, columnas1);
	      } 
				
				else {
          printf("Las matrices no tienen las mismas dimensiones, no se pueden sumar.\n");
	      }
	      break;
		  case 4:
	      if (columnas1 == filas2) {
          multiplicarMatrices(matriz1, matriz2, resultado, filas1, columnas1, columnas2);
          printf("Resultado de la multiplicacion:\n");
          escribirMatriz(resultado, filas1, columnas2);
	      } 
				
				else {
          printf("Las matrices no tienen las dimensiones adecuadas para la multiplicacion.\n");
	      }
	      break;
		  case 5:
	      if (filas1 == columnas1) {
          int determinante = calcularDeterminante(matriz1, filas1);
          printf("Determinante de la matriz 1: %d\n", determinante);
	      } 
				
				else {
          printf("La matriz 1 no es cuadrada, no se puede calcular el determinante.\n");
	      }
	      break;
		  case 6:
	      printf("Matriz 1 transpuesta:\n");
	      calcularTranspuesta(matriz1, filas1, columnas1);
	      break;
		  case 7:
	      return 0;
		  default:
	      printf("Opcion invalida. Por favor seleccione una opcion valida.\n");
		}
  }

  return 0;
}
