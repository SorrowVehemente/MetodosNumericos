/**
 * 
 * Autor: Erick Daniel Fern�ndez Cruz
 * 
 * Archivo: main.cpp
 * 
 * Descripci�n: Este programa muestra un men� con 4 metodos para
 * encontrar una raices.
 * 
 */

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
double F_Derivada(double x);
void tabular(double a, double b, int INTERVALOS);
void salirMetodo();
double errorAbsoluto(double viejo, double nuevo); // Se usa en el me�todo de la Secante
#pragma endregion

// Men� de opciones mostradas al usuario
#pragma region menu
string menu() {
	string option;
	bool looping = true;
	cout << endl << "******** MEN� ********" << endl
		<< "1 -> M�todo de Bisecci�n" <<endl
		<< "2 -> M�todo de Newton Raphson" << endl
		<< "3 -> M�todo de la Secante" << endl
		<< "4 -> M�todo Lagrange" << endl
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
	salirMetodo();
}
#pragma endregion

// M�todo de NewtonRaphson
#pragma region NewtonRaphson
void NewtonRaphson() {
	const int MAX_ITER = 100;
	const int INTERVALOS = 6;
	const int PRECISION = 10;

	double a,
		b,
		tolerancia,
		error,
		x0, // primera aproximaci�n
		x1; // siguiente aproximaci�n
	int iteracion;
	bool converge = true;

	cout.precision(PRECISION);
	cout << "\nC�lculo de las raices de una funci�n aplicando el m�todo de Newton Raphson" << endl;
	cout << "\nIngrese el intervalo inicial [a,b]:" << endl;

	// Se ingresa el intervalo
	cout << "\na > ";
	cin >> a;

	cout << "b > ";
	cin >> b;

	// Se tabulan los valores de f para INTERVALOS intervalos
	tabular(a, b, INTERVALOS);

	// Se pide elegir una aproximaci�n inicial
	cout << "\nEscoja el punto inicial adecuado:   x0 > ";
	cin >> x0;

	// Se pide ingresar la tolerancia
	cout << "Tolerancia > ";
	cin >> tolerancia;

	// Iteraciones
	// Se imprimen los valores de la primera aproximaci�n
	cout << "\nAproximacion inicial:" << endl;
	cout << "x0 = " << x0 << endl
		<< "f(x0) = " << F(x0) << endl
		<< "f'(x0) = " << F_Derivada(x0) << endl;

	iteracion = 1;
	do {
		if (iteracion > MAX_ITER) {
			converge = false;    // Se sobrepas� la m�xima cantidad de iteraciones permitidas
			break;
		} else {
			x1 = x0 - F(x0) / F_Derivada(x0); // C�lculo de la siguiente aproximaci�n
			error = fabs(x1 - x0);    // El error es la diferencia entre dos aproximaciones sucesivas

			// Se imprimen los valores de la siguiente aproximaci�n x1, F(x1), F_derivada(x1), error
			cout << "\nIteracion #" << iteracion << endl;
			cout << "x" << iteracion << " = " << x1 << "\n"
				<< "f(x" << iteracion << ") = " << F(x1) << "\n"
				<< "f'(x" << iteracion << ") = " << F_Derivada(x1) << "\n"
				<< "error = " << error << endl;

			// La diferencia entre dos aproximaciones sucesivas es tambi�n conocida como error.
			// La condici�n de terminaci�n consiste en que que el error debe ser <= que la tolerancia dada
			// Si se cumple la condici�n de terminaci�n, se ha encontrado la raiz aproximada buscada.
			if (error <= tolerancia) { // Condici�n de terminaci�n
				converge = true;
				break;

				// Si no se cumple el criterio de terminaci�n, se pasa a la siguiente iteraci�n
			} else {
				x0 = x1;
				iteracion++;
			}
		}
	} while (1);

	// Respuesta final
	if (converge) {
		cout << "\n\nPara una tolerancia de " << tolerancia << " la raiz de f es: " << x1 << endl;
	} else {
		cout << "\n\nSe sobrepas� la m�xima cantidad de iteraciones permitidas" << endl;
	}
	salirMetodo();
}
#pragma endregion

// M�todo de Secante
#pragma region Secante
void Secante() {
	cout.precision(10);
	cout << "\nAplicaci�n del m�todo de la Secante" << endl;
	
	double x0, x1, xi, error, tolerancia;
	int iteraciones = 0;
	
	cout << "\nIngrese los valores iniciales:" << endl;
	cout << "Ingrese x0 > ";
	cin >> x0;
	cout << "Ingrese x1 > ";
	cin >> x1;
	cout << "Ingrese la tolerancia > ";
	cin >> tolerancia;

	do {
		//Calcula el nuevo punto y el error.
		xi = x1 - ((F(x1) * (x0 - x1)) / (F(x0) - F(x1)));
		error = errorAbsoluto(x1, xi);

		x0 = x1;
		x1 = xi;

		//Se suma una iteraci�n.
		iteraciones++;

		//Todo lo hace mientras el error deseado no haya sido
		//alcanzado todav�a.
	} while (error > tolerancia);

	cout << "La raiz es: " << x1 << endl;
	cout << "Encontrada en: " << iteraciones << " iteraciones." << endl;

	salirMetodo();
}
#pragma endregion

// M�todo de Lagrange
#pragma region Lagrange
void Lagrange() {
	cout << "M�todo de interpolaci�n de Lagrange" << endl;
	int n;
	float x[101],
		y[101],
		x_interpol,
		y_interpolada = 0;
	float productos_num,
		productos_den;

	cout << "\n�Cu�ntos elementos va a ingresar? debe ser de 1 a 100 \n > ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Ingrese x #" << (i + 1) << " > ";
		cin >> x[i];
		cout << "Inrgese y #" << (i + 1) << " > ";
		cin >> y[i];
	}
	
	cout << "\nIngrese el valor de X a evaluar > ";
	cin >> x_interpol;

	// Lagrange
	for (int i = 0; i < n; i++) {
		productos_num = 1;
		productos_den = 1;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				productos_num *= (x_interpol - x[j]);
				productos_den *= (x[i] - x[j]);
			}
		}
		y_interpolada += (productos_num / productos_den) * y[i];
	}

	cout << "\nLa Y interpolada es: " << y_interpolada << endl;

	salirMetodo();
}
#pragma endregion

#pragma errorAbsoluto
//Funci�n que calcula el error
double errorAbsoluto(double viejo, double nuevo) {
	return abs((nuevo - viejo) / nuevo) * 100;
}
#pragma endregion
// F
#pragma region F
double F(double x) {
	//return x * x - 2;
	return x * exp(cos(x)) / 1.5 - 1;
}
#pragma endregion

// F_Derivada
#pragma region F_Derivada
double F_Derivada(double x) {
	//return x * 2;
	return exp(cos(x)) * (1 - x * sin(x)) / 1.5;
}
#pragma endregion

// tabular
#pragma region tabular
void tabular(double a, double b, int INTERVALOS) {
	int puntos = INTERVALOS + 1;

	double ancho = (b - a) / INTERVALOS;

	cout << "\n\tx\t\tf(x) " << endl;
	for (int i = 0; i < puntos; i++) {
		cout << "\t" << a << "\t\t" << F(a) << endl;
		a = a + ancho;
	}
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

// salirMetodo
#pragma region salirMetodo
void salirMetodo() {
	cin.get();
	cout << "Precione cualquier tecla para continuar ";
	cin.get();
}
#pragma endregion

