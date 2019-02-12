int tswitch();

int sleep(int event)
{
  printf("proc %d going to sleep on event=%d\n", running->pid, event);

  running->event = event;
  running->status = SLEEP;
  enqueue(&sleepList, running);
  printList("sleepList", sleepList);
  tswitch();
}

int wakeup(int event)
{
  PROC *temp, *p;
  temp = 0;
  printList("sleepList", sleepList);

  while (p = dequeue(&sleepList)){
     if (p->event == event){
	printf("wakeup %d\n", p->pid);
	p->status = READY;
	enqueue(&readyQueue, p);
     }
     else{
	enqueue(&temp, p);
     }
  }
  sleepList = temp;
  printList("sleepList", sleepList);
}

int kwait(int *status){
  
  int i;
  for(i=0; i<NPROC; i++){
    if(proc[i].ppid == running->pid && proc[i].status != FREE && proc[i].status != ZOMBIE){
      break;
    }
  }

  if(i == NPROC){
    //if it has no children, stop before we start
    printf("The process has no children to take care ofit!\n");
    return -1;
  }

  while(1){
    //find a zombie
    for(i = 0; i< NPROC; i++){
      //if zombie is found, stop waiting
      //printf("looking for zombie\n");
      if(proc[i].status == ZOMBIE && proc[i].ppid == running->pid){
        printf("found zombie\n");
        *status = proc[i].exitCode;
        proc[i].status = FREE;
        enqueue(&freeList, &proc[i]);
        return proc[i].pid;
      }
    }
    sleep(running->pid);
  }
}



int kexit(int exitvalue){
  int i;
  int good = 1;
  if(running->pid == proc[1].pid){
    for(i = 2; i < NPROC; i++){
      if(proc[i].status != FREE){
        good = 0;
        break;
      }
    }
    if(good){
      printf("We cant kill P1 while there are still other processes\n");
      return -1;
    }
  }
  //if we bout to murder some process
  running->exitCode = exitvalue;
  running->status = ZOMBIE;

  for(i=2; i< NPROC; i++){
    if(proc[i].ppid == running->pid){
      proc[i].ppid = proc[1].pid;
    }
  }
  //wake up the procs guardian to switch it
  wakeup((int)proc[running->ppid].event);
  tswitch();
}


  
