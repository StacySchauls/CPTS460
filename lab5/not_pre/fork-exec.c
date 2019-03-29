int fork(){
    printf("In the new fork now :) \n");
    int i;
    char *PA, *CA;
    PROC *p = dequeue(&freeList);
printf("here1\n");
    if(p==0){
        printf("fork failed");
        return -1;
    }

    p->ppid = running->pid;
    printf("new id should be %d\n", p->pid);
    p->parent = running;
    p->status = READY;
    p->priority = 1;
    printf("here2\n");
    PA = running->pgdir[2048] & 0xFFFF0000;  //parent Umode PA
    CA =  p->pgdir[2048] & 0xFFFF0000;       //child Umode PA
    printf("her32\n");
    memcpy(CA,PA, 0x10000);    //copy 1MB Umode image
    printf("her4\n");
    for(i = 1; i <=14; i++){
        p->kstack[SSIZE - i] = running->kstack[SSIZE - i];
    }
    p->kstack[SSIZE - 14] = 0;      //child return pid = 0
    p->kstack[SSIZE - 15] = (int)goUmode;         //child resumes to goUmode
printf("here3\n");

    p->ksp = &(p->kstack[SSIZE-28]);
    p->usp = running->usp;
    p->cpsr = running->cpsr;
    enqueue(&readyQueue, p);
    printf("exi\n");
    return p->pid;
}


