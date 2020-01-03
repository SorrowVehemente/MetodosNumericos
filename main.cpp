/**
 * 
 * Autor: Erick Daniel Fernández Cruz
 * 
 * Archivo: main.cpp
 * 
 * Descripción: Este programa muestra un menú con 4 metodos para
 * encontrar una raices.
 * 
 */

#include <iostream>
#include <locale.h>
#include <math.h>

using namespace std;
// Opciones para el menú
#pragma region MenuOpciones
enum OptionsMenu { Option_Invalid, Option1, Option2, Option3, Option4, Option5 };
OptionsMenu resolveOptions(string input);
#pragma endregion

// Definir métodos
#pragma region Métodos
void Biseccion();
void NewtonRaphson();
void Secante();
void Lagrange();
double F(double x); // La función a ser calculada
double F_Derivada(double x);
void tabular(double a, double b, int INTERVALOS);
void salirMetodo();
double errorAbsoluto(double viejo, double nuevo); // Se usa en el meétodo de la Secante
#pragma endregion

// Menú de opciones mostradas al usuario
#pragma region menu
string menu() {
	string option;
	bool looping = true;
	cout << endl << "******** MENÚ ********" << endl
		<< "1 -> Método de Bisección" <<endl
		<< "2 -> Método de Newton Raphson" << endl
		<< "3 -> Método de la Secante" << endl
		<< "4 -> Método Lagrange" << endl
		<< "5 -> Salir del programa" << endl
		<< "Ingrese opción deseada > ";
	cin >> option;
	return option;
}
#pragma endregion

int main() {
	// Mostrar carácteres con acentos y demás
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
				cout << endl << "Opción desconocida, intentelo otra vez" << endl;
				break;
			}
		}
	} while (looping);

	cout << "\nSaliendo del programa." << endl;
	return 0;
}

// Método de Bisección
#pragma region Bisección
void Biseccion() {
	int imax, iter = 0;
	double xi, xd, ea, em, test, xa = 0, xaold;

	cout << "\nMétodo de Bisección\n" << endl;
	cout << "Ingrese el extremo del intervalo de la izquierda > ";
	cin >> xi;
	cout << "Ingrese el extremo del intervalo de la derecha > ";
	cin >> xd;
	cout << "Ingrese el número de iteraciones maximas > ";
	cin >> imax;
	cout << "Ingrese el error minimo de cálculo > ";
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

// Método de NewtonRaphson
#pragma region NewtonRaphson
void NewtonRaphson() {
	const int MAX_ITER = 100;
	const int INTERVALOS = 6;
	const int PRECISION = 10;

	double a,
		b,
		tolerancia,
		error,
		x0, // primera aproximación
		x1; // siguiente aproximación
	int iteracion;
	bool converge = true;

	cout.precision(PRECISION);
	cout << "\nCálculo de las raices de una función aplicando el método de Newton Raphson" << endl;
	cout << "\nIngrese el intervalo inicial [a,b]:" << endl;

	// Se ingresa el intervalo
	cout << "\na > ";
	cin >> a;

	cout << "b > ";
	cin >> b;

	// Se tabulan los valores de f para INTERVALOS intervalos
	tabular(a, b, INTERVALOS);

	// Se pide elegir una aproximación inicial
	cout << "\nEscoja el punto inicial adecuado:   x0 > ";
	cin >> x0;

	// Se pide ingresar la tolerancia
	cout << "Tolerancia > ";
	cin >> tolerancia;

	// Iteraciones
	// Se imprimen los valores de la primera aproximación
	cout << "\nAproximacion inicial:" << endl;
	cout << "x0 = " << x0 << endl
		<< "f(x0) = " << F(x0) << endl
		<< "f'(x0) = " << F_Derivada(x0) << endl;

	iteracion = 1;
	do {
		if (iteracion > MAX_ITER) {
			converge = false;    // Se sobrepasó la máxima cantidad de iteraciones permitidas
			break;
		} else {
			x1 = x0 - F(x0) / F_Derivada(x0); // Cálculo de la siguiente aproximación
			error = fabs(x1 - x0);    // El error es la diferencia entre dos aproximaciones sucesivas

			// Se imprimen los valores de la siguiente aproximación x1, F(x1), F_derivada(x1), error
			cout << "\nIteracion #" << iteracion << endl;
			cout << "x" << iteracion << " = " << x1 << "\n"
				<< "f(x" << iteracion << ") = " << F(x1) << "\n"
				<< "f'(x" << iteracion << ") = " << F_Derivada(x1) << "\n"
				<< "error = " << error << endl;

			// La diferencia entre dos aproximaciones sucesivas es también conocida como error.
			// La condición de terminación consiste en que que el error debe ser <= que la tolerancia dada
			// Si se cumple la condición de terminación, se ha encontrado la raiz aproximada buscada.
			if (error <= tolerancia) { // Condición de terminación
				converge = true;
				break;

				// Si no se cumple el criterio de terminación, se pasa a la siguiente iteración
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
		cout << "\n\nSe sobrepasó la máxima cantidad de iteraciones permitidas" << endl;
	}
	salirMetodo();
}
#pragma endregion

// Método de Secante
#pragma region Secante
void Secante() {
	cout.precision(10);
	cout << "\nAplicación del método de la Secante" << endl;
	
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

		//Se suma una iteración.
		iteraciones++;

		//Todo lo hace mientras el error deseado no haya sido
		//alcanzado todavía.
	} while (error > tolerancia);

	cout << "La raiz es: " << x1 << endl;
	cout << "Encontrada en: " << iteraciones << " iteraciones." << endl;

	salirMetodo();
}
#pragma endregion

// Método de Lagrange
#pragma region Lagrange
void Lagrange() {
	cout << "Método de interpolación de Lagrange" << endl;
	int n;
	float x[101],
		y[101],
		x_interpol,
		y_interpolada = 0;
	float productos_num,
		productos_den;

	cout << "\n¿Cuántos elementos va a ingresar? debe ser de 1 a 100 \n > ";
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
//Función que calcula el error
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

