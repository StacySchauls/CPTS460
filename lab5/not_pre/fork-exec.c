
#include "loadelf.c"

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



int exec(char *cmdline){
    int i, upa, usp;
    char *cp, kline[128], file[32], filename[32];
    PROC *p = running;
    strcpy(kline, cmdline);
    //get first token of kline as filename
    cp = kline; i = 0;
    while(*cp != ' '){
        filename[i] = *cp;
        i++; cp++;
    }
    filename[i] = 0;
    file[0] = 0;
    //if filename relative
    if(filename[0] != '/'){
        strcpy(file, "/bin/"); //prefix with /bin/
    }
    strcat(file, filename);
    upa = p->pgdir[2048] & 0xFFFF0000; //PA of umode image
    if(!loadelf(file, p)){
        return -1;
    }

    //copy cmdline to high end of Ustack in Umode image
    usp = upa + 0x100000 - 128;
    strcpy((char *) usp, kline);
    p->usp = ((int *)VA(0x100000 - 128));
    //fix syscall fram in kstack to return to VA=0 of new image
    for(i = 2; i<14; i++){ //cleatr umode regs r1-r12
        p->kstack[SSIZE - i] - 0;
    }
    p->kstack[SSIZE - 1] = (int)VA(0);
    return (int)p->usp; //will replace saved r0 in the kstack
}


