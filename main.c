#include "funciones.h"
#include <stdio.h>


#define FILAS 9
#define COLUMNAS 9

#define N_MINAS 5

#define CASILLA '#'


int main()
{
	LimpiarPantalla();

	int volver_a_jugar=1;

	int** tablMinas;
	char** tablero;

	int f;
	int c;

	tablero=ReservarMemTablero(FILAS, COLUMNAS);
	tablMinas=ReservarMemMinas(FILAS, COLUMNAS);

	do{
		MostrarTitulo();
		LimpiarPantalla();

		//Menu();

		RellenarTablero(tablero, FILAS, COLUMNAS, CASILLA);
		ColocarMinas(tablMinas, FILAS, COLUMNAS, N_MINAS);
		ColocarPistas(tablMinas, FILAS, COLUMNAS);

		//BUCLE PRINCIPAL
		while(1){

			if(ComprobarCasillasRest(tablero, FILAS, COLUMNAS, CASILLA)==N_MINAS){
				LimpiarPantalla();
				Victoria();
				break;
			}

			MostrarTablero(tablero, tablMinas, FILAS, COLUMNAS);
			IntroducirCoord(&f, &c,  FILAS, COLUMNAS);

			//Se destapa la casilla y se comprueba si no habia mina, si era una o si se ha ganado
			if(RevelarCasilla(tablero, tablMinas, f, c)==0){
				RevelarAlrededor(tablero, tablMinas, FILAS, COLUMNAS, f, c);
			}
			else if(RevelarCasilla(tablero, tablMinas, f, c)==9){
				LimpiarPantalla();
				Derrota();
				break;
			}

		}
	}while(VolverAJugar());

	LiberarMemTablero(tablero, FILAS);

	return 0;
}