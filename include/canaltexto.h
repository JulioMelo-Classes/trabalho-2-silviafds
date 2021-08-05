#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "Mensagem.h"
using namespace std;

class CanalTexto{
	private:
		string nome;
		vector<Mensagem> mensagens;

	public:
		string getNomeCanal();
		void setNomeCanal(string nome_do_canal);
};

#endif
