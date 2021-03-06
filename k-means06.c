/*
gcc k-means06.c -o myprogram -fopt-info-vec-optimized -lm
time ./myprogram

real    0m56,780s
user    0m56,592s
sys     0m0,168s 
*/

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper")

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>


//******************************************************
#define N 100000
#define Nc 100
#define Nv 1000
#define THRESHHOLD 0.000001
//******************************************************

float Vec[N][Nv] ;
float Center[Nc][Nv] ;
int Classes[N] ;

//******************************************************
void PrintVec(float *a,int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        printf("%f",a[i]);
    }
    
}

//******************************************************

void CreateVec(void){
    //TODO........
    int i,j;
    for(i=0 ; i < N ; i++)
        for (j = 0; j < Nv; j++)
        {
            Vec[i][j] = (1.0*rand())/RAND_MAX ;
        }
        
}

//******************************************************
//Initializes random center array Center[Nc][Nv]

void CreateCenters(void){
    //TODO........
    int i,j,randomCenter;
    bool Unique[N] = {false};  //To prevent getting same centers
    for(i=0;i<Nc;i++){
        randomCenter = rand() % N ;                   //  Choose a center  in  range [0,N+1]
        while(Unique[randomCenter]){                
            randomCenter = rand() % N ;          //find new center while previous is selected
        }
        for(j=0;j<Nv;j++){
            Center[i][j] = Vec[randomCenter][j] ;
            Unique[randomCenter] = true ;           // center chosen becomes true
        }
    }
}

//******************************************************
//Returns the total min distance between the Vec and the Center

float Classification(void){
    //TODO........
    float min,mindist=0;
    for(int i=0;i<N;i++){
        int th=-1;

        min=350000;
        for (int j=0;j<Nc;j++){
            float dist=0;
            for (int k=0;k<Nv;k++){
                dist=dist+(Vec[i][k]-Center[j][k])*(Vec[i][k]-Center[j][k]);
            }
            dist=sqrt(dist);
            if (min>dist){
                min=dist;
                th=j;
            }
        }
        Classes[i]=th;
        mindist=mindist+min;
    }

    return mindist;

}

//******************************************************

void EstimateCenters(void){
    //TODO........
    int i, j, k, counter, n ;                           
    for(k=0;k<Nc;k++){
        float dist[Nv] = {0} ;                          // dist[Nv] array shows the sum of all vectors in the same cluster
        counter = 0 ; 
        for(i=0;i<N;i++){
            if(Classes[i] == k){                          // When Vector is same cluster 
                counter++ ;                             // counter will count how many vectors are in the same cluster
                for(j=0;j<Nv;j++){ 
                    dist[j] += Vec[i][j] ;
                }    
            }
        }   
        for(n=0;n<Nv;n++){
            Center[k][n] = dist[n] / (counter*1.0) ;    // New center is the mean of all vectors belong to the same cluster
        }
    }
}

//******************************************************


//******************************************************

int main (){
    
    float totDist ;
    float prevDist ;
    CreateVec() ;

    CreateCenters() ;
    totDist = 1.0e30 ;

    int count = 0 ;                         // Loop counter
    for(int i=0; i<16; i++){                  // 16 loops
    //do{
        count++ ;  printf("Wait...\n")   ;    
        prevDist = totDist ;
        totDist = Classification() ; 
        printf("totDist = %12f \n\n",totDist) ; 
        EstimateCenters() ; 
    } //while((prevDist-totDist)/totDist > THRESHOLD) ;
    printf("\nTimes Looped : %d\n",count) ; 
    
    return 0;
}