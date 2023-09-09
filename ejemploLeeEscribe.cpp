#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <fstream>
#include <string.h>

using namespace std;

string addZeros(int num, int desired_length){
	string base = "";
	for(int i=0; i < (desired_length - to_string(num).length()); i++){
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
	string resultado = "";
	// TO-DO eliminar ":" de hora, y regresar	string con ese formato

	return addZeros(stoi(resultado), 6);
}

void sortVector(vector<vector<string>> *datos){
	// TO-DO ordenar vector datos, usando datos[i][0] como número a ordenar
}

int main(int argc, char* argv[])
{
	string sline;
	int index;

	vector<vector<string>> datos;
	string meses[12] = {"Jan", "Feb", "Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};


	ifstream inFile("bitacora2.txt"); 	    //  input file stream
	ofstream outFile("salida2.txt");		//	output file stream

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
			line = sline.substr(index+1);
			index = line.find(" ");
			string dia = line.substr(0, index);
			numerote += addZeros(stoi(dia), 2);  

			//	Obtiene hora 
			line = sline.substr(index+1);
			index = line.find(" ");
			string hora = line.substr(0, index);
			numerote += removeDots(hora);

			vector<string> appendedElem = {numerote, line};

			datos.push_back(appendedElem);
		}
	}

	// ordenar vector datos
	sortVector(datos);

	// guardar en archivo de salida vector ordenado
	for(int i=0; i<datos.size(); i++){
		outFile << datos[i][1] << endl;
	}

	inFile.close();
	outFile.close();

	/*
	// Código para revisar numerote: 
	for(int i = 0; i < datos.size(); i++)
    {
		string numerote = datos[i][0];
		// string linea = datos[i][1];
		cout << numerote;
        cout << endl;
    }
	*/
}
