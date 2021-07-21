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
		Servidor(int id, string nome_servidor){
			usuarioDonold = id;
			nome = nome_servidor;	
				
		}

		int getID(){
			return usuarioDonold;
		}

		string getNome_servidor(){
			return nome;
		}
		
		Servidor(string desc){
			descricao = desc;
		}

		string getDescricao(){
			return descricao;
		}

};

#endif
