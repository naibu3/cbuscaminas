#ifndef __FUNCTIONS__

#define __FUNCTIONS__

//FUNCIONES DE RESERVA DE MEMORIA
char** ReservarMemTablero(int fil, int col);
void LiberarMemTablero(char** matriz, int fil);

int** ReservarMemMinas(int fil, int col);
void LiberarMemMinas(int** matriz, int fil);

//FUNCIONES DE INICIO
void RellenarTablero(char** matriz, int fil, int col, char caracter);
void ColocarMinas(int** matriz, int fil, int col, int n_minas);

//FUNCIONES DE JUEGO
void MostrarTablero(char** tablero, int** minas, int fil, int col);
void IntroducirCoord(int* f, int* c,  int fil, int col);
void ColocarPistas(int** minas, int fil, int col);
int RevelarCasilla(char** tablero, int** minas, int f, int c);
void RevelarAlrededor(char** tablero, int** minas, int fil, int col, int f, int c);
int ComprobarCasillasRest(char** tablero, int fil, int col, char caract);
int VolverAJugar();

//FUNCIONES GRAFICAS
void MostrarTitulo();
void LimpiarPantalla();
void Victoria();
void Derrota();

#endif