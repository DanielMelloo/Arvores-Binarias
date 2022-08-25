// *********************** genBST.h *************************
// Árvore binária de busca genérica
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <class T>
    class Node
    {
        public:
            int info;
            Node *next;

            Node () { next=0; }

            Node (int el, Node *pr)
            {
                info=el;
                next=pr;
            }
    };

template <class T>
    class Stack : public stack<T> { /* implementar */ };

template <class T>
    class Queue : public queue<T> 
    {
        public:
            T dequeue() {
                T tmp = queue<T> ::front(); // returns a reference to the first element of the queue
                queue<T>::pop();
                return tmp;
            }
            void enqueue(const T& el) 
            {
                queue<T>::push(el);
            }
    };

template <class T>
    class BSTNode 
    {
        public:
            BSTNode() 
            {
                left = right = 0;
            }
            BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) 
            {
                el = e; left = l; right = r;
            }

            T el;
            BSTNode<T> *left, *right;
    };

template<class T>
    class BST 
    {
        public:
        BST() 
        {
            root = 0;
        }

        ~BST()
        {
            clear();
        }

        void clear() 
        {
            clear(root); root = 0;
        }

        bool isEmpty() const 
        {
            return root == 0;
        }

        void preorder() 
        {
            preorder(root);
        }

        void inorder() 
        {
            inorder(root);
        }

        void postorder() 
        {
            postorder(root);
        }

        T* search(const T& el) const 
        {
            return search(root,el);
        }

        void insert (const T& el);

        void breadthFirst();

    protected:
        BSTNode<T>* root;
        void clear(BSTNode<T>*);
        T* search(BSTNode<T>*, const T&) const; // Ve onde e se o elemento informado esta na arvore
        void preorder(BSTNode<T>*);
        void inorder(BSTNode<T>*);
        void postorder(BSTNode<T>*);
        virtual void visit(BSTNode<T>* p) 
        {
            cout << p->el << ' ';   
        }   
    };

template<class T>
void BST<T>::insert(const T& el) 
{
    BSTNode<T> *p = root, *prev = 0;
    while (p != 0) 
    { // encontrar um lugar para inserir um nó
        prev = p;
        if (el < p->el)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
            
    }

    if (root == 0) // verifica se a árvore esta vazia
    {
        root = new BSTNode<T>(el); //insere o nó na raiz
    }

    else if (el < prev->el) // compara el com o filho à esquerda
    {
        prev->left = new BSTNode<T>(el); //insere o nó no filho à esquerda
    }

    else 
    {
        prev->right = new BSTNode<T>(el); //insere o nó no filho à direita.
    }
}

template <class T>
void BST<T>::clear (BSTNode<T>*)
{
    clear ();
}

//Pesquisar por valores em árvores binárias de busca
template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const 
{
    while (p != 0)
        if (el == p->el)
            return &p->el;
    else if (el < p->el)
        p = p->left;
    else p = p->right;
        return 0;
}

//Procedimento em-ordem (inorder)
template <class T>
void BST<T>:: inorder (BSTNode<T> *p) 
{
    if ( p != 0 ) 
    {
        inorder (p->left);
        visit(p);
        inorder (p->right);
    }
}

//Procedimento pré-ordem
template <class T>
void BST<T>:: preorder (BSTNode<T> *p) 
{
    if ( p != 0 ) 
    {
        visit(p);
        preorder (p->left);
        preorder (p->right);
    }
}

//Procedimento pós-ordem
template <class T>
void BST<T>:: postorder (BSTNode<T> *p) 
{
    if ( p != 0 )
    {
        postorder (p->left);
        postorder (p->right);
        visit(p);
    }
}

#endif

int main()
{
    setlocale( LC_ALL, "" ); //Apenas para acentuar

    int el;
    int* pesq;

    BST <int> arvore1;

    //Inserir elementos na árvore
    for (int i=0;i<20;i++)
    {
        arvore1.insert (i);
    }

    el=10;

    if (arvore1.isEmpty() == false )
    {
        cout << "Percurso in-order:\n";
        arvore1.inorder ();
        
        cout << "\n";

        cout << "Percurso pre-order:\n";
        arvore1.preorder ();
        
        cout << "\n";

        cout << "Percurso post-order:\n";
        arvore1.postorder ();
        
        cout << "\n";
    }

    return 0;
}