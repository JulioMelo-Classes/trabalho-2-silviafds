#ifndef SISTEMA_H
#define SISTEMA_H
#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "usuario.h"
#include "servidor.h"
#include "canaltexto.h"


// Sistema deve concentrar todas as operações do Concordo
class Sistema {
	private:
		std::vector<Servidor> servidores; // um vetor com todos os servidores do sistema.
		std::vector<Usuario> usuarios; // um vetor com todos os usuários cadastrados.
		std::map< int, std::pair<std::string, std::string> > usuariosLogados; //<! um vetor contendo os usuários que logaram no sistema		

	public:
		vector<int> id_usuario; // vector que armazena os ids dos(as) usuários(as).
		vector<string> email_validos; // vector que contém os e-mail cadastrados.
		std::vector<Usuario> validar_email; // vector que verifica se o e-mail está válido.

		/*! Encerra o funcionamento do Concordo, o programa termina ao executar este comando.
				@return uma string com a mensagem "Saindo.."
		*/
		std::string quit();

		/*! 
		* @brief Método implementado para criar um(a) usuário(a). 
		*
		* @param email atributo do tipo string que armazena o e-mail correspondente ao/à usuário(a).
		* @param senha atributo do tipo string que armazena a senha correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao/à usuário(a).
		*
		* @return uma string contendo uma mensagem de erro caso o(a) usuário(a) já tenha sido criado(a) ou "Usuário(a) criado(a)."
		*/
		std::string create_user (const std::string email, const std::string senha, const std::string nome);

		/*! 
		* @brief Método implementado para realizar o login de um(a) usuário(a) no sistema. 
		*
		* @param email atributo do tipo string que armazena o e-mail correspondente ao/à usuário(a).
		* @param senha atributo do tipo string que armazena a senha correspondente ao/à usuário(a).
		*
		* @return uma string contendo a mensagem de erro: "Senha ou usuário inválidos." caso seja necessário e, caso não, retorna "Logado como <email>".
		* 
		*/
		std::string login(const std::string email, const std::string senha);

		/*! 
		* @brief Método implementado para desconectar um(a) usuário específico do sistema. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*
		* @return uma string contendo uma mensagem de erro para caso o(a) usuário(a) não esteja conectado(a) ou "Desconectando usuário <email>" caso esteja conectado(a). 
		*
		*/
		std::string disconnect(int id);

		/*! 
		* @brief Função na qual cria um servidor. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao servidor a ser criado.
		*
		* @return uma string contendo uma mensagem de erro caso já exista um servidor com esse nome ou o(a) usuário(a) não esteja logado(a) e uma string contendo "Servidor <nome> criado." caso não haja nenhum erro.
		*/
		std::string create_server(int id, const std::string nome);
		
		/*! 
		* @brief método implementado para modificar a descrição do servidor passado como parâmetro. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome do servidor.
		* @param descricao atributo do tipo string que armazena a nova descrição dada pelo(a) usuário(a).
		*
		* @return string contendo uma mensagem de erro caso o servidor passado como parâmetro não exista, uma mensagem de erro caso o(a) usuário(a) não esteja logado(a), uma mensagem de erro caso o id passado como parâmetro não seja dono(a) do servidor e "Descrição do servidor <nome> modificada!" caso não haja nenhum erro.
		*/
		std::string set_server_desc(int id, const std::string nome, const std::string descricao);

		/*! 
		* @brief método implementado para modificar o código de convite de um servidor específico. 
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao servidor que a pessoa quer alterar o código.
		* @param codigo atributo do tipo string que armazena o código de convite a ser alterado.
		*
		* @return "Código de convite do servidor <nome> modificado com sucesso" caso não haja erros e, caso haja, serão retornadas strings contendo mensagens de erro caso o(a) usuário(a) não esteja logado(a), caso o(a) usuário(a) não seja o(a) dono(a), caso o código seja removido, e caso o servidor não exista.
		*/
		std::string set_server_invite_code(int id, const std::string nome, const std::string codigo);

		/*! 
		* @brief método que lista todos os servidores que estão cadastrados no sistema.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*
		* @return uma string vazia ou uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string list_servers(int id);
	
		/*! 
		* @brief Função que remove um servidor
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome  correspondente ao servidor.
		*
		* @return "Servidor <nome> removido com sucesso." todas as validações sejam cumpridas; caso contrário, serão retornadas mensagens de erro se o(a) usuário(a) não for dono(a) do servidor, bem como se não estiver logado(a) e caso o servidor não seja encontrado.
		*/
		std::string remove_server(int id, const std::string nome);

		/*! 
		* @brief método que faz com que o(a) usuário(a) entre em um servidor.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao servidor.
		* @param codigo atributo do tipo string que armazena o código de convite para entrar no sistema.
		*
		* @return "Entrou no servidor <nome> com sucesso" caso todas as validações sejam cumpridas; ou mensagens de erro para caso o(a) usuário(a) não forneça o código de acesso, caso o código de acesso fornecido estiver incorreto e caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string enter_server(int id, const std::string nome, const std::string codigo);

		/*! 
		* @brief método que faz com que o(a) usuário(a) saia de um servidor em que esteja conectado(a).
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao servidor.
		*
		* @return "Saindo do servidor <nome>." caso todas as validações sejam cumpridas; ou mensagens de erro para caso o(a) usuário(a) não esteja logado(a) ou tampouco conectado(a) a algum servidor.
		*/
		std::string leave_server(int id, const std::string nome);

		/*! 
		* @brief método que lista os participantes que estão presentes no servidor que o(a) usuário(a) passado como parâmetro - através do id - está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*
		* @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string list_participants(int id);

		/*! 
		* @brief método que lista os canais do servidor que o usuário pertencente àquele id está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* 
		* @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string list_channels(int id);

		/*! 
		* @brief método que cria um canal no servidor em que o(a) usuário(a) está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao canal a ser criado.
		*
		* @return "Canal <nome> criado." caso todas as validações sejam cumpridas e mensagens de erro caso o(a) usuário(a) não esteja logado(a), caso um canal de texto com o nome passado já exista ou caso o(a) usuário(a) não esteja visualizando nenhum servidor.
		*/
		std::string create_channel(int id, const std::string nome);
		
		/*! 
		* @brief método que faz com que o(a) usuário(a), correspondente ao id, entre em um canal específico.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param nome atributo do tipo string que armazena o nome correspondente ao canal que o(a) usuário(a) irá entrar.
		*
		* @return "Entrou no canal <nome>" caso todas as validações sejam cumpridas ou mensagens de erro caso o canal não exista ou o(a) usuário(a) não esteja logado(a).
		*/
		std::string enter_channel(int id, const std::string nome);

		/*! 
		* @brief método que faz com que o(a) usuário(a) passado como parâmetro seja retirado do canal que está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*
		* @return "Saindo do canal <nome>" caso todas as validações sejam cumpridas ou mensagens de erro caso o(a) usuário(a) não esteja visualizando o canal ou não esteja logado(a).
		*/
		std::string leave_channel(int id);
		
		/*! 
		* @brief método que envia uma mensagem para o canal que o(a) usuário(a) passado(a) como parâmetro está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		* @param mensagem atributo do tipo string que armazena a mensagem a ser enviada ao canal.
		*
		* @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string send_message(int id, const std::string mensagem);
		
		/*! 
		* @brief método que lista todas as mensagens do canal que o(a) usuário(a) passado(a) como parâmetro está visualizando.
		*
		* @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
		*
		* @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
		*/
		std::string list_messages(int id);
};

#endif
