#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "Mensagem.h"
using namespace std;

class CanalTexto{
	public:
		string nome;
		vector<Mensagem> mensagens;
};

#endif