#include <iostream>
#include <locale.h>
#include <math.h>

using namespace std;
// Opciones para el men�
#pragma region MenuOpciones
enum OptionsMenu { Option_Invalid, Option1, Option2, Option3, Option4, Option5 };
OptionsMenu resolveOptions(string input);
#pragma endregion

// Definir m�todos
#pragma region M�todos
void Biseccion();
void NewtonRaphson();
void Secante();
void Lagrange();
double F(double x); // La funci�n a ser calculada
#pragma endregion

// Men� de opciones mostradas al usuario
#pragma region menu
string menu() {
	string option;
	bool looping = true;
	cout << endl << "******** MEN� ********" << endl
		<< "1 -> M�todo Bisecci�n" <<endl
		<< "2 -> Tangente" << endl
		<< "3 -> M�todo 3" << endl
		<< "4 -> Lagrange" << endl
		<< "5 -> Salir del programa" << endl
		<< "Ingrese opci�n deseada > ";
	cin >> option;
	return option;
}
#pragma endregion

int main() {
	// Mostrar car�cteres con acentos y dem�s
	#pragma region Acentos
	char *locale;
	locale = setlocale(LC_ALL, "");
	#pragma endregion

	string option;
	bool looping = true;
	do
	{
		option = menu();
		switch (resolveOptions(option)) {
			case Option1: {
				Biseccion();
				break;
			}
			case Option2: {
				NewtonRaphson();
				break;
			}
			case Option3: {
				Secante();
				break;
			}
			case Option4: {
				Lagrange();
				break;
			}
			case Option5: {
				looping = false;
				break;
			}
			case Option_Invalid:
			default: {
				cout << endl << "Opci�n desconocida, intentelo otra vez" << endl;
				break;
			}
		}
	} while (looping);

	cout << "\nSaliendo del programa." << endl;
	return 0;
}

// M�todo de Bisecci�n
#pragma region Bisecci�n
void Biseccion() {
	int imax, iter = 0;
	double xi, xd, ea, em, test, xa = 0, xaold;

	cout << "\nM�todo de Bisecci�n\n" << endl;
	cout << "Ingrese el extremo del intervalo de la izquierda > ";
	cin >> xi;
	cout << "Ingrese el extremo del intervalo de la derecha > ";
	cin >> xd;
	cout << "Ingrese el n�mero de iteraciones maximas > ";
	cin >> imax;
	cout << "Ingrese el error minimo de c�lculo > ";
	cin >> em;

	if (F(xi) * F(xd) > 0) {
		cout << "\nNo hay raiz en ese intervalo." << endl;
	}
	else {
		cout << "\nIter\tRaiz\t\tError Aprox" << endl;
		do {
			iter++;

			xaold = xa;
			xa = (xi + xd) / 2;
			ea = fabs((xa - xaold) / xa) * 100;

			test = F(xi) * F(xa);

			if (test < 0)
				xd = xa;
			else if (test > 0)
				xi = xa;
			else
				xa = 0;

			cout << iter << "\t" << xa << "\t\t" << ea << endl;

		} while (ea > em&& iter < imax);
	}

}
#pragma endregion

// M�todo de NewtonRaphson
#pragma region NewtonRaphson
void NewtonRaphson() {

}
#pragma endregion

// M�todo de Secante
#pragma region Secante
void Secante() {

}
#pragma endregion

// M�todo de Lagrange
#pragma region Lagrange
void Lagrange() {

}
#pragma endregion

// F
#pragma region F
double F(double x) {
	return x * x - 2;
}
#pragma endregion

// resolveOptions
#pragma region resolveOptions
OptionsMenu resolveOptions(string input) {
	if (input == "1") return Option1;
	if (input == "2") return Option2;
	if (input == "3") return Option3;
	if (input == "4") return Option4;
	if (input == "5") return Option5;
	return Option_Invalid;
}
#pragma endregion
