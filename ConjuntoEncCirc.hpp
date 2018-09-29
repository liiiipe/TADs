#include <new>
using std::nothrow;

template <typename T>
struct Conjunto{
	struct noh{
		T elem;
		noh *ant;
		noh *prox;
	};
	noh *prim;
	noh *sentinela;
	bool inicializar(){
		noh *n = new(nothrow) noh;
		if(n == nullptr){return true;}
		prim = sentinela = n;
		return false;
	}
	bool vazio(){
		return prim == sentinela;
	}
	struct Iterador{
		noh *n;
		bool operator!=(const Iterador &i){return n != i.n;}
		bool operator==(const Iterador &i){return n == i.n;}
		T operator*(){return n->elem;}
		void operator++(){return n->prox;}
	};
	Iterador Fazer_it(noh *p){
		Iterador i;
		i.n = p;
		return i;
	}
	Iterador fim(){
		return Fazer_it(sentinela);
	}
	Iterador inicio(){
		return Fazer_it(prim);
	}
	Iterador inserir(T e){
		noh *n = new(nothrow) noh;
		if(n == nullptr){return fim();}
		n->elem = e;
		sentinela->prox = n;
		n->ant = sentinela;
		n->prox = prim;
		prim->ant = n;
		prim = n;
		return Fazer_it(n);
	}
	Iterador pertence(T e){
		sentinela->elem = e;
		noh *n = prim;
		while(n->elem != e){
			n = n->prox;
		}
		if(n != sentinela){
			return Fazer_it(n);
		}
		return fim();
	}
	void remover(Iterador i){
		noh *n = i.n;
		if(n == prim){
			prim = n->prox;
		}
		n->ant->prox = n->prox;
		n->prox->ant = n->ant;
		delete n;
	}
	void terminar(){
		while(prim != sentinela){
			noh *n = prim; 
			prim = n->prox;
			delete n;
		}
	}
};
