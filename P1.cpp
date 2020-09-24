
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>

using namespace std;

int filas=20;
int columnas=20;
int Matrix[20][20];
int Matrix_A[20][20];
int Matrix_B[20][20];
int Producto[20][20];

void Generar(int **M, int fil, int col)
{
    for(int i=0; i<fil; i++)
    {
        for(int j=0; j<col; j++)
        {
            M[i][j]= rand()%10+1;
            //cout<<M[i][j]<<" ";
        }
        //cout<<endl;
    }
}

void Generar_zero(int **M, int tam)
{
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            M[i][j]=0;
        }
    }
}

void Bucles_Fila(int **M, int tam)
{
    int suma = 0;
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            suma+=M[i][j];
        }
    }
    //cout<<"Fila: "<<suma<<endl;
}

void Bucles_Columna(int **M, int tam)
{
    int suma=0;
    for(int i=0; i<tam; i++)
    {
        for(int j=0; j<tam; j++)
        {
            suma+=M[i][j];
        }
    }
    //cout<<"Columna: "<<suma<<endl;
}

void Multi_clasica(int **M1, int **M2, int **MR, int tam)
{
    for (int fil = 0; fil < tam; fil++)
    {
        for (int col = 0; col < tam; col++)
        {
            for (int inner = 0; inner < tam; inner++)
            {
                MR[fil][col] += M1[fil][inner] * M2[inner][col];
            }
        }
    }
}

void Multi_block(int n, int **M1, int **M2, int **MR)
{
    int bi=0;
    int bj=0;
    int bk=0;
    int i=0;
    int j=0;
    int k=0;
    int blockSize=2;

    for(bi=0; bi<n; bi+=blockSize)
        for(bj=0; bj<n; bj+=blockSize)
            for(bk=0; bk<n; bk+=blockSize)
                for(i=0; i<blockSize; i++)
                    for(j=0; j<blockSize; j++)
                        for(k=0; k<blockSize; k++)
                            MR[bi+i][bj+j] += M1[bi+i][bk+k]*M2[bk+k][bj+j];
}

vector<clock_t> matrix_dinamica(int tam)
{
    vector<clock_t> vr;
    clock_t t;

    int fil=tam;
    int col=tam;
    int **M1 = new int*[fil];
    int **M2 = new int*[fil];
    int **MRC = new int*[fil];
    int **MRB = new int*[fil];

    for (int i = 0; i < fil; i++)
    {
        M1[i] = new int[col];
        M2[i] = new int[col];
        MRC[i] = new int[col];
        MRB[i] = new int[col];
    }

    Generar(M1,tam,tam);
    Generar(M2,tam,tam);
    Generar_zero(MRC,tam);
    Generar_zero(MRB,tam);

    t = clock();
    //Multi_clasica(M1,M2,MRC,tam);
    t = clock() - t;
    vr.push_back(t);

    t = clock();
    Multi_block(tam,M1,M2,MRB);
    t = clock() - t;
    vr.push_back(t);


    delete M1;
    delete M2;
    delete MRC;
    delete MRB;

    return vr;
}

vector<clock_t> Ejercicio1(int tam)
{
    vector<clock_t> vr;
    clock_t t;

    int **M1 = new int*[tam];
    for (int i = 0; i < tam; i++)
    {
        M1[i] = new int[tam];
    }
    Generar(M1,tam,tam);

    t = clock();
    Bucles_Fila(M1,tam);
    t = clock() - t;

    vr.push_back(t);

    t = clock();
    Bucles_Columna(M1,tam);
    t = clock() - t;

    vr.push_back(t);

    delete M1;

    return vr;
}


int main()
{
    srand (time(NULL));

    //// EJERCICIO 1
    /*
    vector<clock_t> v1;
    vector<clock_t> v2;
    vector<int> vt;

    for (int i = 100; i < 15000; i+=500)
    {
        vector<clock_t> vr = Ejercicio1(i);
        v1.push_back(vr[0]);
        v2.push_back(vr[1]);
        vt.push_back(i);
    }

    for (int i = 0; i < v1.size(); i++)
    {
        cout<<((float)v1[i])/CLOCKS_PER_SEC<<" << "<<((float)v2[i])/CLOCKS_PER_SEC<<" << "<<vt[i]<<endl;
    }
    */

    /// EJERCICIO 2 Y 3
/*
    vector<clock_t> v1;
    vector<clock_t> v2;
    vector<int> vt;

    for (int i = 64; i < 1000; i+=64)
    {
        vector<clock_t> vr = matrix_dinamica(i);
        v1.push_back(vr[0]);
        v2.push_back(vr[1]);
        vt.push_back(i);
    }

    for (int i = 0; i < v1.size(); i++)
    {
        cout<<((float)v1[i])/CLOCKS_PER_SEC<<" << "<<((float)v2[i])/CLOCKS_PER_SEC<<" << "<<vt[i]<<endl;
    }
*/
    /// EJERCICIO 5

    matrix_dinamica(1000);
    cout<<"Matriz de 1000x1000 por bloque"<<endl;

    return 0;
}
