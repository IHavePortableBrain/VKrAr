#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAX_fNAME_LEN UCHAR_MAX

typedef unsigned int Tfcount;
typedef size_t offset;
typedef unsigned char fEl;
typedef unsigned char fnameSymb;
typedef unsigned char Tfnamelen;
typedef uint32_t TCheckSUM;

size_t fsize(FILE *f);

//fstr - adr for str --- malloced size is to be sufficient/; buf - buffer we are reading str from 
//bufInpFilled - ind of last valid el in buf, bufInpProcPos - ind of firs el wich wasnt processed
//f - file buf assigned to 
void readBufedNULLTermStr(fEl *fstr, fEl *buf, offset *bufInpFilled, offset *bufInpProcPos, size_t bufsize, FILE *f);

//res = number of el read
//fstr - adr for n felements --- malloced size is to be sufficient/; buf - buffer we are reading bytes from 
//bufInpFilled - ind of last valid el in buf, bufInpProcPos - ind of firs el wich wasnt processed
//f - file buf assigned to 
offset readBufedNelmnts(fEl *fstr, offset n, fEl *buf, offset *bufInpFilled, offset *bufInpProcPos, size_t bufsize, FILE *f);

fnameSymb *extractFName(const fnameSymb *fname);

fnameSymb *extractFpath(const fnameSymb *fname);

//copies file elements to dest until 00 byte met, in case 00 was not reached returns max_Len. 
//in case ret == max_Len calling code must check if  dest[max_Len - 1] = '\0' or size of dest is too small, because 00 symb was not reached  
//len == max_Len ? dest[len] = '\0' ? 42 : ferror;
//res = len sequence read
size_t *MyBinfgets(fEl *dest, size_t max_Len, FILE *f);

//returns len of byte sequence from curr file pos till EOF 
fpos_t fbytesTillEOF(FILE *f);

//bufsize - size of both bufs in bytes
char bufsAreDifferent(void *buf1, void *buf2, size_t bufsize);

//ret - count of checksumed bytes
//*adrprevCrc32 = checksum of ret bytes starting from adr;
size_t crc32_bitwise(const void *adr, size_t length, uint32_t *adrprevCrc32);

//almost trash___________________

//ret - checksumed bytes count
//increment *adrSUM by checksum of ret bytes of file
//adrf - adr of var FILE type wich is to be checksumed; 
//checks file from begining till EOF;saves file pos
size_t crc32_file(uint32_t *adrSUM, const FILE **adrf);

//ret - checksumed bytes count
//increment *adrSUM by checksum of ret bytes of file
//adrf - adr of var FILE type wich is to be checksumed, n - bytes to be checksumed; 
//checks file from current pos till EOF;file pos changes respectively
size_t crc32_nfile(uint32_t *adrSUM, const FILE **adrf, size_t n);

//ret = bytes copied;copies n bytes of content of fsrc to f dest.
//fdest is to be open as "wb" , fsrc - "rb"; pos of files changes accordingly
size_t fncpy(FILE *fdest, const FILE *fsrc, size_t n);