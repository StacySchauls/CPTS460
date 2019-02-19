int tswitch();

int ksleep(int event)
{
  int sr = int_off();
  printf("proc %d going to sleep on event=%d\n", running->pid, event);

  running->event = event;
  running->status = SLEEP;
  enqueue(&sleepList, running);
  printList("sleepList", sleepList);
  tswitch();
  int_on(sr);
}

int kwakeup(int event)
{
  PROC *temp, *p;
  temp = 0;
  int sr = int_off();
  
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
  int_on(sr);
}

int kexit(int exitValue)
{
  PROC *p;
  if (running->pid == 1)
  {
    printf("Cannot kill process 1\n");
    return;
  }

  for (int i = 0; i < NPROC; i++)
  {
    p = &proc[i];

    //processes get tied back to process 1 if they become orphaned 
    if(p->status != FREE && p->ppid == running->pid)
    {
      p->ppid = 1;
      p->parent = &proc[1];
    }
  }

  running->exitCode = exitValue;
  running->status = ZOMBIE;

  kwakeup(&proc[1]);
  kwakeup(running->parent);

  tswitch();
}

  //stacy's algo properly refree's the process
//book pseudo code 
int kwait(int *status)
{
  int i;
  for(i=0; i<NPROC; i++)
  {
    if(proc[i].ppid == running->pid && proc[i].status == READY);
      break;
  }

  if(i == NPROC)
  {
    printf("No child processess\n");
    return -1;
  }

  while(1){
    for(i = 0; i < NPROC; i++)
    {
      if(proc[i].status == ZOMBIE && proc[i].ppid == running->pid)
      {
        *status = proc[i].exitCode;
        proc[i].status = FREE;
        enqueue(&freeList,&proc[i]);
        return proc[i].pid;
      }
    }
    ksleep(running->pid);
  }
}

int do_wait()
{
  int status;
  int pid = kwait(&status);
  printf("\nZombie pid: %d\n", pid);
  printf("Zombie exitCode: %d\n", status);
}