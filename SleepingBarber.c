#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t seatMutex;       
sem_t customers;       
sem_t semBarber;    
int runningTime;        
int freeseatsCount; 
int customersCount;    
int customerWait;      
int receivedHaircut;  
pthread_t barberThread;          
pthread_t customerThread[20];    
void* barber() {
    int haircutTime;   
    while(1) {
	    sem_wait(&customers);
	    sem_wait(&seatMutex);
	    freeseatsCount += 1;
	    haircutTime = (rand() % 5) + 1;
	    printf("Barber with customer, and he takes %d seconds for haircut.\n",haircutTime);
	    printf("Number of free seats: %d\n",freeseatsCount);
	    sem_post(&semBarber);
	    sem_post(&seatMutex);
   	    sleep(haircutTime);
    } 
}
void* customer() {
    int waitingTime;
    int a = 1;
    while(a == 1) {
	    sem_wait(&seatMutex);
	    if(freeseatsCount <= 0){
	        waitingTime = (rand() % customerWait) + 1;
		    printf("Customer %zu dint get haircut, and will come back after %ds for again trying\n", pthread_self(),waitingTime);
		    sem_post(&seatMutex);
	        sleep(waitingTime);
	    }
	    else{
		    freeseatsCount -= 1;
		    printf("Customer %zu is waiting.\n",pthread_self());
		    printf("\tNumber of free seats: %d\n",freeseatsCount);
		    sem_post(&customers);
		    sem_post(&seatMutex);
		    sem_wait(&semBarber);
		    printf("Customer %zu gets haircut\n",pthread_self());
		    a = 0;
		    receivedHaircut += 1;
	    }
      
     }
}                                      
int main() {
    printf("Enter the running time of the program: ");
    scanf("%d",&runningTime);
    printf("Enter the number of free seats: ");
    scanf("%d",&freeseatsCount);
    printf("Enter the customers count: ");
    scanf("%d",&customersCount);
    printf("Enter the maximun waiting time for the customer to come again: ");
    scanf("%d",&customerWait);
    receivedHaircut = 0;   
    sem_init(&seatMutex,0,1);
    sem_init(&customers,0,0);
    sem_init(&semBarber,0,0);
    pthread_create(&barberThread, NULL, barber, NULL);
    printf("Barber has been created.\n");
    for (int i = 0; i < customersCount; i++){
	   pthread_create(&customerThread[i], NULL, customer, NULL); 
	   printf("Customer %zu has been created.\n",customerThread[i]);
    }
    sleep(runningTime); 
    printf("\n %d out of %d customers get haircut.",receivedHaircut,customersCount);
    exit(0);
}



