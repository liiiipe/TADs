template <typename T>
struct Deque{
	T *I, *F, *E, *D; 
	// Ponteiro I para o inicio do vetor, F para o fim, E para o ultimo elemento da esquerda e D para o da direita.
	int tamanho, contador;
	// Variaveis para saber o tamanho atual do vetor e quantos elementos possui, para auxiliar na hora da alocação de memoria.
};

#include <new>
using std::nothrow;

template <typename T>
bool inicializar(Deque<T> &D)
{
	/* inicializa o vetor de tamanho 1, os ponteiros apontando para nullptr e as variaveis inteiras. */ 
	if(D.I = new(nothrow) T[1])
	{
		D.F = D.I;
		D.E = nullptr;
		D.D = nullptr;
		D.tamanho = 1;
		D.contador = 0; // n
		return false;
	}
	else {
		return true;
	}
}

template <typename T>
void terminar(Deque<T> &D)
{
	/* desaloca o vetor e termina */
	delete[] D.I;
}

template <typename T>
bool vazio(Deque<T> &D)
{
	/* retorna se esta vazia ou nao */
	return ((D.E == nullptr) && (D.D == nullptr));
}

template <typename T>
bool cheia(Deque<T> &D)
{
	/* funçao auxiliar que retorna se o vetor esta cheio para faz a alocaçao do novo vetor*/
	if(D.contador == D.tamanho) /* cada remoçao ou inserçao eh registrada no contador, e o tamanho guarda o tamanho do vetor a cada nova alocaçao  */
	{
		return true;
	}
	return false;
}

template <typename T>
bool inserir_esq(Deque<T> &D, T e)
{
	if(vazio(D))
	{
		D.E = D.D = D.I; /* se o deque estiver vazio os ponteiros sao acertados para a inserçao */
	}
	else if(cheia(D))
	{
		
		int novo_tam = ((D.F - D.I)+1)*2;
		T *V = new(nothrow) T[novo_tam];
		if(V == nullptr) 
		{
			return true;
		}
		T *P = D.E;
		T *Q = V;
		/* aqui vou copiar os elementos para o novo vetor, começando do elemento apontando pelo D.E, logo D.E vai ficar na primeiro posiçao */
		do {
			if(D.tamanho == 1) /* ***correção da falha de segmentaçao */
			{
				*Q++ = *P;
			}
			else if(P == D.F) /* se o ponteiro P que esta apontando para o D.E estiver no final do vetor */
			{
				*Q = *P; /* o valor de onde Q esta apontando recebe o valor apontado por P no D.F */
				P = D.I; /* P vai pro inicio, e incremento o Q */
				Q++;
			}	
			else /* se P nao estiver no final, o valor de Q recebe o de P e depois incremento ambos */
			{
				*Q++ = *P++;
			}
		}while (P != D.E); /* isso enquanto o P nao chegar no D.E de volta */
		delete[] D.I; /* desaloco o vetor antigo */
		D.I = D.E = V; /* acerto os ponteiros pro inicio e o da esquerda, que vao aponta pro começo do vetor V */
		D.F = D.I + (novo_tam - 1); /* D.F vai apontar para o final do novo vetor */
		D.D = Q - 1; /* D.D vai aponta para a posiçao em que o "ultimo" elemento foi inserido */
		D.tamanho = novo_tam; /* D. tamanho recebe o novo tamanho para a funçao auxiliar "cheia" */
	}	
		/* Depois de testar se esta vazia ou cheia, vou ter dois casos: */
	if(D.contador == 0) /* ***correçao de erro, se passasse pelo primeiro if, ia para o debaixo e D.D ficaria no inicio e D.E no final, havendo erro quando fosse remover e tivesse apenas um elemento, já que os dois tem q apontar para o mesmo lugar nesse momento*/
	{
		*D.E = e;
	}
	else if(D.E == D.I) /* se o D.E estiver no inicio, ele aponta para o final e recebe o elemento,
	no caso se ele estiver cheio isso condiçao sempre vai ser true */
	{
		D.E = D.F;
		*D.E = e;
	}		
	else /* senao, apenas decremento e add o elemento */
	{
		D.E--;
		*D.E = e;
	}
	D.contador++; /* contador recebe +1, auxilia para saber o tamanho e fazer a funçao "cheia" */
	return false;
}

template <typename T>
bool inserir_dir(Deque<T> &D, T e)
{
	/* essa funçao eh analoga a inserir_esq, com excessao de algumas coisas :   */
	if(vazio(D))
	{
		D.D = D.E = D.I; 
	}
	else if(cheia(D))
	{
		int novo_t = ((D.F - D.I)+1)*2;
		T *v = new(nothrow) T[novo_t];
		if(v == nullptr)
		{
			return true;
		}
		T *p = D.E;
		T *q = v;
		do{
			if(D.tamanho == 1)
			{
				*q++ = *p;
			}
			else if(p == D.F)
			{
				*q = *p;
				p = D.I;
				q++;
			}	
			else 
			{
				*q++ = *p++;
			}
		}while (p != D.E);
		delete[] D.I;
		D.I = D.E = v;
		D.F = D.I + (novo_t - 1);
		D.D = q - 1;
		D.tamanho = novo_t;
	}
	if(D.contador == 0) /* ***correçao de erro */
	{
		*D.D = e;
	}
	else if(D.D == D.F) /* se o D.D estiver no final, ele aponta para o inicio para receber o elemento, 
	no caso se estiver cheio essa condiçao nao vai acontecer */
	{
		D.D = D.I;
		*D.D = e;	
	}		
	else /* senao, apenas incremento e adiciono o elemento */
	{
		D.D++;
		*D.D = e;
	}
	D.contador++;
	return false;
}

template <typename T>
T remover_esq(Deque<T> &D)
{
	T e = *D.E; /* e recebe o elemento a ser removido */
	if(D.E == D.D)
	{ /* se D.E tiver apontando para o mesmo lugar que o D.D, D.E aponta para null, e o vetor ficara vazio de acordo com a funçao "vazia" */ 
		D.E = nullptr;
		D.D = nullptr;
	}
	else if(D.E == D.F) /* se o D.E estiver no final, ele aponta para o inicio */
	{
		D.E = D.I;	
	}
	else
	{
		D.E++; /* senao, apenas incremento */
	}
	D.contador--; /* diminuo 1 ao contador */
	return e; /* retorno o elemento */
}

template <typename T>
T remover_dir(Deque<T> &D)
{
	T e = *D.D; /* e recebe o elemento a ser removido */
	if(D.E == D.D)
	{ 
		D.E = nullptr;
		D.D = nullptr;
	}
	else if(D.D == D.I) /* se o D.D estiver no inicio, ele aponta para o final */
	{
		D.D = D.F;
	}
	else
	{
		D.D--; /* senao, apenas decremento */
	}
	D.contador--;
	return e;
}
