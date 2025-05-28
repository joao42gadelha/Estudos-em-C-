#include <locale>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
   setlocale(LC_ALL, "Portuguese");
   cout << "*****************************************" << endl;
   cout << "*   Bem vindo ao jogo da adivinhação    *" << endl;
   cout << "*****************************************" << endl;

   cout << "Escolha sua dificuldade" << endl;
   cout << "Fácil (F), Médio (M) ou Difícil (D)" << endl;

   char dificuldade;
   cin >> dificuldade;

   int numero_de_tentativas;

   if (dificuldade == 'F')
   {
      numero_de_tentativas = 15;
   }
   if (dificuldade == 'M')
   {
      numero_de_tentativas = 10;
   }
   if (dificuldade == 'D')
   {
      numero_de_tentativas = 5;
   }
   srand(time(NULL));
   const int NUMERO_SECRETO = rand() % 100;

   bool nao_acertou = true;
   int tentativas = 0;

   double pontos = 1000.0;

   for (tentativas = 1; tentativas <= numero_de_tentativas; tentativas++)
   {
      cout << "tentativa " << tentativas << endl;
      int chute;
      cout << "qual é o seu chute?" << endl;
      cin >> chute;

      double pontos_perdidos = abs(chute - NUMERO_SECRETO) / 2.0;
      pontos = pontos - pontos_perdidos;

      cout << "o valor do seu chute ?: " << chute << endl;

      bool acertou = chute == NUMERO_SECRETO;
      bool maior = chute > NUMERO_SECRETO;

      if (acertou)
      {
         cout << "Parabéns, você acertou o número secreto! " << NUMERO_SECRETO << endl;
         nao_acertou = false;
         break;
      }
      else if (maior)
      {
         cout << "O seu chute foi maior que o número secreto!" << endl;
      }
      else
      {
         cout << "O seu chute foi menor que o número secreto!" << endl;
      }
   }

   cout << "Fim de jogo " << endl;

   if (nao_acertou)
   {
      cout << "você perdeu! Tente novamente!" << endl;
   }
   else
   {
      cout << "Você acertou o número secreto em " << tentativas << " tentativas" << endl;
      cout.precision(2);
      cout << fixed;
      cout << "sua pontuação foi de: " << pontos << " pontos." << endl;
   }
}
