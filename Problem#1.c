
//  Created by hajar on 28/07/1442 AH.

#include "ass2.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdbool.h"

//shared data..
int array[10];

int elementsnum;
//declaring mutex
pthread_mutex_t lock;

void*median(){
    
    //locking
    pthread_mutex_lock(&lock);
    //insertion sorting
    for (int i = 1; i < elementsnum; i++) {
        int temp = array[i];
        int j = i;
        while (j > 0 && array[j - 1] > temp) {
            array[j] = array[j - 1];
            j--; }
        array[j] = temp;
    }
    int mid=elementsnum/2;
    int res;
    if(elementsnum%2==0)
        res= (array[mid-1]+array[mid])/2;
     else
         res=array[mid];
        
        
    printf("The median is %d\n",res);
    
    //unlocking
    pthread_mutex_unlock(&lock);
}

void*mean(){
    pthread_mutex_lock(&lock);
    int sum=0;
    for(int i=0 ; i<elementsnum ; i++)
        sum+=array[i];
    
    float Mean = ((float)sum / elementsnum);
    printf("The Mean is %.2f\n",Mean);
    pthread_mutex_unlock(&lock);
}

void*prime(){
    
    pthread_mutex_lock(&lock);
    for(int i=0 ; i<elementsnum ; i++){
        bool flag = false;
        if(array[i]>1){
    for (int j = 2; j < array[i] ; j++) {
        if (array[i] % j == 0) {
            flag = true;
            break;
        }
    
  

    }
        }else{
            flag = true;
        }
        if (!flag)
            printf("%d is a prime number\n",array[i] );
    
    }
  pthread_mutex_unlock(&lock);
}



int main(void){
    //initializing mutex
    pthread_mutex_init(&lock,NULL);
    
    printf("How many number in your list -mustn't exceed 10 numbers- \n");
    
    scanf("%d",&elementsnum);
    
    
    printf("Enter your list number :");
    for(int i=0; i<elementsnum ; i++){
        //printf("i = %d",i);
        scanf(" %d ",&array[i]);
    }
    

    
    printf("Your list number  is: \n");
    for(int i=0; i<elementsnum ;i++){
        printf(" %d ",array[i]);
     
    }
    printf("\n");
    
pthread_t th1;
pthread_t th2;
pthread_t th3;
    
    pthread_create(&th2,NULL,mean,NULL);
    pthread_join(th2,NULL);
   
    pthread_create(&th1,NULL,median,NULL);
    pthread_join(th1,NULL);

    pthread_create(&th3,NULL,prime,NULL);
    pthread_join(th3,NULL);
    
    //destroying mutex
    pthread_mutex_destroy(&lock);
    
}
