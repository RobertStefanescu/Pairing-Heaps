#include<iostream>
#include <fstream>
using namespace std;
int n, crt,elem;
char x[256];
struct HN {
    
    int key;
    bool exista;
    HN *LC;
    HN *NS;
    
    HN():
    LC(NULL), NS(NULL), exista(true) {}
    
    HN(int key_, HN *LC_, HN *NS_):
    key(key_), LC(LC_), NS(NS_) {}
    
    void AC(HN *node) {
        if(LC == NULL)
            LC = node;
        else {
            node->NS = LC;
            LC = node;
        }
    }
};

bool Empty(HN *node) {
    return (node == NULL);
}

HN *merge(HN *A, HN *B)
{
    if(A == NULL) return B;
    if(B == NULL) return A;
    
    
    if(A->key < B->key) {
        A->AC(B);
        return A;
    }
    else {
        B->AC(A);
        return B;
    }
    
    return NULL;
}

int FM(HN *node) {
    return node->key;
}

HN *Inserare(HN *node, int key) {
    return merge(node, new HN(key, NULL, NULL));
}

HN *TPM(HN *node) {
    if(node == NULL || node->NS == NULL)
        return node;
    else {
        HN *A, *B, *nN;
        A = node;
        B = node->NS;
        nN = node->NS->NS;
        
        A->NS = NULL;
        B->NS = NULL;
        
        return merge(merge(A, B), TPM(nN));
    }
    
    return NULL;
}

HN *StergeMin(HN *node) {
    return TPM(node->LC);
}

void LazyDelete(HN *node, int x)
{
    if(node->key == x && node->exista == true)
    {
        node->exista = false;
    }
    if(node->NS != NULL)
        LazyDelete(node->NS, x);
    if(node->LC != NULL)
        LazyDelete(node->LC, x);
}


struct PH {
    HN *root;
    
    PH():
    root(NULL) {}
    

    
    void StergeMin(void) {
        root = ::StergeMin(root);
    }
    
    void J(PH other) {
        root = ::merge(root, other.root);
    }
    
    void LazyDelete(int x) {
        ::LazyDelete(root, x);
    }
    bool E(void) {
        return ::Empty(root);
    }
    
    int FM(void) {
        return ::FM(root);
    }
    
    void Inserare(int key) {
        root = ::Inserare(root, key);
    }
};

int main()
{
    ifstream fin("heap.txt");
    PH H;
    fin>>n;
    for(int i=1;i<=n;i++)
    {
        fin >> crt;
        if (crt==1)
        {
            fin >>elem;
            cout<<"Adaugam in heap elementul: "<<elem<<endl;
            H.Inserare(elem);
        }
        else if (crt==2)
        {
            fin >> elem;
            H.LazyDelete(elem);
            cout<<"Elementul "<< elem <<" a fost sters. "<<endl;
        }
        else if (crt==3)
            cout<<"Minimul curent este: "<<H.FM()<<endl;
        else if (crt==4)
        {
            int minim = H.FM();
            cout<<"A fost eliminat minimul curent care este: "<<minim<<endl;
            while (H.FM() == minim)
                H.StergeMin();
        }
    }
    
    return 0;
}

