#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <fstream>
#include <string.h>

using namespace std;

string addZeros(int num, int desired_length){

	string base = "";

	for(int i=0; i < (desired_length - to_string(num).length()); i++)
    {
		base += "0";
	}

	base += to_string(num);
	return base;
}

string monthToNum(string mes, string *meses)
{
	for(int i = 0; i < 12; i++)
	{
		if(mes == meses[i])
		{
			return addZeros(i+1, 2);
		}
	}

	return "-1";

}

string removeDots(string hora)
{
	string resultado;
	int index;
	// eliminar ":" de hora, y regresar string con ese formato

	for(int i = 0; i < 2; i++)
	{
	    string line = hora.substr(index);
        index = line.find(":");

		string shora = line.substr(0, index);
		resultado += addZeros(stoi(shora), 2);
		index++;
	}
	index += 3;

	string line = hora.substr(index);
	index = line.find(" ");
    string shora = line.substr(0, index);
    resultado += addZeros(stoi(shora), 2);

	return resultado;
}

// Función de ordenamiento del método Quick Sort
int particion(vector<string> &A, int l, int r)
{
    // Define el pivote y la variable de ciclo de este
    int pivote = stoi(A[r]);
    int i = l - 1;

    for(int j = l; j < r; j++)
    {
        // Conforme cicla todo el arreglo, revisa si un valor es menor al pivote
        if(stoi(A[j]) < pivote)
        {
            // La variable de ciclo aumenta en 1 para que el intercambio se realice con el elemento siguiente
            i++;

            // El elemento correspondiente a la variable de ciclo y el comparado intercambian posiciones
            string aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    // El pivote y el elemento correpondiente a donde termine la variable de ciclo intercambian posiciones
    string aux = A[i + 1];
    A[i + 1] = A[r];
    A[r] = aux;

    // Se devuelve i + 1, lo cual acorta el arreglo
    return(i + 1);
}

// || Método Quick Sort ||

/*
    Complejidad de tiempo:

Mejor Caso - n log n / linearítmica
En promedio - n log n / linearítmica
Peor caso - n^2 / cuadrática

    Complejidad de espacio: log n / logarítmica
*/

void sortVector(vector<string> &A, int l, int r)
{
    // Continuan las recursiones mientras que la posición inicial sea menor a la final
    if(l < r)
    {
        /* Los pivotes representan elementos de comparación tanto al inicio como al final
        del arreglo. Todos los elementos terminaran siendo pivotes conforme el arreglo se
        reduce, de esta manera todos los elementos se comparan y quedan ordenados.
        */
        int pivot = particion(A,l,r);

        // Recursiones con pivotes tanto al inicio como al final del arreglo
        sortVector(A,l, pivot - 1);
        sortVector(A, pivot + 1, r);
    }
}


int main(int argc, char* argv[])
{
	string sline;
	int index;

	vector<vector<string>> matriz;
	string meses[12] = {"Jan", "Feb", "Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

	ifstream inFile("bitacora.txt"); 	    //  input file stream
	ofstream outFile("salida.txt");		//	output file stream

	//	Verifica que los archivos se hayan abierto correctamente
	if (inFile.is_open() && outFile.is_open() )
	{	//	Lee linea a linea
		while ( getline(inFile, sline) )
		{

			string numerote;

			// Obtiene mes:
			string line = sline;
			index = line.find(" ");
			string mes = line.substr(0, index);
			numerote += monthToNum(mes, meses);


			//	Obtiene dia
			int index_hora = index + 1;
			line = sline.substr(index_hora);
			index = line.find(" ");
			string dia = line.substr(0, index);

			if(dia.size() > 1)
            {
                index_hora++;
            }
			numerote += addZeros(stoi(dia), 2);


			//	Obtiene hora
			line = sline.substr(index_hora + 2);
			index_hora = line.find(" ");
			string hora = line.substr(0, index_hora);
			numerote += removeDots(hora);


			vector<string> appendedElem = {numerote, line};

			matriz.push_back(appendedElem);
		}
	}

	// guardar en archivo de salida vector ordenado
	for(int i=0; i < matriz.size(); i++)
        outFile << matriz[i][1] << endl;

	inFile.close();
	outFile.close();

	// ordenar vector datos

	vector<string> datos;

	for(int i = 0; i < matriz.size(); i++)
    {
        datos.push_back(matriz[i][0]);
    }

	sortVector(datos, 0, datos.size() - 1);

	/*
	// Código para revisar numerote:
	for(int i = 0; i < matriz.size(); i++)
    {
		string numerote = matriz[i][0];
		string linea = matriz[i][1];
		cout << numerote;
        cout << endl;
    }
    */

    // Código para revisar vector
    for(int i = 0; i < datos.size(); i++)
    {
        cout << datos[i] << endl;
    }
}
