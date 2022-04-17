#include "funciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>	//Para num aleatorios usados en ColocarMinas
#include <ccolor.h>
#include <unistd.h>	//delay

//PARA LIMPIAR LA PANT
#ifdef _WIN32
	#include <windows.h>
#endif

char** ReservarMemTablero(int fil, int col){

	char** matriz;

	if( (matriz=(char**)malloc( fil*sizeof(char*))) ==NULL ){

		printf("[!] ERROR AL RESERVAR MEMORIA");
		exit(-1);
	}

	for(int i=0; i< fil ; i++){

		if( (matriz[i]=(char*)malloc(col*sizeof(char))) == NULL ){

			printf("[!] ERROR AL RESERVAR MEMORIA");
			exit(-1);
		}

	}
	
	return matriz;
}

int** ReservarMemMinas(int fil, int col){

	int** matriz;

	if( (matriz=(int**)malloc( fil*sizeof(int*))) ==NULL ){

		printf("[!] ERROR AL RESERVAR MEMORIA");
		exit(-1);
	}

	for(int i=0; i< fil ; i++){

		if( (matriz[i]=(int*)malloc(col*sizeof(int))) == NULL ){

			printf("[!] ERROR AL RESERVAR MEMORIA");
			exit(-1);
		}

	}
	
	return matriz;
}

void LiberarMemTablero(char** matriz, int fil){

	for(int i=0; i<fil; i++){

		free(matriz[i]);

	}

	free(matriz);
}

void LiberarMemMinas(int** matriz, int fil){

	for(int i=0; i<fil; i++){

		free(matriz[i]);

	}

	free(matriz);
}


void RellenarTablero(char** matriz, int fil, int col, char caracter){

	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			matriz[i][j]=caracter;
		}
	}
}

void ColocarMinas(int** matriz, int fil, int col, int n_minas){

	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			matriz[i][j]=0;
		}
	}

	//Generación de numeros aleatorios

	time_t t;         // tipo definido en time.h

	register int i;
	
	srand((int)time(&t));

	int fila;
	int columna;

	//Colocacion automatica de minas
	for(int i=0; i<n_minas; i++){

		fila=rand()%fil;
		columna=rand()%col;

		printf("<%i , %i>\n", fila, columna);

		matriz[fila][columna]=9;
	}
}

//TERMINAR MAS TARDE
void ColocarPistas(int** minas, int fil, int col){

	//Buscamos las minas
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){

			if(minas[i][j]==9){

				//Recorremos las cassillas alrededor de la mina para incrementar su valor
				//los if revisan no salir del rango del tablero
				for(int k=(i-1); k<(i+2); k++){
					if((0<=k)&&(k<fil)){
						for(int l=(j-1); l<(j+2); l++){
							if((0<=l)&&(l<col)){
								
								if(minas[k][l]!=9){
									minas[k][l]++;
								}

							}
						}
					}
				}
			}
		}
	}

}

int RevelarCasilla(char** tablero, int**minas, int f, int c){

	if(tablero[f][c]!=' '){

		tablero[f][c]=' ';
	
	}

	return minas[f][c];

}

void RevelarAlrededor(char** tablero, int** minas, int fil, int col, int f, int c){

	for(int i=(f-1); i<(f+2); i++){
		if((0<=i) && (i<fil)){

			for(int j=(c-1); j<(c+2); j++){
				if((0<=j) && (j<col)){

					if(tablero[i][j]!=' '){
						if(RevelarCasilla(tablero, minas, i, j)==0){
							RevelarAlrededor(tablero, minas, fil, col, i, j);
						}
					}

				}	
			}

		}
	}

}

void MostrarTablero(char** tablero, int** minas, int fil, int col){

	printf("\n    ");

	//Numeros de columnas
	printf(CYAN_T);
	for(int i=0; i<fil; i++){
		printf("%i   ", i);
	}
	printf(RES_COL);
	printf("\n");


	for(int i=0; i<fil; i++){

		//Numeros de filas
		printf(CYAN_T);
		printf("%i %s| ", i, RES_COL);

		for(int j=0; j<col; j++){
			//Si esta destapada se cambia por el numero de minas
			if(tablero[i][j]==' '){
				//color para los numeros
				if(minas[i][j]==1){
					printf(AZUL_T);
				}
				if(minas[i][j]==2){
					printf(VERDE_T);
				}
				printf("%i %s| ", minas[i][j], RES_COL);
			}//En caso contrario, se muestra el tablero tapado
			else{
				printf(AMARILLO_T);
				printf("%c %s| ", tablero[i][j], RES_COL);
			}
		}	
		printf("\n");	
	}
	printf("\n");
}

