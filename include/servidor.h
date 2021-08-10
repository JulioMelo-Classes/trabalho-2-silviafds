#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <vector>
#include <string>
#include "canaltexto.h"
#include "Mensagem.h"
#include "usuario.h"
using namespace std;

class Servidor{
	private:
		int usuarioDonold;//id do usuário que criou o servidor.
		string nome; //nome do servidor.
		string descricao; //descrição do servidor.
		string codigoConvite; //código de convite do servidor.
		vector<CanalTexto> canaisTexto; // vector que armazena os canais criados.
		//não pode ter get e set
		vector<int> participantesIDs; //vector que armazena o id dos(a) usuários(a) de um servidor.
		//não pode ter get e set

	public:
	
		/*! 
		* @brief método implementado para acessar o atributo do ID do(a) usuário(a). 
		*
		* @return o atributo do ID do(a) usuário(a).
		*/
		int getID();

		/*! 
		* @brief método implementado para acessar o atributo do ID do(a) usuário(a) e fazer com que esse atributo seja modificado.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*/
		void setID(int id);

		/*! 
		* @brief método implementado para acessar o atributo de nome do servidor. 
		*
		* @return o atributo de nome do servidor.
		*/
		string getNome_servidor();

		
		/*! 
		* @brief método implementado para acessar o atributo de nome do servidor e fazer com que esse atributo seja modificado.
		*
		* @param nome_servidor atributo do tipo string que armazena o nome do servidor que o(a) usuário(a) vai acessar. 
		*/
		void setNome_servidor(string nome_servidor);

		/*! 
		* @brief método implementado para acessar o atributo de descrição de um servidor específico. 
		*
		* @return o atributo de descrição do servidor.
		*/
		string getDescricao();

		/*! 
		* @brief método implementado para acessar o atributo de descrição de um servidor específico e fazer com que esse atributo seja modificado. 
		*
		* @param descricao_servidor atributo do tipo string que armazena a descrição de um servidor específico.
		*/
		void setDescricao(string descricao_servidor);

		/*! 
		* @brief método implementado para acessar o atributo de código de um convite de um servidor específico. 
		*
		* @return o atributo de código de convite do servidor.
		*/
		string getCodigoConvite();

		/*! 
		* @brief método implementado para acessar o atributo de código de convite de um servidor específico e fazer com que esse atributo seja modificado. 
		*
		*  @param codigo_convite atributo do tipo string que armazena o código de convite de um servidor específico. 
		*/
		void setCodigoConvite(string codigo_convite);

		/*! 
		* @brief método implementado para preencher o vetor que contém os IDs dos(as) participantes de determinado servidor. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*/
		void adicionarParticipantes(int id);

		/*! 
		* @brief método implementado para verificar se um(a) participante está em determinado servidor. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* 
		* @return true se o id verificado estiver em determinado servidor e false caso contrário.
		*/
		bool verificarParticipante(int id);

		/*! 
		* @brief método implementado para excluir um(a) participante do vetor que contém os IDs dos(as) participantes de determinado servidor. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*/
		void excluirParticipante(int id);

		/*! 
		* @brief método implementado para mostrar os(a) participantes de um determinado servidor. 
		*
		* @param usuarios atributo vector do tipo da classe Usuario que contém todos os usuários criados.
		*/
		void mostrarParticipantes(vector<Usuario>& usuarios);

		/*! 
		* @brief método implementado para criar canais em determinado servidor. 
		*
		* @param nome_do_canal atributo do tipo string que armazena o nome do canal que o(a) usuário(a) quer criar.
		* 
		* @return false se encontrar um canal com aquele nome e true caso contrário.
		*/
		bool criarCanais(string nome_do_canal);

		/*! 
		* @brief método implementado para mostrar os canais de um determinado servidor. 
		*/
		void mostrarCanais();

		/*! 
		* @brief método implementado para verificar se um canal específico existe dentro de um determinado servidor. 
		*
		* @param nome_entrar_canal atributo do tipo string que armazena o nome do canal que o(a) usuário(a) quer entrar.
		* 
		* @return true se encontrar o nome do canal e false caso contrário.
		*/
		bool verificarCanais(string nome_entrar_canal);

		/*! 
		* @brief método implementado para verificar se existe o canal que o(a) usuário(a) quer enviar uma mensagem. 
		*
		* @param data_hora atributo do tipo string que armazena a data e a hora da mensagem a ser enviada.
		* @param id_remetente atributo do tipo int que armazena o id do(a) usuário(a) que está tentando enviar a mensagem.
		* @param conteudo_da_mensagem atributo do tipo string que armazena a mensagem a ser enviada.
		* @param canal_n atributo do tipo string que armazena o canal para o qual a mensagem será enviada.
		*/
		void percorrerCanais(string data_hora, int id_remetente, string conteudo_da_mensagem, string canal_n);

		/*! 
		* @brief método implementado para listar as mensagens de um canal específico. 
		*
		* @param usuarios atributo vector do tipo da classe Usuario que contém todos os usuários criados.
		* @param canal_visto atributo do tipo string que armazena o nome do canal que está sendo visualizado pelo(a) usuário(a).
		* @param id atributo do tipo int que armazena o id do(a) usuário(a) que enviou a mensagem.
		*/
		void listarMensagensCanais(vector<Usuario>& usuarios, int id);


};

#endif
