#include <new>
using std::nothrow;
 template <typename T>
struct Fila{
	struct noh{
		T elem;
		noh *prox;
	};
	noh *I, *F;
	void inicializar(){
		I = nullptr;
	}
	bool vazia(){
		return I == nullptr;
	}
	bool enfilar(T e){
		noh *n = new(nothrow) noh;
		if(n == nullptr){return true;}
		n->elem = e;
		n->prox = nullptr;
		if(vazia())
			{I = n;}
		else
			{F->prox = n;}
		F = n;
		return false;
	}
	T desenfilar(){
		T e = I->elem;
		noh *n = I;
		I = I->prox;
		delete n;
		return e;
	}
	void terminar(){
		while(!vazia()){
			desenfilar();
		}
	}
};
