#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "Mensagem.h"
using namespace std;

class CanalTexto{
	private:
		string nome;
		vector<Mensagem> mensagens; //não pode haver get e set

	public:
		string getNomeCanal();
		void setNomeCanal(string nome_do_canal);
		void enviarMensagens(string data_hora, int id_remetente, string conteudo_da_mensagem);
		void listarMensagens(string nome);
};

#endif
