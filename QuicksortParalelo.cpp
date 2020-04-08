include <iostream>
#include <string>
#include <thread>
#include<stdlib.h>
#include <time.h>

using namespace std;

void quick_sort(int *ptr_array,int izquierda,int derecha)
{
    thread izq,der;
    int i=izquierda;
    int j=derecha;
    int pivote=ptr_array[(derecha+izquierda)/2];
    int temp;
    while(i<=j)
    {
        while(ptr_array[i]<pivote)
        {
            i++;
        }
        while(ptr_array[j]>pivote)
        {
            j--;
        }
        if(i<=j)
        {
            temp=ptr_array[i];
            ptr_array[i]=ptr_array[j];
            ptr_array[j]=temp;
            i++;
            j--;
        }
    }
    if(izquierda<j)
    {
        izq=thread(quick_sort,ptr_array,izquierda,j);
        izq.join();
    }
    if(derecha>i)
    {
        der=thread(quick_sort,ptr_array,i,derecha);
        der.join();
    }
}

void imprimir(int *ptr_array,int tam)
{
    for(int i=0;i<tam;i++)
    {
        cout<<*(ptr_array+i)<<"  ";
    }
}

int main()
{
    //int num_thread = 2;
    int tam=10000;
    int array1[10000];
    for(int i=0;i<tam;i++)
    {
        array1[i]=rand()%10;
    }

    imprimir(array1,tam);
    cout<<endl;

    float tiempo1,tiempo2;
    tiempo1=clock();

    thread t1(quick_sort,array1,0,tam);
    t1.join();

    tiempo2=clock();

    imprimir(array1,tam);

    cout<<"Tiempo : "<<(tiempo2-tiempo1)/CLOCKS_PER_SEC<<endl;

    return 0;
}