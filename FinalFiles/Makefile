AS=as -Iinclude
LD=ld
CC=gcc
CPP=gcc -E -nostdinc -Iinclude
CFLAGS=-Wall -pedantic -W -nostdlib -nostdinc -Wno-long-long -I include -fomit-frame-pointer -fno-builtin -std=c99

HEAD_OBJS= us.o crt0.o uio.o ucode.o ../mtxlib
IHEAD_OBJS= us.o uio.o ucode.o ../mtxlib

.s.o:
	${AS} -a $< -o $*.o > $*.map


all: head ihead init login sh ls cat cp ps man mkdir rmdir rm link unlink \
	symlink	touch sync grep more lpr mount umount cdserver cdclient signal \
	itimer trap divide segcatcher matrix race norace qsort hits kill loop \
	vfork demandpage sbrk test mp l2u ptable

head:
	${AS} -o us.o us.s
	${CC} -c crt0.c
	${CC} -c uio.c
	${CC} -c ucode.c

ihead:
	${AS} -o us.o us.s
	${CC} -c uio.c
	${CC} -c ucode.c

init:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/

login:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
sh:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
ls:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
cat:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
cp:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
ps:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
man:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
mkdir:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
rmdir:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
rm:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/

link:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
unlink:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
symlink:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
touch:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
sync:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
grep:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
more:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
lpr:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
mount:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
umount:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
cdserver:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
cdclient:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
signal:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
itimer:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
trap:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
divide:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
dividecatcher:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
segcatcher:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
matrix:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
race:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
norace:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
qsort:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
hits:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
kill:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
loop:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
vfork:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
demandpage:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
sbrk:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
test:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
mp:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/

l2u:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/
ptable:  
	${CC} ${CFLAGS} -c $@.c 
	${LD} -T ld.script  ${HEAD_OBJS} $@.o -N  -o $@
	@wc -c $@; mv $@ bin/

install:
	vmware-mount /root/vmware/Other/Other.vmdk 3 /mnt
	cp -av bin/* /mnt/bin/
	vmware-mount -d /mnt

clean:
	rm -f bin/* *.o
