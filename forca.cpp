#include <iostream>
#include <string>
#include <locale>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string palavra_secreta = "MELANCIA";

map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char chute)
{
	for (char letra : palavra_secreta)
	{
		if (chute == letra)
		{
			return true;
		}
	}
	return false;
}

bool nao_acertou()
{
	for (char letra : palavra_secreta)
	{
		if (!chutou[letra])
		{
			return true;
		}
	}
	return false;
}

bool nao_enforcou()
{
	return chutes_errados.size() < 5;
}

void imprime_erros()
{
	cout << "Chutes errados: ";
	for (char letra : chutes_errados)
	{
		cout << letra << " ";
	}
	cout << endl;
}

void imprime_cabecalho()
{
	cout << "***********************" << endl;
	cout << "*    JOGO DA FORCA    *" << endl;
	cout << "***********************" << endl;
	cout << endl;
}

void imprime_palavras()
{
	for (char letra : palavra_secreta)
	{
		if (chutou[letra])
		{
			cout << letra << " ";
		}
		else
		{
			cout << "_ ";
		}
	}
	cout << endl;
}

void chuta()
{
	cout << "Seu chute: " << endl;
	char chute;
	cin >> chute;

	chutou[chute] = true;

	if (letra_existe(chute))
	{
		cout << " Você acertou! seu chute está na palavra. " << endl;
	}
	else
	{
		cout << " Você errou! Seu chute não está na palavra." << endl;
		chutes_errados.push_back(chute);
	}
	cout << endl;
}

vector<string> le_arquivo()
{
	ifstream arquivo;
	arquivo.open("palavras.txt");

	int quantidade_palavras;
	arquivo >> quantidade_palavras;

	vector<string> palavras_do_arquivo;

	for (int i = 0; i < quantidade_palavras; i++)
	{
		string palavra_lida;
		arquivo >> palavra_lida;
		palavras_do_arquivo.push_back(palavra_lida);
	}
	return palavras_do_arquivo;
}

void sorteia_palavra()
{
	vector<string> palavras = le_arquivo();

	srand(time(NULL));
	int indice_sorteado = rand() % palavras.size();

	palavra_secreta = palavras[indice_sorteado];
}

void salva_arquivo(vector<string> nova_lista)
{
	ofstream arquivo;
	arquivo.open("palavras.txt");
	if (arquivo.is_open())
	{
		arquivo << nova_lista.size() << endl;

		for (string palavra : nova_lista)
		{
			arquivo << palavra << endl;
		}
		arquivo.close();
	}
	else
	{
		cout << "Não foi possível acessar o banco de palavras. " << endl;
		exit(0);
	}
}

void adiciona_palavra()
{
	cout << "Digite a nova palavra, usando letras maiúsculas." << endl;
	string nova_palavra;
	cin >> nova_palavra;
	vector<string> lista_palavras = le_arquivo();
	lista_palavras.push_back(nova_palavra);

	salva_arquivo(lista_palavras);
}
int main()
{
	imprime_cabecalho();

	le_arquivo();

	sorteia_palavra();

	setlocale(LC_ALL, "portuguese");

	while (nao_acertou() && nao_enforcou())
	{

		imprime_palavras();
		chuta();
	}
	cout << "FIM DE JOGO!" << endl;
	cout << "A palavra secreta era: " << palavra_secreta << endl;
	if (nao_acertou())
	{
		cout << "você perdeu!" << endl;
	}
	else
	{
		cout << "voc acertou a palavra secreta!" << endl;
		cout << "você deseja adicionar uma nova palavra ao banco? (S/N)" << endl;

		char resposta;
		cin >> resposta;

		if (resposta == 'S')
		{
			adiciona_palavra();
		}
	}
}
