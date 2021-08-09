#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "Mensagem.h"
using namespace std;

class CanalTexto{
	private:
		string nome; //nome do canal que foi criado pelo(a) usuário(a).
		vector<Mensagem> mensagens; //vector com mensagens que foram enviadas no canal.

	public:
	
		/*! 
		* @brief método implementado para acessar o atributo que armazena o nome do canal a ser acessado para realizar implementações. 
		*
		* @return o atributo que armazena o nome do canal.
		*/
		string getNomeCanal();

		/*! 
		* @brief método implementado para acessar o atributo que armazena o nome do canal a ser acessado para realizar implementações e modifica esse atributo.
		* @param nome_canal atributo do tipo string que armazena o nome do canal. 
		*/
		void setNomeCanal(string nome_do_canal);

		/*! 
		* @brief método implementado para preencher o vector que contém as informações - data e hora, quem enviou e o conteúdo da mensagem - das mensagens enviadas aos canais. 
		*
		* @param data_hora atributo do tipo string que armazena a data e a hora da mensagem enviada.
		* @param id_remetente atributo do tipo int que armazena o id do(a) usuário(a) que enviou a mensagem.
		* @param conteudo_da_mensagem atributo do tipo string que armazena a mensagem a ser enviada.
		*/
		void enviarMensagens(string data_hora, int id_remetente, string conteudo_da_mensagem);

		/*! 
		* @brief método implementado para mostrar as mensagens que foram enviadas para determinado canal.
		*
		* @param nome_usuario atributo do tipo string que armazena o nome do(a) usuário(a) que enviou a mensagem.
		*/
		void listarMensagens(string nome, int id);
};

#endif
