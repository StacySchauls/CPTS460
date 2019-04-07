#ifndef __READ__
#define __READ__

#include "type.h"

extern MINODE minode[NMINODES];
extern MINODE *root;
extern PROC proc[NPROC], *running;
extern char gpath[255];
extern char *name[]