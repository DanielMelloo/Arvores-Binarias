// *********************** genBST.h *************************
// Árvore binária de busca genérica
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

void passagem()
{
    cout << "Aqui passou\n";
}

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
        //=============================================================
        // Construtores e Inicializadores
        //=============================================================

            BSTNode ()
            {
                left = right = 0;
            } 
            BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) 
            {
                el = e; left = l; right = r;
            }
            BSTNode (const BSTNode&)=default; // Cópia

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

        void createBackboneRa (){ createBackboneR ();}
        void createBackboneLa (){ createBackboneL ();}

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
        void rotateRight (BSTNode<T>* Gr, BSTNode<T>* Par, BSTNode<T>* Ch); // Rotaciona à direita
        void rotateLeft (BSTNode<T>* Gr, BSTNode<T>* Par, BSTNode<T>* Ch);  // Rotaciona à esquerda
        void createBackboneR (); // Com rotação à esquerda
        void createBackboneL (); // Com rotação à direita

    };

template <class T>
void BST<T>::rotateRight (BSTNode<T>* Gr, BSTNode<T>* Par, BSTNode<T>* Ch)
{
    // Gr = pai de Par
    // Par = pai de Ch

    // BSTNode<T> *tmp;

    if (Par==root)
    {
        Par->left=Ch->right;
        Ch->right=Par;
        root=Ch;
    }
    else
    {
        Par->left=Ch->right;
        Ch->right=Par;
        Gr->right=Ch;
    }
}

template <class T>
void BST<T>::rotateLeft (BSTNode<T>* Gr, BSTNode<T>* Par, BSTNode<T>* Ch)
{
    // Gr = pai de Par
    // Par = pai de Ch

    // BSTNode<T> *tmp;

    if (Par==root)
    {
        Par->right=Ch->left;
        Ch->left=Par;
        root=Ch;
    }
    else
    {
        Par->right=Ch->left;
        Ch->left=Par;
        Gr->left=Ch;
    }
}

template <class T>
void BST<T>::createBackboneR ()
{
    BSTNode<T> *tmp, *Gr, *Par, *Ch;

    tmp=root;

    while (tmp!=0)
    {
        while (tmp->left!=0)
        {
            if (tmp==root) // Quando o pai é a raiz
            {
                if (tmp->left!=0) // Se a raiz tem filho à esquerda
                {
                    rotateRight (Gr, tmp, tmp->left);
                    Gr=root;
                }
                else // Se a raiz só tem filho à direita
                {
                    Gr=root;
                    tmp=tmp->right;
                }
            }
            else // Quando o não é raiz
            {   
                while (tmp->left!=0) 
                {

                    // aqui dentro o gr n pode mudar e o tmp tem sempre que ser
                    // quem o gr aponta

                    Par=tmp;
                    Ch=tmp->left;
                    rotateRight (Gr, Par, Ch);

                    tmp=Gr->right;
                }    
            }
        }
        Gr=Gr->right;
        tmp=Gr->right;
    }

}

template <class T>
void BST<T>::createBackboneL ()
{
    BSTNode<T> *tmp, *Gr, *Par, *Ch;

    tmp=root;

    while (tmp!=0)
    {
        while (tmp->right!=0)
        {
            if (tmp==root) // Quando o pai é a raiz
            {
                if (tmp->right!=0) // Se a raiz tem filho à esquerda
                {
                    rotateLeft (Gr, tmp, tmp->right);
                    Gr=root;
                }
                else // Se a raiz só tem filho à direita
                {
                    Gr=root;
                    tmp=tmp->left;
                }
            }
            else // Quando o não é raiz
            {   
                while (tmp->right!=0) 
                {

                    // aqui dentro o gr n pode mudar e o tmp tem sempre que ser
                    // quem o gr aponta

                    Par=tmp;
                    Ch=tmp->right;
                    rotateRight (Gr, Par, Ch);

                    tmp=Gr->left;
                }    
            }
        }
        Gr=Gr->left;
        tmp=Gr->left;
    }

}

template <class T>
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
    
    BST <int> arvore1;

    //Inserir elementos na árvore desbalanceada para direita
    // for (int i=0;i<20;i++)
    // {
    //     arvore1.insert (i); 
    // }

    arvore1.insert (2);
    arvore1.insert (10);
    arvore1.insert (5);
    arvore1.insert (3);
    arvore1.insert (8);
    arvore1.insert (17);
    arvore1.insert (28);
    arvore1.insert (1);

    cout << " ** ÁRVORE DESBALANCEADA ** \n\n";
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

    arvore1.createBackboneRa ();

    cout << "\n\n ** ÁRVORE DESBALANCEADA PARA DIREITA ** \n\n";

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

    arvore1.createBackboneLa ();

    cout << "\n\n ** ÁRVORE DESBALANCEADA PARA ESQUERDA ** \n\n";

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