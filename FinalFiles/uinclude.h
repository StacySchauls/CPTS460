/* uinclude.h file */

#define printk printf
int printf(char *fmt,...);

typedef unsigned char       u8 ;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;

typedef struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
} DIR;

typedef struct stat {
  u16    st_dev;		/* major/minor device number */
  u16    st_ino;		/* i-node number */
  u16    st_mode;		/* file mode, protection bits, etc. */
  u16    st_nlink;		/* # links; TEMPORARY HACK: should be nlink_t*/
  u16    st_uid;			/* uid of the file's owner */
  u16    st_gid;		/* gid; TEMPORARY HACK: should be gid_t */
  u16    st_rdev;
  long   st_size;		/* file size */
  long   st_atime;		/* time of last access */
  long   st_mtime;		// time of last modification
  long   st_ctime;		// time of creation
  long   st_dtime;
  long   st_date;
  long   st_time;
} STAT;


// UNIX <fcntl.h> constants: <asm/fcntl.h> in Linux
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#define O_CREAT		   0100	/* not fcntl */
#define O_TRUNC		  01000	/* not fcntl */
#define O_APPEND	  02000

#define EOF  -1

#define exit mexit
/*
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR   2
*/

void prints();
void print2f();

int find_cmd();

int getpid(), getppid(), fork(), exec(), wait(), exit(), tswitch();

int mkdir(), rmdir(), creat(), open(), read(), write(), lseek(), close();
int mount(), umount();

int fixtty(),gettty(); 
int itierm();

int chdir(),chuid();
int dup(),pipe(),command();
int eatpath(),pwd(),fisan();
int signal();
int stat(), fstat();
int link(), unlink(), symlink(), readlink();

int getcs(), texit(), thread(), tjoin();
int touch();

int mutex_creat(), mutex_lock(), mutex_unlock(), mutex_destroy();

int getaddr();
int syscall();
int getc();

int uputc(char);
int gets();

void ufork();
void uwait();
void uexec();

void show_menu();
void ps();
void chname();
void kmode();
void kswitch();
void uexit();
void invalid();
void uls();

char *strcpy(), *strcat(), *strncpy();
int strcmp(), atoi(); //strlen();
void align();
int send(), recv();
int itimer();
int getline(), strncmp();
/***********************
int strcat(char *s1, char *s2)
{
  while(*s1)
    s1++;
  while(*s2)
    *s1++ = *s2++;
  *s1 = 0;
}

int strncpy(char *s1, char *s2, int n)
{
  char *p = s1;
  while(n && *s2){
    *s1++ = *s2++;
    n--;
  }
  *s1 = 0;
  return (int)p;
}  
***********************/
