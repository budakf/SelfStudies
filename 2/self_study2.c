/*
Fatih BUDAK
Derlemek icin : gcc self_study2.c -lpthread
*/

#include <stdio.h> 
#include <string.h> 
#include <errno.h>          
#include <semaphore.h>      
#include <stdlib.h>         
#include <sys/types.h>     
#include <sys/shm.h>       
#include <fcntl.h> 

#define MAX_READ 5
#define MAX_WRITE 1

sem_t *s1, *sm, *s2; 

int *count_read = 0;
int *count_write = 0;
int * islocked = 0;

void reading(char * type ,int time){	
	
	if((*count_write) != 0){
		printf("%s bekliyor (cunku yazma islemi devam ediyor)\n",type);	
		
		if((*count_read) == 0){
			sem_wait(s2);
		  	if((*count_write) == 0)
				sem_post(s2);
			sem_wait(s1);
			(*count_read)++;
			printf("%s okumaya basladi\n",type);
			sleep(time);
			printf("%s okumayi bitirdi\n",type);	
			sem_post(s1);
			(*count_read)--;

			if((*count_read) == 0){
				sem_post(s2);
				sem_post(sm);
			}
		}
		
	}

	else{
		if((*count_read) == 0)
			sem_wait(s2);

		sem_wait(s1);
		(*count_read)++;
		printf("%s okumaya basladi\n",type);
		sleep(time);
		printf("%s okumayi bitirdi\n",type);	
		sem_post(s1);
		(*count_read)--;
		if((*count_read) == 0){
			sem_post(s2);
			sem_post(sm);
		}
	}		
}

void writing(char * type ,int time){
	
	if((*count_read) != 0){
		printf("Okuma islemi var bu yuzden %s bekler\n", type);
		sem_wait(s2);	
	}
	else if((*count_write) != 0)
		printf("Yazma islemi var bu yuzden %s bekler\n", type);

	sem_wait(s2);
	(*count_write)++;
        printf("%s calismaya basladi\n",type);
	sleep(time);
	printf("%s calismayi bitirdi\n",type);
	(*count_write)--;
	sem_post(s2);
	sem_post(sm);
	 	
}

int main(){
	char *type =  (char *) malloc(sizeof(char)*3);
	int time,i;
	char * temp = (char *) malloc(sizeof(char)*128);
	char e_h='E';
	pid_t pid = 1 ;
	int shmid,shmid2,shmid3;	
	shmid = shmget (IPC_PRIVATE, sizeof (int)*1, 0644 | IPC_CREAT);
	shmid2 = shmget (IPC_PRIVATE, sizeof (int)*1, 0644 | IPC_CREAT);
	shmid3 = shmget (IPC_PRIVATE, sizeof (int)*1, 0644 | IPC_CREAT);
	if (shmid < 0){                           
        	perror ("shmget\n");
       		exit (1);
	}
	if (shmid2 < 0){                           
        	perror ("shmget\n");
       		exit (1);
	}
	if (shmid3 < 0){                           
        	perror ("shmget\n");
       		exit (1);
	}
	islocked = (int *) shmat (shmid, NULL, 0);
	count_read = (int *) shmat (shmid2, NULL, 0);
	count_write = (int *) shmat (shmid3, NULL, 0);

	s1 = sem_open ("Semaf1", O_CREAT | O_EXCL, 0644, 5 ); 
        sem_unlink ("Semaf1");
	s2 = sem_open ("Semaf2", O_CREAT | O_EXCL, 0644, 1 ); 
        sem_unlink ("Semaf2");            
	sm = sem_open ("Semaf3", O_CREAT | O_EXCL, 0644, 0); 
	sem_unlink ("Semaf3");

	while(e_h=='E'){	 
		if(pid != 0){
		   printf("Proses tipini ve calisma suresini giriniz:\n");
		   scanf("%s %d %s",type, &time, temp);
		   getchar();
	
		   if(type[0]=='W'){
			pid = fork();
			if(pid == 0){
		         	writing(type, time);
				break;		
			}

		
		   }
		   else if(type[0]=='R'){
			if((*count_read) > 0)				
				printf("Calisan okuyucu sayisi 5 ten kucuk\n");			    			
			pid = fork();
			if(pid == 0){
		         	reading(type, time);
				break;		
			}

		
		   }
                   if(pid!=0){
			sleep(1);
		   	printf("Devam etmek istiyor musunuz? (E/H)\n");
		   	e_h = getchar();
		   }
		}
	}
	if (pid!=0){
		while (pid = waitpid (-1, NULL, 0)){
            		if (errno == ECHILD)
                		break;
		}

		shmdt (islocked);					
        	shmctl (shmid, IPC_RMID, 0);

		shmdt (count_read);					
        	shmctl (shmid2, IPC_RMID, 0);

		shmdt (count_write);					
        	shmctl (shmid3, IPC_RMID, 0);	

		sem_destroy (s1);
		sem_destroy (s2);
		sem_destroy (sm);
		printf("Tüm prosesler sonlandi\n");
		exit (0);	
	}
	
	return 0;
}

/*
W1 10 saniye
E
R1 10 saniye
E
R2 10 saniye
E
W2 10 saniye
E
R3 10 saniye
H
*/