void IntroducirCoord(int* f, int* c, int fil, int col){
	
	do{
		printf("\nIntroduce la fila: ");
		scanf("%i", f);
		printf("\n");
	}while(!(col>(*f)>0));

	do{
		printf("\nIntroduce la columna: ");
		scanf("%i", c);
		printf("\n");	
	}while(!(fil>(*c)>0));
	
}

void MostrarTitulo(){

	printf("\n\n\n");
	printf(" ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄    ▄▄   ▄▄ ▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ \n");
	printf("█  ▄    █  █ █  █       █       █       █  █  █▄█  █   █  █  █ █       █       █\n");
	sleep(1);
	printf("█ █▄█   █  █ █  █  ▄▄▄▄▄█       █   ▄   █  █       █   █   █▄█ █   ▄   █  ▄▄▄▄▄█\n");
	printf("█       █  █▄█  █ █▄▄▄▄▄█     ▄▄█  █▄█  █  █       █   █       █  █▄█  █ █▄▄▄▄▄ \n");
	sleep(1);
	printf("█  ▄   ██       █▄▄▄▄▄  █    █  █       █  █       █   █  ▄    █       █▄▄▄▄▄  █\n");
	printf("█ █▄█   █       █▄▄▄▄▄█ █    █▄▄█   ▄   █  █ ██▄██ █   █ █ █   █   ▄   █▄▄▄▄▄█ █\n");
	sleep(1);
	printf("█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█  █▄█   █▄█▄▄▄█▄█  █▄▄█▄▄█ █▄▄█▄▄▄▄▄▄▄█\n");
	sleep(1);
	printf("\n*************************************By N4ibu3**********************************\n");
	sleep(1);
	printf("\n                                     Pulsa intro\n");
	getchar();
	scanf("");
}

void LimpiarPantalla(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

int ComprobarCasillasRest(char** tablero, int fil, int col, char caract){
	int cont=0;

	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			if(tablero[i][j]==caract){
				cont++;
			}
		}
	}
	return cont;
}

void Victoria(){
	printf("\n\n\n  /\\  /\\  __ _  ___ \n");
	printf(" / /_/ / / _` |/ __|									_\n");
	printf("/ __  / | (_| |\\__ \\	 __ _   __ _  _ __    __ _   __| |  ___  \n");
	printf("\\/ /_/   \\__,_||___/	/ _` | / _` || '_ \\  / _` | / _` | / _ \\ \n");
	printf("                       | (_| || (_| || | | || (_| || (_| || (_) |\n");
	printf("                      \\__, | \\__,_||_| |_| \\__,_| \\__,_| \\___/ \n");
	printf("                        |___/ \n");
	printf("\n\n                      Pulsa Intro\n");
	getchar();
	scanf("");
}

void Derrota(){
	printf("\n\n\n  /\\  /\\  __ _  ___ \n");
	printf(" / /_/ / / _` |/ __|                            _  _      _       \n");
	printf("/ __  / | (_| |\\__ \\	 _ __    ___  _ __   __| |(_)  __| |  ___ \n");
	printf("\\/ /_/   \\__,_||___/	| '_ \\  / _ \\| '__| / _` || | / _` | / _ \\ \n");
	printf("                        | |_) ||  __/| |   | (_| || || (_| || (_) |\n");
	printf("                        | .__/  \\___||_|    \\__,_||_| \\__,_| \\___/ \n");
	printf("                        |_|\n");
	printf("\n\n                      Pulsa Intro\n");
	getchar();
	scanf("");
}

int VolverAJugar(){

	LimpiarPantalla();
	
	char resp='a';

	while(!((resp=='s') || (resp=='n'))){

		printf("\n\nVolver al titulo?(s/n): ");
		getchar();
		scanf("%c", &resp);
		printf("%s","Hola");
	}
	if(resp=='s'){
		return 1;
	}
	else{
		return 0;
	}
}