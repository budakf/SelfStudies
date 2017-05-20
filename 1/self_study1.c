/*
Fatih BUDAK
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>     
#include <sys/shm.h>       
#include <errno.h>          
#include <semaphore.h>      
#include <fcntl.h>  
							
		
int * array;	
int * which;
//

void function(int * id){
	
	if(*id==0){
		int i,n,M;
		int x=0;
		n=array[0];
		M=array[1];
		for(i=4;i<n+4;i++){
			if(array[i]<=M)
				x++;
		}
		array[2]=x;
		printf("Cocuk_1: \"<= M\" olan eleman sayisi x=%d\n",x);
		
		printf("Cocuk_1: B dizisinin baslangic adresi:%d\n",&array[n+4]);
		printf("Cocuk_1: B={");
		int j=0;
		for(i=4;i<n+4;i++){
			if(array[i]<=M){
				printf("%d",array[i]);
				j++;
				if(j<x)
					printf(",");
			}
			
		}
		printf("}\n");
		
	}
	
	else {
		int i,n,M;
		int y=0;
		n=array[0];
		M=array[1];
		for(i=4;i<n+4;i++){
			if(array[i]>M)
				y++;
		}
		array[3]=y;
		printf("Cocuk_2: \"> M\" olan eleman sayisi y=%d\n",y);
		
		printf("Cocuk_2: C dizisinin baslangic adresi:%d\n",&array[n+4+array[2]]);
		
		printf("Cocuk_2: C={");
		int j=0;
		for(i=4;i<n+4;i++){
			if(array[i]>M){
				printf("%d",array[i]);
				j++;
				if(j<y)
					printf(",");
			}
			
		}
		printf("}\n");
		
	}
	
}

int main(){
	
	int n,M,i;
	pid_t pid;
	int shmid,shmid2;            
	sem_t *sem;
	printf("A dizisinin eleman sayisini (n) giriniz:");
	scanf("%d",&n);
	srand(time(NULL));
	//key_t key_value=ftok ("/dev/null", 3);
	
	shmid = shmget (IPC_PRIVATE/*key_value*/, sizeof (int)*(4+2*n), 0644 | IPC_CREAT);
	shmid2= shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0644);
	
	if (shmid < 0){                           
        	perror ("shmget\n");				
        	exit (1);
	}
	
	if (shmid2 < 0){                          
	        perror ("shmget\n");
		exit (1);
	}
	
	array = (int *) shmat (shmid, NULL, 0);
	which= (int *) shmat (shmid2, NULL, 0);
	*which=0;
	sem = sem_open ("Semaforroo", O_CREAT | O_EXCL, 0644, 1);  // sem_open() ile isimli semafor olusturduk ismi:Semaforroo:)
	sem_unlink ("Semaforroo");	
	array[0]=n;
	
	printf("Olusturulan A dizisi A:{");
	for(i=4;i<n+4;i++){
	    int producted_value = rand()%100; 	
	    array[i]=producted_value;
	    printf("%d",array[i]);
	    if(i!=n+3)
	    	printf(",");
	}
	printf("}\n");
	
	
	printf("A dizisinin baslangic adresi: %d\n" ,&(array[4]));
	
	printf("M degerini giriniz:");	
	scanf("%d",&M);
	array[1]=M;

	for (i = 0; i < 2; i++){
        pid = fork ();
        if (pid < 0)              
            printf ("Fork error.\n");
        else if (pid == 0)		
            break;                  
	}
	
	if (pid != 0){								//Anne proses
        
        while (pid = waitpid (-1, NULL, 0)){	//anne proses sonlanmak için çocuk prosesleri bekliyor 
            if (errno == ECHILD)
                break;
        }
     
        shmdt (array);	//shmdt() fonksiyonu, prosesin bellek bölgesini kullanymy sona erdi?inde bellek ile olan ili?kisi bitirmektedir.
        shmctl (shmid, IPC_RMID, 0);	//  Bellek bölgesinin kullanymy bitti?inde stmctl() kullanylarak geri verilmelidir..
        shmdt (which);
	shmctl (shmid2, IPC_RMID, 0);
        sem_destroy (sem);
        exit (0);
    	} 

	else  {						//Çocuk Prosesler									
       		sem_wait (sem);     			// P iþlemi 
        	sleep (2);
        	function(which);
        	(*which)++; 
        	sem_post (sem);          		// V iþlemi
	        exit (0);
    	}

	
	
	
	
	return 0;
}
