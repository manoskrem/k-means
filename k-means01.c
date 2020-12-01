#include <stdio.h>
#include <stdlib.h>
//******************************************************
#define N 6 
#define Nc 2
#define Nv 2
//******************************************************

float Vec[N][Nv] ;
float Center[Nc][Nv] ;
int Classes[N] ;
//******************************************************
void PrintVec(float *a,int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        printf(" %f",a[i]);
    }
    
}


void CreateVec(void){
    //TODO........
    int i,j;
    for(i=0 ; i < N ; i++)
        for (j = 0; j < Nv; j++)
        {
            Vec[i][j] = (4.0*rand()) / RAND_MAX ;
        }
        
}

void CreateCenters(void){
    //TODO........
}

void Classification(void){
    //TODO........
}

void EstimateCenters(void){
    //TODO........
}

int Termninate(void){
    //TODO........
    return 0; 
}

//******************************************************

int main (){

    CreateVec();
    PrintVec((float *)Vec,N*Nv);
    CreateCenters();
    Classification();

   /* do{
    Classification();
    EstimateCenters();
    }while (Terminate()) ;
   */
    
    return 0;
}