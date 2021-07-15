#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <vector>
#include <string>
#include "canaltexto.h"
using namespace std;
class Servidor{
	private:
		int usuarioDonold;//id do usuário que criou o servidor
		string nome;
		string descricao;
		string codigoConvite;
		vector<CanalTexto> canaisTexto;
		vector<int> participantesIDs;
};

#endif
