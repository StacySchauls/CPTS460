int kprintf(char *, ...);

int strlen(const char *s)
{
  int i = 0;
  while(*s){
    i++; s++;
  }
  return i;
}

int strcmp(const char *s1, const char *s2)
{
  while((*s1 && *s2) && (*s1==*s2)){
      s1++; s2++;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}

int strncmp(const char *s1, const char *s2, int n)
{
  while((*s1 && *s2) && (*s1==*s2) && n){
    s1++; s2++; n--;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}

int strcpy(char *dest, const char *src)
{
  char *cp = dest;
  //  printf("strcpy: src=%s ", src);

  while(*src){
    // mputc(*src);
    *dest = *src;
    dest++; src++;
  }
  *dest = 0;
  // printf("cp=%s ", cp);
}

char *strncpy(char *dest, const char *src, int n)
{
  //printf("strncpy ");
  while(*src && n){
    *dest++ = *src++;
    n--;
  }
  // printf("dest=%s ", dest);
}

int kstrcpy(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}

char *kstrcat(char *dest, const char *src)
{
  char *cp = dest;

  while(*cp){
    cp++;
  }

  while(*src){
    *cp++ = *src++;
  }

}

char *strcat(char *dest, const char *src)
{
  char *cp = dest;

  while(*cp){
    //mputc(*cp);
    cp++;
  }
  while(*src){
    *cp = *src;
    cp++; src++;
  }
  // printf("dest=%s  ", dest);
}

char *strncat(char *dest, const char *src, int n)
{
  char *cp = dest;
  while(*cp)
    cp++;
  while(*src && n){
    *cp++ = *src++;
    n--;
  }
}

void *memcpy(void *dest, const void *src, int n)
{
  while(n){
    *((u32 *)dest++) = *((u32 *)src++);
    n -= 4;
  }
}

int atoi(char *s)
{
  int v = 0;
  while (*s){
    v = 10*v + (*s - '0');
    s++;
  }
  //kprintf("v=%d\n", v);
  return v;
}
int geti()
{
  char s[16];
  getline(s);
  return atoi(s);
}
