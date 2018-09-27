#include <new>
using std::nothrow

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
		bool operato!=(const Iterador &i){return n != i.n;}
		bool operato==(const Iterador &i){return n == i.n;}
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
		if(i.n == prim){
			// se elemento estiver no inicio "extremidade esquerda" que esta apontada pelo ponteiro prim
			prim = prim->prox; // prim recebe o campo prox
			prim->ant = nullptr; // o campo ant desse novo noh que prim esta apontando recebe nulo
		}
		else{
			// esse else abrange dois possiveis casos, do elemento esta no meio ou na "extremidade direita"
			// primeira linha pode vir aq
			p = p->ant; // o ponteiro auxiliar vai pro anterior
			p->prox = i.n->prox; // o campo prox do noh apontando por p recebe o campo prox apontado pelo iterador
			p = i.n; // ponteiro p volta a apontar para o i.n, pra ser desalocado junto
		}
		delete i.n; // desalocando o iterador
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
