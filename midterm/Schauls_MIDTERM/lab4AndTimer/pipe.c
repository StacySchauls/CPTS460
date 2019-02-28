#define NPIPE 10
#define PSIZE  8

typedef struct pipe{
  char buf[8];
  int head, tail;
  int data, room;
  int status;
}PIPE;

extern PROC *running;
extern PROC *readyQueue;
extern PIPE *kpipe;



PIPE pipe[NPIPE];


int pipe_init()
{
  int i;
  printf("pipe_init()\n");
  for (i=0; i<NPIPE; i++){
    pipe[i].status = 0;
  }
}

int show_pipe()
{
  PIPE *p = pipe;
  int i;
  printf("----------------------------------------\n");
  printf("room=%d data=%d buf=", p->room, p->data);
  for (i=0; i<p->data; i++)
    kputc(p->buf[p->tail+i]);
  printf("\n");
  printf("----------------------------------------\n");
}

int kpipe_()
{
  int i;
  PIPE *p = &pipe;
  p->head = p->tail = 0;
  p->data = 0; p->room = PSIZE;
  p->status = FREE;
}


PIPE *create_pipe()
{
  int i; PIPE *p;
  printf("creating pipe ....");
  for (i=0; i<NPIPE; i++){
    p = &pipe[i];
    if (p->status==0){
      p->status = 1;
      break;
    }
  }
  p->head = p->tail = p->data = 0;
  p->room = PSIZE;
  printf("OK\n");
  return p;
}

int read_pipe(PIPE *p, char *buf, int n)
{
  int ret;
  char c;
  
  if (n<=0)
    return 0;
  if(p->status == FREE){
    printf("Pipe broke\n");
    return -1;
  }
  show_pipe();

  while(n){
    printf("reader %d reading pipe\n", running->pid);
    ret = 0;
    while(p->data){
        *buf = p->buf[p->tail++];
        p->tail %= PSIZE;
        buf++;  ret++; 
        p->data--; p->room++; n--;
        if (n <= 0)
            break;
    }
    show_pipe();
    if (ret){   /* has read something */
       kwakeup(&p->room);
       return ret;
    }
    // pipe has no data
    printf("reader %d ksleep for data\n", running->pid);
    kwakeup(&p->room);
    ksleep(&p->data);
    continue;
  }
}
int write_pipe(PIPE *p, char *buf, int n)
{
  int r = 0; int w = 0;
  
  if (p->status == 0) return -1;
  if (n<=0) return 0;
  //printf("proc%d writing %d bytes to pipe\n", running->pid, n);
    
  while(n){
    w = 0;
    while(p->room){
      p->buf[p->head++] = *buf;
      p->head %= PSIZE;
      p->data++; p->room--; buf++; w++; r++; n--;
      if (n==0)
	    break;
    }
    show_buffer();
    printf("proc%d wrote %d bytes\n", running->pid, w);
    kwakeup((int)&p->data);
    if (n==0){
      printf("proc%d finished writing %d bytes\n", running->pid, r);
      return r;
    }
    ksleep((int)&p->room);
  }
}


int write_pipe_(PIPE *p, char *buf, int n)
{
  char c;
  int i = 0;
  int ret = 0; 
  printf("n: %d\n", n);
  printf("Before write: \n");
  show_pipe();
  while (n){
    printf("writer %d writing pipe\n", running->pid);
    while (p->room){
       p->buf[p->head] = *buf; 
       printf("wrote %c\n",p->buf[p->head]);
       p->head++;
       p->head  %= PSIZE;
       buf++;  ret++; 
       i++;
       p->data++; p->room--; n--;
       if (n==0){
         break;
         //show_pipe();
	       //kwakeup(&p->data);
	       //return ret;
       }
    }
    printf("After write\n");
    show_pipe();
    printf("writer %d ksleep for room\n", running->pid);
    kwakeup(&p->data);
    ksleep(&p->room);
  }
}


int pipe_writer(){
    struct uart *up = &uart[0];
    char line[128];;
    while(1){
    printf("Enter a line for task1 to get: ");
    //printf("task%d waits for line from UART0\n", running->pid, line);

    kgets(line);
    if(line[0] == 0){
      printf("line is null, exiting\n");
      kexit(running->pid);
    }
    printf("\r\n");
    printf("task%d writes line=[%s] to pipe\n", running->pid, line);
    write_pipe(kpipe, line, strlen(line));
    }
}

int pipe_reader(){
    char line[128];
    int i, n;
    while(1){
        printf("task%d readig from pipe\n", running->pid);
        n = geti();
        if(n == 0){
          printf("n is 0. nno data. Exit\n");
          kexit(running->pid);
        }
        printf("task%d read n=%d bytes from pipe : [", running->pid);
        for(i=0;i<n;i++){
            kputc(line[i]);
        }
        printf("]\n");
    }
}
 /* old before port to arm */
 /*
int pipe_reader()
{
  char line[128];
  int nbytes, n;
  PIPE *p = &pipe;
  printf("proc %d as pipe reader\n", running->pid);
 
  while(1){
    printf("input nbytes to read : " );
    scanf("%d", &nbytes); getchar();
    n = read_pipe(p, line, nbytes);
    line[n] = 0;
    printf("Read n=%d bytes : line=%s\n", n, line);
  }
}


int pipe_writer()
{
  char line[128];
  int nbytes, n;
  PIPE *p = &pipe;
  printf("proc %d as pipe writer\n", running->pid);

  while(1){
    printf("input a string to write : " );

    fgets(line, 128, stdin);
    line[strlen(line)-1] = 0;

    if (strcmp(line, "")==0)
       continue;

    nbytes = strlen(line);
    printf("nbytes=%d buf=%s\n", nbytes, line);
    n = write_pipe(p, line, nbytes);
    printf("wrote n=%d bytes\n", n);
  }
}
*/


