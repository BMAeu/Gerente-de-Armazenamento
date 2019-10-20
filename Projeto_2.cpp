// Projeto_2.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;



void INSERT() {
	cout << "Insira as linhas que voce quer adicionar" << endl;
	cout << "Separe os campos com as devidas separacoes, seja ',' '|' ou outros" << endl;
	string dado;
	vector<string> v;
	getline(cin, dado);
	v.push_back(dado);
	while (getline(cin, dado)) {
		if (dado.empty()) { break; }
		v.push_back(dado);
	}
	vector<string>::iterator it;

	ofstream teste;
	teste.open("teste.csv", ios::binary|ios::app);
	for (it = v.begin()+1; it != v.end(); it++) {
		teste << *it << '\n';
	}
	teste.close();
	cout << "Registros inseridos";
}

void DELETE() {

	fstream teste, temp;
	string delet, val_delet;
	vector<string>row;
	string linha, campo, k;
	char separador;
	cout << "Qual o separador do arquivo?" << endl;
	cin >> separador;
	teste.open("teste.csv", ios::binary | ios::in);
	temp.open("temp.csv", ios::binary | ios::app);
	cout << "Qual campo voce vai querer especificar o valor a ser deletado?" << endl;

	getline(teste, linha);
	stringstream s(linha);
	while (getline(s, campo, separador)) {
		row.push_back(campo);
		int i = row.size();
		cout << row[i - 1] << endl;
	}
	temp << linha << '\n';

	cout << "Escreva como aparece na tela" << endl;
	cin >> delet;
	cout << "Qual valor do campo?" << endl;
	cin >> val_delet;

	vector<string>::iterator it = std::find(row.begin(), row.end(), delet);
	int num = distance(row.begin(), it);               //posicao do valor a ser procurado para usar no vetor
	int tamanho = row.size();
	if (num == tamanho) {
		num = num - 1;
	}

	while (!teste.eof()) {
		row.clear();
		getline(teste, linha);
		stringstream s(linha);
		while (getline(s, campo, separador)) {
			row.push_back(campo);
		}
		int row_size = row.size();

		if (teste.eof()) {
			break;
		}
		if (row[num] != val_delet) {
			if (!teste.eof()) {
				temp << linha << "\n";
			}
		}
	}

	teste.close();
	temp.close();
	remove("teste.csv");
	rename("temp.csv", "teste.csv");

	cout << "Registros deletados";
}

void SELECT() {
	fstream teste, select;
	string selec, val_selec, linha, campo, k, campos_selec;
	vector<string>row;
	char separador, SouN;

	teste.open("teste.csv", ios::binary | ios::in);        //Abre os arquivos a serem usados
	select.open("select.csv", ios::binary | ios::app);

	cout << "Qual separador usado no arquivo(',' '|' ou outro)?" << endl;
	cin >> separador;
	cout << "Qual ou quais campo(s) voce vai querer selecionar?" << endl;

	getline(teste, linha);
	stringstream s(linha);
	while (getline(s, campo, separador)) {
		row.push_back(campo);
		int i = row.size();
		cout << row[i - 1] << endl;                         //mostrar os campos do arquivo  
	}                            
	

	cout << "Escreva como aparece na tela, e entre 0 quando terminar" << endl;

	vector<string> campos;
	while (std::cin >> campos_selec && campos_selec != "0") {
		campos.push_back(campos_selec);                              //pegar os campos desejados
	}

	int tam_campos = campos.size();

	if (tam_campos == 1) {                                         //checar a quantidade de campos desejados
		cout << "Vai querer especificar valor (S/N)?" << endl;
		cin >> SouN;
		if (SouN == 'S' || SouN == 's') {
			cout << "Qual valor do campo?" << endl;
			cin >> val_selec;

			vector<string>::iterator it = std::find(row.begin(), row.end(), campos[0]);
			int num = distance(row.begin(), it);               //posicao do valor a ser procurado para usar no vetor
			int tamanho = row.size();
			if (num == tamanho) {
				num = num - 1;
			}

			select << linha << endl;

			while (!teste.eof()) {
				row.clear();
				getline(teste, linha);
				stringstream s(linha);
				while (getline(s, campo, separador)) {
					row.push_back(campo);
				}
				int row_size = row.size();

				if (teste.eof()) {
					break;
				}
				if (row[num] == val_selec) {
					if (!teste.eof()) {
						select << linha << "\n";
					}
				}
			}

			teste.close();
			select.close();
		}
		if (SouN == 'N' || SouN == 'n') {
			vector<string>::iterator it = std::find(row.begin(), row.end(), campos[0]);
			int num = distance(row.begin(), it);               //posicao do valor a ser procurado para usar no vetor
			int tamanho = row.size();
			if (num == tamanho) {
				num = num - 1;
			}

			select << row[num] << endl;

			while (!teste.eof()) {
				row.clear();
				getline(teste, linha);
				stringstream s(linha);
				while (getline(s, campo, separador)) {
					row.push_back(campo);
				}
				int row_size = row.size();

				if (teste.eof()) {
					break;
				}
				if (!teste.eof()) {
					select << row[num] << "\n";
				}
			}

			teste.close();
			select.close();
		}

	}
	else {
		vector<int> indices;
		for (int i = 0; i < tam_campos; i++) {
			vector<string>::iterator it = std::find(row.begin(), row.end(), campos[i]);
			int num = distance(row.begin(), it);
			int tamanho = row.size();
			if (num == tamanho) {
				num = num - 1;
			}
			indices.push_back(num);
		}

		for (int i = 0; i < tam_campos; i++) {
			int num = indices[i];
			select << row[num] << ',';
		}
		select << '\n';

		while (!teste.eof()) {
			row.clear();
			getline(teste, linha);
			stringstream s(linha);
			while (getline(s, campo, separador)) {
				row.push_back(campo);
			}
			int row_size = row.size();

			if (teste.eof()) {
				break;
			}
			for (int i = 0; i < tam_campos; i++) {
				int num = indices[i];
				select << row[num] << ',';
			}
			select << '\n';
		}

		teste.close();
		select.close();
	}
	cout << "Abra a pasta select.csv para ver os resultados";
}

int main()
{
	string escolha;
	cout << "O padrao deste programa esta com o arquivo DOCENTES_SUDESTE.csv, para mudar use find and replace no codigo e mude todas as entradas de DOCENTES_SUDESTE para o nome do arquivo desejado" << endl;
	cout << "Voce quer:\nINSERT \nDELETE \nSELECT \n";
	cin >> escolha;
	if (escolha == "INSERT" || escolha == "insert" ) { 
		INSERT(); 
	}
	if (escolha == "DELETE" || escolha == "delete") { 
		DELETE(); 
	}
	if (escolha == "SELECT" || escolha == "select") { 
		SELECT(); 
	}

	return 0;
}


