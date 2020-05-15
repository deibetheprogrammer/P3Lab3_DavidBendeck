#include <iostream>
#include<stdlib.h>
#include<time.h>

using std::cout;
using std::cin;
using std::endl;

//una función que crea una matriz de chars
char** createCharMatrix(int,int);

//una función que libera una matriz de chars
void freeCharMatrix(char**&, int);

//una función que imprime una matriz de chars
void printCharMatrix(char**, int,int);

//una función que llena aleatoriamente la matriz
void randomFill(char**&,int,int);

//una función que llena la matriz de forma predeterminada
void standardFill(char**&,int,int);

//función que simula el juego de la vida de Conway
void conway(char**&,int,int,int);

//función que prepara una matriz para ser utilizada por la función "conway"
void conwayFill(char**&,char**&,int,int);

//función para copiar una matriz a otra
void copyCharMatriz(char**&,char**&,int,int);


int main(int argc, char** argv) {
	
	//Menu
	cout << "******** BIENVENIDO AL JUEGO DE LA VIDA *******" << "\n\n\n"
		 << "*** MENU ***" << "\n\n"
		 << "1) Tablero predeterminado" << endl
		 << "2) Tablero aleatorio" << endl
		 << "Su elecccion: ";
	
	int opcion = 0;
	cin >> opcion;
	
	while ( !cin || opcion < 1 || opcion > 2 )
	{
    	cin.clear ();    // Restore input stream to working state
    	cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
    	cout << "Ingrese una opcion valida por favor (1 o 2): ";
    	cin >> opcion;    // After cin is restored and any garbage in the stream has been cleared, store user input in number again
	}
	
	cout << "Ingrese el numero de turnos que desea probar: ";
	int turnos = 0;
	cin >> turnos;
	
	while ( !cin || turnos < 1 )
	{
    	cin.clear ();    // Restore input stream to working state
    	cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
    	cout << "Ingrese un entero mayor a 0 por favor: ";
    	cin >> turnos;    // After cin is restored and any garbage in the stream has been cleared, store user input in number again
	}
	
	switch(opcion) {
		
		//Matriz predeterminada
		case 1: {
			
			//crear matriz de chars
			char** matriz = NULL;//instancia variable
	
			//llamar de creación
			matriz = createCharMatrix(20,20);
			
			//Llenar la matriz
			standardFill(matriz, 20, 20);
			
			conway(matriz, 20, 20, turnos);
			
			break;
		}
		
		//Matriz aleatoria
		case 2: {
			
			cout << "Ingrese el número de filas: ";
			int sizeX = 0;
			
			while ( !cin || sizeX < 1 )
			{
    			cin.clear ();    // Restore input stream to working state
    			cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
    			cout << "Ingrese un entero mayor a 0 por favor: ";
    			cin >> sizeX;    // After cin is restored and any garbage in the stream has been cleared, store user input in number again
			}
			
			cout << "Ingrese el número de columnas: ";
			int sizeY = 0;
			
			while ( !cin || sizeY < 1 )
			{
    			cin.clear ();    // Restore input stream to working state
    			cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
    			cout << "Ingrese un entero mayor a 0 por favor: ";
    			cin >> sizeY;    // After cin is restored and any garbage in the stream has been cleared, store user input in number again
			}
			
			//crear matriz de chars
			char** matriz = NULL;//instancia variable
	
			//llamar de creación
			matriz = createCharMatrix(sizeX,sizeY);
			
			//Llenar la matriz
			randomFill(matriz, sizeX, sizeY);
			
			conway(matriz, sizeX, sizeY, turnos);
			
			break;
		}
	}
	
	
	return 0;
}

//una función que imprime una matriz de chars
void printCharMatrix(char** matriz, int sizeX,int sizeY){
	if(matriz!=NULL){
		for(int i = 0; i<sizeX;i++){
			for(int j=0;j<sizeY;j++){
				cout<<matriz[i][j]<<" ";
			}
			cout<<endl;
		}//forj
	}//endif	
}


//una función que libera una matriz de chars
void freeCharMatrix(char**& matriz, int sizeX){
	//liberar la memoria de la matriz
	if(matriz!=NULL){
		
		//liberar los arreglos de chars
		for(int i =0; i<sizeX;i++){
			delete[] matriz[i];
		} 
		
		//liberamos el arreglo de apuntadores a char (char*)
		delete[] matriz;
		
		matriz=NULL;
	}
}

//una función que crea una matriz de chars
char** createCharMatrix(int sizeX, int sizeY){
	
	char** matriz=NULL;
	
	//crear el arreglo de apuntadores
	matriz = new char*[sizeX];
	
	//instanciar los arreglos de chars
	for(int i =0; i<sizeX;i++){
		matriz[i]=new char[sizeY];
	} 
		
	return matriz;
}

//una función que llena aleatoriamente la matriz
void randomFill(char**& matriz,int sizeX,int sizeY) {
	
	srand(time(NULL));
	
	int num = 0;
	
	for(int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			num = rand()%101;
			if(num >= 50) {
				matriz[i][j] = '*';
			} else {
				matriz[i][j] = ' ';
			}
		}
	}
}

//una función que llena la matriz de forma predeterminada
void standardFill(char**& matriz,int sizeX,int sizeY) {
	
	
	int temp_mat [20][20] = {	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0},
	{0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	
	for(int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			if(temp_mat[i][j] == 1) {
				matriz[i][j] = '*';
			} else {
				matriz[i][j] = ' ';
			}
		}
	}
}


//función que simula el juego de la vida de Conway
void conway(char**& matriz,int sizeX,int sizeY,int turnos) {
	
	sizeX += 2;
	sizeY += 2;
	
	//crear matriz de chars
	char** matrizConway = NULL;//instancia variable
	
	//llamar de creación
	matrizConway = createCharMatrix(sizeX,sizeY);
	
	//Llenar matriz
	conwayFill(matriz,matrizConway,sizeX,sizeY);
	
	//Creación de matrices actual y turno siguiente
	char** actual = NULL;
	actual = createCharMatrix(sizeX,sizeY);
	copyCharMatriz(matrizConway,actual,sizeX,sizeY);
	
	char** siguiente = NULL;
	siguiente = createCharMatrix(sizeX,sizeY);
	copyCharMatriz(matrizConway,siguiente,sizeX,sizeY);
	
	//El juego de la vida turno por turno
	for (int i = 0; i < turnos; i++) {
		
	}
	
	
}

//función que prepara una matriz para ser utilizada por la función "conway"
void conwayFill(char**& matriz,char**& matrizConway,int sizeX,int sizeY) {
	
	for (int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			//Creacion de borde superior e inferior
			if(i == 0 || i == (sizeX-1)) {
				matrizConway[i][j] = '#';
			} else {
				//Creacion de borde izquierdo y derecho
				if (j == 0 || j == (sizeY-1)) {
					matrizConway[i][j] == '#';
				} else { //Copiar la matriz original enmedio
					matrizConway[i][j] = matriz[i+1][j+1];
				}
			}
		}
	}
}

//función para copiar una matriz a otra
void copyCharMatriz(char**& original ,char**& copia,int sizeX,int sizeY) {
	
	for(int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			copia[i][j] = original[i][j];
		}
	}
}
