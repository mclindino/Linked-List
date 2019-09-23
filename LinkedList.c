#include "LinkedList.h"

//Da malloc no Head, criando um Head com quantidade 0 e apontando para NULL. Inicializa toda a Lista seguinte.
Lista* cria_lista(){	
	Lista *head;
	if((head = malloc(sizeof(Lista))) == NULL) {
		exit(1);
	}

	head->qtd = 0;
	head->first = NULL;
	return head;
}

//Caso a quantidade da lista for MAX, retorna 1. Se a lista não existir, retorna -1.
int lista_cheia(Lista *L){
	if(L->qtd == MAX) {
		return 1;
	} else if(L == NULL) {
		return -1;
	} else {
		return 0;
	}

}

/*Caso o head estiver apontando para NULL, a lista estará vazia e consequentemente retorna valor 1. 
Se a lista não existir, retorna -1. */
int lista_vazia(Lista *L){
	if(L->first == NULL) {
		return 1;
	} else if(L == NULL) {
		return -1;
	} else {
		return 0;
	}
}

int insere(Lista *L, int pos, int valor){
	Nodo *p, *novo;
	int i;
	p = L->first;

	if(pos > L->qtd) {	//Se o usuario quiser inserir um nodo em uma posição inválida, retorna 0 (ERRO).
		return 0;
	}
	if((novo = malloc(sizeof(Nodo))) == NULL) {
		exit(1);
	}
	novo->val = valor;
	if(pos == 0) {								//Inserir na primeira posição
		if(L->qtd == 0) {						//Caso não tenha nenhum nodo na lista
			L->first = novo;
			novo->prox = NULL;
			L->qtd++;
			return 1;
		} else {								//Caso já tenha pelo menos um nodo na lista
			novo->prox = L->first;
			L->first = novo;
			L->qtd++;
			return 1;
		}
	}
	for(i = 1; i < pos; i++) {					//Procura o nodo da posição desejada
		p = p->prox;	
	}
	if(pos == L->qtd) {							//Caso a posição seja a ultima da lista
		p->prox = novo;
		novo->prox = NULL;
		L->qtd++;
		return 1;
	}											//Caso geral para a inserção de um nodo
	novo->prox = p->prox;
	p->prox = novo;
	L->qtd++;
	return 1;
}

int deleta(Lista *L, int pos){
	Nodo *p, *q;
	int i;
	p = L->first;
	q = p->prox;
	if(lista_vazia(L) != 0 || pos >= L->qtd) {		//Se o usuario quiser deletar um nodo em uma posição inválida ou a lista estiver vazia, retorna 0 (ERRO).
		return 0;
	} else {
		if(pos == 0) {								//Caso a posição do nodo a ser deletado seja a primeira
			L->first = q;							//Head aponta para o proximo nodo que não seja o 0
			free(p);
			L->qtd--;
			return 1;
		} 
		if(q == NULL) {								//Caso não tenha nenhum nodo para apontar, aponte para NULL
			L->first = NULL;
			free(p);
			L->qtd--;
			return 1;
		}
		for(i = 1; i < pos; i++) {					//Procura o nodo na posiçao desejada e o nodo anterior
			p = q;
			q = p->prox;
		}
		if(q->prox != NULL) {						//Caso generico
			p->prox = q->prox;
			free(q);
			L->qtd--;
			return 1;
		} else {
			p->prox = NULL;							//Caso for deletar a ultima posição
			free(q);
			L->qtd--;
			return 1;
		}
	}
}

//Utiliza a função deleta até não houver mais elementos. Free (head) depois.
void destroi_Lista(Lista *L){
	int n, i;
	n = L->qtd;
	if(L->first != NULL) {
		for(i = 0; i < n; i++) {
			deleta(L, i);
		}
	}
	free(L);
}

int get(Lista *L, int pos){
	Nodo *p;
	int i;

	p = L->first;
	if(pos > L->qtd || pos >= MAX) {			//Retorna 0 caso a posição for maior que quantidade ou MAX.
		return 0;
	}
	for(i = 0; i < pos; i++) {					//Retorna o valor do Nodo depois de realizar a procura da posição a partir de um for.
		p = p->prox;
	}
	return p->val;
}

int set(Lista *L, int pos, int valor){
	Nodo *p;
	int i;

	p = L->first;
	if(pos > L->qtd || pos >= MAX) {			//Retorna 0 caso a posição for maior que quantidade ou MAX.
		return 0;
	}
	for(i = 0; i < pos; i++) {					//Retorna 1 depois de realizar a procura de um nodo na posição desejada e sobrescrever seu valor.
		p = p->prox;
	}
	p->val = valor;
	return 1;
}

int locate(Lista *L, int numero){
	Nodo *p;
	int i;

	p = L->first;
	if(p->val == numero) {						//Retorna posição 0 caso o valor desejado estiver no primeiro Nodo.
		return 0;
	} else {
		for(i = 1; i < (L->qtd); i++) {			//Retorna  a posiçaõ do nodo depois de realizar a sua procura, comparando o valor de cada nodo com o parametro numero.
			p = p->prox;
			if(p->val == numero) {
				return i;
			}
		}
	}
	return -1;
}

//Retorna quantidade da lista.
int length(Lista *L){
	return L->qtd;

}
