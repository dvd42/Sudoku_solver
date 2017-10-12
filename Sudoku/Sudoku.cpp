// Sodoku.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"


// =============================================================================
// ALUMNOS =====================================================================
// =============================================================================

char* NombreAlumno1 = "Diego";
char* ApellidosAlumno1 = "Velazquez Dorta";
char* NIAAlumno1 = "1429086"; // NIA alumno1

							  // No rellenar en caso de grupo de un alumno
char* NombreAlumno2 = "Nil";
char* ApellidosAlumno2 = "Domene Esteban";
char* NIAAlumno2 = "1425988"; // NIA alumno2

char* NIAS[] = {
	"1335167","1428136","1397750","1390855","1424739","1424670","1423739",
	"1423177","1427371","1423725","1448752","1423210","1391968","1424454",
	"1338429","1425988","1424818","1421980","1368533","1365501","1423802",
	"1175542","1264719","1424801","1423710","1390452","1424116","1391795",
	"1395085","1391630","1424310","1423234","1425968","1307828","1395062",
	"1426532","1391627","1366098","1425082","1325835","1425067","1424350",
	"1424035","1391544","1391634","1426771","1424698","1358835","1362219",
	"1425785","1424114","1424408","1362389","1428260","1391808","1425084",
	"1366706","1391632","1425109","1424032","1430970","1430896","1428176",
	"1390536","1429086","1423588","1195650","1424671","1306347"
};

bool CheckNIA(char* nia)
{
	for (const char *pNIA : NIAS) {
		if (strcmp(nia, pNIA) == 0) return true;
	}
	return false;
}

// =============================================================================
// PROBLEMA ====================================================================
// =============================================================================

// Clock =======================================================================

double Clock()
{
	LARGE_INTEGER cnt;
	LARGE_INTEGER fre;

	if (QueryPerformanceFrequency(&fre) && QueryPerformanceCounter(&cnt)) {
		return (double)cnt.QuadPart / (double)fre.QuadPart;
	}
	else return (double)clock() / (double)CLOCKS_PER_SEC;
}

typedef int Sodoku[9][9];

// LeerSodoku ==================================================================

void LeerSodoku(Sodoku &s, const char *filename)
{
	FILE *fp;
	fopen_s(&fp, filename, "r");
	if (fp == NULL) {
		printf("No se ha podido abrir el fichero %s", filename);
		exit(1);
	}
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			fscanf_s(fp, "%d", &s[i][j]);
		}
	}
	fclose(fp);
}

// Print =======================================================================

void Print(Sodoku &s) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			printf("%d ", s[i][j]);
		}
		puts("");
	}
}

//  Implemented Functions (Backtracking) =======================================

void unassigned_value(int& row, int& col, Sodoku sd) {
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++) {
			if (sd[row][col] == 0) {
				return;
			}
		}
	}
	row = 9;
	return;
}

bool check_restrictions(int row, int col, int var, Sodoku sd) {

	for (int i = 0; i < 9; i++) {
		if ((var == sd[i][col]) || (var == sd[row][i])) {
			return false;
		}
	}

	row = (row / 3) * 3;
	col = (col / 3) * 3;


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (var == sd[row + i][col + j]) {
				return false;
			}
		}
	}
	return true;
}

bool Backtracking(int row, int col, Sodoku sd) {


	unassigned_value(row, col, sd);

	if (row > 8) {
		return true;
	}

	for (int i = 1; i <=9; i++) {
		if (check_restrictions(row, col, i, sd)) {
			sd[row][col] = i;
			if (Backtracking(row, col, sd)) {
				return true;
			}
			sd[row][col] = 0;
		}
	}
	return false;
}



// main ========================================================================

Sodoku taulell; // Variable per guadar el taulell del Sodoku

int main(int argc, char *argv[])
{
	if (!CheckNIA(NIAAlumno1) || !(*NIAAlumno2 == '\0' || CheckNIA(NIAAlumno2))) {
		puts("Indentificacio dels alumnes incorrecte");
		return 1;
	}
	printf("NIA1: %s\n", NIAAlumno1);
	printf("NOM1: %s\n", NombreAlumno1);
	printf("COGNOMS1: %s\n", ApellidosAlumno1);
	printf("NIA2: %s\n", NIAAlumno2);
	printf("NOM2: %s\n", NombreAlumno2);
	printf("COGNOMS2: %s\n", ApellidosAlumno2);
	//if (argc != 2) {
		//puts("Uso: sodoku FicheroDeSodoku\n");
		//return 1;
	//}
	
	double t0;
	double t1;

	//I ve modified the main function a bit so it solves all the sudokus at once and returns the total time
	// Hope its not a problem :)
	for (int i = 0; i < argc-1; i++) {
		printf("\n");
		printf(argv[i + 1]);
		LeerSodoku(taulell, argv[i + 1]);
		puts("\nSODOKU:");
		Print(taulell);
		bool HiHaSolucio = false;
		t0 = Clock();
		// Codi que soluciona el Sodoku
		// La solució es guarda a taulell
		// HiHaSolucio serà true si hi ha solució, en cas contrari serà false.

		HiHaSolucio = Backtracking(0, 0, taulell);

		t1 = Clock();
		if (true) {
			puts("\nSOLUCIO:");
			Print(taulell);
		}
		else {
			puts("\nNO TE SOLUCIO");
		}
		
	}
	printf("TEMPS TOTAL: %lf\n", t1 - t0);
	getchar();
	
	return 0;
}


