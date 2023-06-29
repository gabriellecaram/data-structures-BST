/* Estruturas de dados avançadas
 * Árvore binária de busca
 * inserção e remoção SEM balanceamento
 * 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char T;

typedef struct node{
    struct node *left, *right;
    T data;
} node;

typedef struct abb{
    node *raiz;
} ABB;

node *insert_private(node *p, T data){
    if (!p){ // se não achar o elemento, é onde deve inserir
        node *novo = (node *)malloc(sizeof(node));
        novo->data = data;
        novo->left = novo->right = 0;
        return novo;
    }
    else if (data < p->data){
        p->left = insert_private(p->left, data);
    }
    else if (data > p->data){
        p->right = insert_private(p->right, data);
    }
    else
        p->data = data;
    return p;
}

void insert(ABB *arvore, T data){
    arvore->raiz = insert_private(arvore->raiz, data);
}

// 3 situações:
// 1- remover uma folha ok
// 2- remover um nó com 1 filho 
// 3- remover um nó com 2 filhos: substitui o nó pelo maior elemento da subarvore da esquerda,
//                                ou o menor elemento da subarvore da direita. (função encontrar maior)

int vazia(ABB *arvore){
    return arvore->raiz == NULL;
}

node* max_node( node* p ) {
    if( ! p->right )
        return p;
    else
        return max_node( p->right);
}

T max(ABB* arvore){
    assert(!vazia(arvore));
    return max_node(arvore->raiz)->data;
}

node* min_node(node* p){
    if(!p->left)
        return p;
    else
        return min_node(p->left);
}

T min(ABB* arvore) {
    assert(!vazia(arvore));
    node* no = min_node(arvore->raiz);
    return no->data;
}

node *remove_private(node *p, T data){
    if(!p)
        return NULL;
    if(p->left == NULL && p->right == NULL){//se não tiver filhos
            free(p);
            return NULL;
    }
    else if(data < p->data){
        p->left = remove_private(p->left, data); //Se a chave for menor, busca na subárvore esquerda
    }
    else if(data > p->data){
        p->right = remove_private(p->right, data); //Se a chave for maior, busca na subárvore direita
    }
    else{
        if(!p->left){//O nó tem apenas um filho à direita, retorna o filho e libera o nó
            node* temp = p->right;
            free(p);
            return temp;
        }else if(!p->right){ //O nó tem apenas um filho à esquerda, retorna o filho e libera o nó
            node* temp = p->left;
            free(p);
            return temp;
        }else{
            node* temp = min_node(p->right);
            p->data = temp->data; //Copia o valor do sucessor para o nó atual
            p->right = remove_private(p->right, temp->data); //Remove o sucessor da subárvore direita
        }
        return p;
    }
}
void remove_node(ABB *arvore, T data)
{
    arvore->raiz = remove_private(arvore->raiz, data);
}

int main()
{
    ABB arvore;
    arvore.raiz = NULL;

    // Test insertion
    insert(&arvore, 'F');
    insert(&arvore, 'D');
    insert(&arvore, 'J');
    insert(&arvore, 'B');
    insert(&arvore, 'E');
    insert(&arvore, 'G');
    insert(&arvore, 'K');
    insert(&arvore, 'A');
    insert(&arvore, 'C');
    insert(&arvore, 'I');

     // Test finding the maximum element
    T maxElement = max(&arvore);
    printf("Maximum element: %c\n", maxElement);

    // Test finding the minimum element
    T minElement = min(&arvore);
    printf("Minimum element: %c\n", minElement);

    // Test removal
    T elementToRemove = 'D';
    remove_node(&arvore, elementToRemove);
    printf("Removed element: %c\n", elementToRemove);

    // Test finding the maximum element after removal
    maxElement = max(&arvore);
    printf("Maximum element after removal: %c\n", maxElement);
    
    return 0;
}