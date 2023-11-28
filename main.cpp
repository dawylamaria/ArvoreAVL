#include <iostream>
using namespace std;

struct NoArvore {
    int chave;
    NoArvore* esquerda;
    NoArvore* direita;
    int altura;
};

NoArvore* novoNo(int chave) {
    NoArvore* novoNo = new NoArvore;
    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;

    return novoNo;
}

int maior(int esquerda, int direita) {
    return (esquerda > direita) ? esquerda : direita;
}

int alturaDoNo(NoArvore*& raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

int fatorBalanceamento(NoArvore*& raiz) {
    if (raiz != NULL) {
        return (alturaDoNo(raiz->esquerda) - alturaDoNo(raiz->direita));
    } else {
        return 0;
    }
}

NoArvore* rotacaoEsquerda(NoArvore*& raiz) {
    NoArvore* y;
    NoArvore* filho;

    y = raiz->direita;
    filho = y->esquerda;

    y->esquerda = raiz;
    raiz->direita = filho;

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

NoArvore* rotacaoDireita(NoArvore*& raiz) {
    NoArvore* y;
    NoArvore* filho;

    y = raiz->esquerda;
    filho = y->direita;

    y->direita = raiz;
    raiz->esquerda = filho;

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

NoArvore* rotacaoDireitaEsquerda(NoArvore*& raiz) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

NoArvore* rotacaoEsquerdaDireita(NoArvore*& raiz) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

NoArvore* balancear(NoArvore*& raiz) {
    int fb = fatorBalanceamento(raiz);
    if (fb < -1 && fatorBalanceamento(raiz->direita) <= 0) {
        raiz = rotacaoEsquerda(raiz);
        
    } else if (fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0) {
        raiz = rotacaoDireita(raiz);
        
    } else if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz = rotacaoEsquerdaDireita(raiz);
        
    } else if (fb < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}

NoArvore* inserirAVL(NoArvore*& raiz, int chave) {
    if (raiz == NULL) {
        return novoNo(chave);
    } else {
        if (chave < raiz->chave) {
            raiz->esquerda = inserirAVL(raiz->esquerda, chave);
        } else if (chave > raiz->chave) {
            raiz->direita = inserirAVL(raiz->direita, chave);
        } else {
            cout << "Elemento ja existe!" << endl;
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

void percorrerEmOrdem(NoArvore* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        cout << raiz->chave << " ";
        percorrerEmOrdem(raiz->direita);
    }
}

int main(int argc, char** argv) {
    NoArvore* raiz = NULL;

    raiz = inserirAVL(raiz, 10);
    raiz = inserirAVL(raiz, 20);
    raiz = inserirAVL(raiz, 30);

    percorrerEmOrdem(raiz);

    return 0;
}

