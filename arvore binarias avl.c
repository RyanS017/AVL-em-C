#include <stdio.h>
#include <malloc.h>

typedef struct No{
    int valor;
    struct No *esq;
    struct No *dir;
    int altura;
    
}No;

void atualizaAltura(No* n, No* subN ){
    if(n->altura <= subN->altura){
        n->altura = subN->altura +1;
    }
}
No* rotaçãoDireita(No* n, No* esq){
    if(esq->dir == NULL){
        n->esq = NULL;
        esq->dir = n;
        n->altura = esq->altura-1;
        atualizaAltura(esq,n);
        return esq;
    }else{
        n->esq = esq->dir;
        esq->dir = n;
        n->altura = esq->altura-1;
        atualizaAltura(esq,n);
        return esq;
    }
}
No* rotaçãoEsquerda(No* n, No* dir){
    if(dir->esq == NULL){
        n->dir = NULL;
        dir->esq = n;
        n->altura = dir->altura-1;
        atualizaAltura(dir,n);
        return dir;
    }else{
        n->dir = dir->esq;
        dir->esq = n;
        n->altura = dir->altura-1;
        atualizaAltura(dir,n);
        return dir;
    }
}

No* rotaçãoDuplaDir(No* n, No* esq){
    n->esq = esq->dir;
    esq->dir = NULL;
    n->esq->esq = esq;
    int temp = esq->altura;
    esq->altura = n->esq->altura;
    n->esq->altura = temp;
    return rotaçãoDireita(n, n->esq);
}

No* rotaçãoDuplaEsq(No* n, No* dir){
    n->dir = dir->esq;
    dir->esq = NULL;
    n->dir->dir = dir;
    int temp = dir->altura;
    dir->altura = n->dir->altura;
    n->dir->altura = temp;
    return rotaçãoEsquerda(n, n->dir);
}

No* balanceiaArvore(No* n, No* subE, No* subD){
    if(subD != NULL && subE != NULL){
    if(subE->altura - subD->altura > 1 || subE->altura - subD->altura < -1){
        if(subE->altura - subD->altura > 1){
            if(subE->esq != NULL){
                n = rotaçãoDireita(n, subE);
            }else{
                n = rotaçãoDuplaDir(n, subE);
            }
        }else{
            if(subD->dir != NULL){
                n = rotaçãoEsquerda(n, subD);
            }else{
                n = rotaçãoDuplaEsq(n, subD);
            }
        }
    }
    }else if(subD == NULL && n->altura > 1){
        if(subE->esq != NULL){
                n = rotaçãoDireita(n, subE);
            }else{
                n = rotaçãoDuplaDir(n, subE);
            }
    }else if(subE == NULL && n->altura > 1){
        if(subD->dir != NULL){
               n =  rotaçãoEsquerda(n, subD);
            }else{
                n = rotaçãoDuplaEsq(n, subD);
            }
    }
    return n;
}

No* atribuiValor(int valor, No* n){
    if(n == NULL){
        No *novo = (No*)malloc(sizeof(No*));
        novo->valor = valor;
        novo->dir = NULL;
        novo->esq= NULL;
        novo->altura = 0;
        return novo;
    }else{
        if(n->valor > valor){ 
            n->esq = atribuiValor(valor, n->esq);
            atualizaAltura(n, n->esq);
             n = balanceiaArvore(n, n->esq, n->dir);
        }
        else if(n->valor < valor) {
            n->dir = atribuiValor(valor, n->dir);
            atualizaAltura(n,n->dir);
            n = balanceiaArvore(n, n->esq, n->dir);
        }
       //balanceiaArvore(n, n->esq, n->dir);
        return n;
    }
}
void imprimirEmOrdem(No* raiz){
	if( raiz == NULL ){
		return;
	}
	imprimirEmOrdem(raiz->esq);
	printf("%d - ", raiz->valor);
	imprimirEmOrdem(raiz->dir);
	return;
}


int main(){
    
    No* arv = NULL;
    arv = atribuiValor(5, arv);
    arv = atribuiValor(7, arv);
    arv = atribuiValor(6, arv);
   imprimirEmOrdem(arv);
   printf("sddd");

}