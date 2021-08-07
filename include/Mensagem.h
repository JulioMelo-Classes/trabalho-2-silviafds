#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>
using namespace std;

class Mensagem{
	private:
		string dataHora;
        int enviadaPor;
        string conteudo;

    public:
        string getData_hora();
        void setData_hora(string data_e_hora);
        int getEnviadaPor();
        void setEnviadaPor(int id_que_enviou);
        string getConteudo();
        void setConteudo(string conteudo_mensagem);


};
#endif
