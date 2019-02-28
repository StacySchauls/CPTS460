#define NPIPE 10
#define PSIZE  8


typedef struct pipe{
  char buf[8];
  int head, tail;
  int data, room;
  int status;
}PIPE;

PIPE pipe;


int pipe_init()
{
  int i;
  printf("pipe_init()\n");
    pipe.status = 2;
}


int show_pipe()
{
  PIPE *p = &pipe;
  int i;
  printf("----------------------------------------\n");
  printf("room=%d data=%d buf=", p->room, p->data);
  for (i=0; i<p->data; i++)
    putchar(p->buf[p->tail+i]);
  printf("\n");
  printf("----------------------------------------\n");
}
int kpipe()
{
  int i;
  PIPE *p = &pipe;
  p->head = p->tail = 0;
  p->data = 0; p->room = PSIZE;
}

int read_pipe(PIPE *p, char *buf, int n)
{
  int ret;
  char c;
  
  if (n<=0){
    return 0;
    pipe.status = 0;
    printf("Changing pipe status to 0\n");
    printf("pipe status: %d\n", pipe.status);
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
    
    printf("reader %d sleep for data\n", running->pid);
    kwakeup(&p->room);
    ksleep(&p->data);
    continue;
  }
}

int write_pipe(PIPE *p, char *buf, int n)
{
  char c;
  int ret = 0; 


  show_pipe();
  while (n){
    printf("writer %d writing pipe\n", running->pid);
    while (p->room){
       p->buf[p->head++] = *buf; 
       p->head  %= PSIZE;
       buf++;  ret++; 
       p->data++; p->room--; n--;
       if (n<=0){
         show_pipe();
	 kwakeup(&p->data);
	 return ret;
       }
    }
    show_pipe();
    printf("writer %d sleep for room\n", running->pid);
    kwakeup(&p->data);
    ksleep(&p->room);
  }
}
 
int pipe_reader()
{
  char line[128];
  int nbytes, n;
  PIPE *p = &pipe;
  printf("proc %d as pipe reader\n", running->pid);
 
  while(1){

    printf("input nbytes to read : " );
    //scanf("%d", &nbytes); getchar();
    nbytes = geti();
    if(nbytes == 0){
      printf("nbytes is 0, no data. Exit.\n");
      pipe.status = 0;
      kexit(running->pid);
    }
    n = read_pipe(p, line, nbytes);
    line[n] = 0;
    printf("Read n=%d bytes : line=%s\n", n, line);
  }
}


int pipe_writer()
{
  //struct uart *up = &uart[0];
  char line[128];
  int nbytes, n;
  PIPE *p = &pipe;
 


  while(1){
     printf("proc %d as pipe writer\n", running->pid);
    printf("pipe status = %d\n",pipe.status);
    if(pipe.status == FREE){
    printf("Broken PIPE\n");
    return -1;
  }
    printf("input a string to write : " );
    kgets(line);
    //fgets(line, 128, stdin);
    if(line[0] == 0){
      printf("Line is null. exit\n");
      kexit(running->pid);
    }
    line[strlen(line)] = 0;

    if (strcmp(line, "")==0)
       continue;

    nbytes = strlen(line);
    printf("nbytes=%d buf=%s\n", nbytes, line);
    n = write_pipe(p, line, nbytes);
    printf("wrote n=%d bytes\n", n);
  }
}


