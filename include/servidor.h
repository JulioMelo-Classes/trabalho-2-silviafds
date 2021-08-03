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
		vector<CanalTexto> canaisTexto; //não pode ter get e set
		vector<int> participantesIDs; //não pode ter get e set

	public:
		int getID();
		void setID(int id);
		string getNome_servidor();
		void setNome_servidor(string nome_servidor);
		string getDescricao();
		void setDescricao(string descricao_servidor);
		string getCodigoConvite();
		void setCodigoConvite(string codigo_convite);
		void adicionarParticipantes(int id);
		void testarParticipantes(string name);
		bool verificarParticipante(int id);
		void excluirParticipante(int id);
};

#endif
