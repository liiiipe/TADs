#include <new>
using std::nothrow;

template <typename T>
struct Deque{
	struct noh{
		T elem; // campo para armazenar o elemento
		noh ant; // campo para apontar pro anterior
		noh prox; // campo para apontar pro proximo
	};
	noh *E, *D; // ponteiro para a esquerda e direita do deque
	void inicializar(){
		E = nullptr; // inicializo apenas um ponteiro, o outro n�o importa
	}
	bool vazia(){
		return E == nullptr; // vai retornar true caso o E volte a forma que foi inicializada
	}
	bool inserir_esq(T e){
		noh *n = new(nothrow) noh; // aloca��o de novo n�
		if(n == nullptr){return true;} // teste de aloca��o
		n->elem = e; // campo elem do novo n� recebe o elemento
		n->ant = nullptr; // campo ant do novo n� aponta pra nulo, ja que ele vai ser a extremidade esquerda
		if(vazia())
			{D = n;} // se tiver vazia o ponteiro D aponta pro novo n�, observe que logo depois o E tambem apontara pro n
		else
			{E->ant = n;} // se n�o tiver vazia, o campo ant apontado pelo ponteiro E aponta para o novo n�
		E = n; // depois da inser��o pela esquerda, o ponteiro E aponta para o novo n�
		return false;
	}
	bool inserir_dir(T e){
		noh *n = new(nothrow) noh;
		if(n == nullptr){return true;}
		n->elem = e;
		n->prox = nullptr; // campo prox do novo n� aponta pra nulo, ja que ele vai ser a extremidade direita
		if(vazia())
			{E = n;} // se tiver vazia o ponteiro E aponta pro novo n�, observe que logo depois o D tambem apontara pro n
		else
			{D->prox = n;} // se n�o tiver vazia, o campo prox apontado pelo ponterio D aponta para o novo n�
		D = n; // depois da inser��o pela direita, o ponteiro D aponta para o novo n�
		return false;
	}
	T remover_esq(){
		T e = E->elem; // variavel "e" recebe o elemento que esta no campo elem apontado pelo ponteiro E
		noh *n = E; // ponteiro n auxiliar, que aponta para onde E est� apontando
		E = E->prox; // agora E aponta para onde o campo prox apontado pelo ponteiro E esta apontando 
		delete n; // deleto o ponteiro auxilar que est� apontando para onde o E estava
		return e; // retorno o elemento removido
	}
	T remover_dir(){ // analoga a remover_esq
		T e = D->elem;
		noh *n D;
		D = D->ant;
		delete n;
		return e;
	}
	void terminar(){ 
		while(!vazia){ 
		/* enquanto nao estiver vazia, vou remover pela esquerda ate chegar na extremidade direita
		   quando chegar no ultimo elemento, E ir� ficar nulo e consequentemente vazia */				
			remover_esq();
		}
	}
};
