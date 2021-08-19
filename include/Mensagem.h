#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>
using namespace std;

/*
cp2 ok
*/
class Mensagem{
	private:
		string dataHora; // string que armazena a data e a hora que um(a) usuário(a) enviou uma mensagem.
        int enviadaPor; // armazena o id da pessoa que enviou a mensagem.
        string conteudo; // armazena o conteúdo da mensagem.

    public:

        /*! 
        * @brief método implementado para acessar o atributo de data e hora que uma mensagem foi enviada. 
        *
        * @return o atributo de data e hora.
        */
        string getData_hora();

        /*! 
        * @brief método implementado para acessar o atributo de data e hora que uma mensagem foi enviada e fazer com que esse atributo seja modificado. 
        * @param data_e_hora atributo do tipo string que armazena a data e a hora que uma mensagem foi enviada. 
        */
        void setData_hora(string data_e_hora);

        /*! 
        * @brief método implementado para acessar o atributo que armazena o id do(a) usuário(a) que enviou uma mensagem para determinado canal. 
        *
        * @return o atributo que armazena o id do(a) usuário(a).
        */
        int getEnviadaPor();

        
        /*! 
        * @brief método implementado para acessar o atributo que armazena o id que enviou uma mensagem e fazer com que esse atributo seja modificado. 
        *
        * @param id_que_enviou atributo do tipo int que armazena o id do(a) usuário(a) que enviou determinada mensagem.
        */
        void setEnviadaPor(int id_que_enviou);

        /*! 
        * @brief método implementado para acessar o atributo que armazena a mensagem a ser enviada para determinado canal. 
        *
        * @return o atributo que armazena a mensagem.
        */
        string getConteudo();

        /*! 
        * @brief método implementado para acessar o atributo que armazena a mensagem que vai ser enviada e modifica esse atributo.
        *
        * @param conteudo_mensagem atributo do tipo string que armazena a mensagem enviada.
        */
        void setConteudo(string conteudo_mensagem);


};
#endif
