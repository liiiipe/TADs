#include <new>
using std::nothrow;

template <typename T>
struct Conjunto{
	struct noh{
		T elem; // campo para o elemento
		noh *ant, *prox; // campo para os ponteiros que apontam para o anterior e posterior
	};
	noh *prim; // ponteiro pqu irá apontar para o primeiro
	void inicializar(){
		prim = nullptr;
	}
	bool vazio(){
		return prim == nullptr;
	}
	struct Iterador{
		noh *n;
		// operadores do iterador
		bool operator!=(const Iterador &i){return n != i.n;}
		bool operator==(const Iterador &i){return n == i.n;}
		T operator*(){return n->elem;}
		void operator++(){n = n->prox;}
	};
	Iterador Fazer_it(noh *p){ // funçao de fazer iterador, evita repetição de codigo
		Iterador i; // cria o iterador
		i.n = p; // iterador recebe o noh passado por argumento
		return i; // retorna o iterador
	}
	Iterador fim(){return Fazer_it(nullptr);} // retorna um iterador pro fim
	Iterador inicio(){return Fazer_it(prim);} // retorna um iterador pro inicio
	Iterador inserir(T e){
		noh *n = new(nothrow) noh; // crio e aloco o novo noh 
		if(n == nullptr){return fim();} // teste de alocação
		n->elem = e; // campo elem de n recebe o elemento
		n->ant = nullptr; // campo ant de n aponta para nullptr
		n->prox = prim; // campo prox de n recebe prim, o caso de estar vazia ja esta resolvido, pois o prim sera nulo
		if(prim != nullptr){prim->ant = n;} // se nao estiver vazia, acerto o campo prox de prim, apontando para o novo noh
		prim = n; // acerto o ponteiro prim apontando para o novo noh
		return Fazer_it(n); // faço um iterador do novo noh e retorno ele
	}
	Iterador pertence(T e){
		/* para saber se o elemento pertence ao conjunto, um for de n (um ponteiro auxiliar declarado dentro do for apontando para o prim)
		enquanto n for diferente de nulo, n vai passando pro proximo */
		for(noh *n = prim; n != nullptr; n = n->prox){
			if(n->elem == e){return Fazer_it(n);} // se o campo elem de n for o elemento, faço e retorno o iterador
		}
		return fim(); // se acabar o laço e chegar até aq, o elemento não pertente, retorno um iterador pro fim
	}
	void remover(Iterador i){
		noh *p = i.n; // ponteiro auxiliar para o iterador
		if(p->prox != nullptr){ // se o campo prox de p for diferente de nulo
			p->prox->ant = p->ant; // o campo prox de p e o anterior recebe o noh q o campo ant esta apontando 
		}
		if(p->ant != nullptr){ // se o campo ant de p for diferente de nulo
			p->ant->prox = p->prox; // o campo ant de p e o proximo recebe o noh q o campo prox esta apontando 
		}
		else{
			prim = p->prox; // 
		}
		delete p; // desalocando o iterador
	}
	void terminar(){
		while(prim != nullptr){
			// enquanto o prim for diferente de nulo, crio um ponteiro auxiliar 'n' e faço o 'prim' ir pro prox
			noh *n = prim; // crio um ponteiro auxiliar
			prim = prim->prox; // quando chegar no ultimo noh da "direita" o seu campo prox apontara para nulo, saindo do while
			delete n; // desaloco o ponteiro auxiliar
		}
	}
};
