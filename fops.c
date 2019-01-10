#include "fops.h"

size_t fsize(FILE *f) {
	size_t pos, len;
	pos = ftell(f);
	fseek(f, 0L, SEEK_END);
	len = ftell(f);
	fseek(f, pos, SEEK_SET);
	return len;
}

void readBufedNULLTermStr(fEl *fstr, fEl *buf, offset *bufInpFilled,offset *bufInpProcPos, size_t bufsize,FILE *f) {
#define j bufInpProcPos	
	offset k = 0;
	do {
		fstr[k++] = buf[(*j)++];
	} while (*j < *bufInpFilled && buf[*j - 1]);//cpystr until prev copied sumb was NULL
	if (*j == *bufInpFilled) {
		*j = 0;
		*bufInpFilled = fread(buf, sizeof(fEl), bufsize, f);
	}
	if (fstr[k - 1]) {  //part of fname is not in that block(size(block) = BUFSIZ)
		do {
			fstr[k++] = buf[(*j)++];
		} while (buf[*j - 1]);// fname << buf size so dont check if j >= bufsize in cycle and after it
	}
#undef j
}

offset readBufedNelmnts(fEl *fElSeq,offset n,fEl *buf, offset *bufInpFilled, offset *bufInpProcPos, size_t bufsize, FILE *f) {
#define j bufInpProcPos	
	offset k = 0;
	while (*j < *bufInpFilled && k < n){
		fElSeq[k++] = buf[(*j)++];
	};
	if (*j == *bufInpFilled) {
		*j = 0;
		*bufInpFilled = fread(buf, sizeof(fEl), bufsize, f);
	}
	if (k < n) {  //part of n sequence is not in that block(size(block) = bufsize)
		do {
			fElSeq[k++] = buf[(*j)++];
		} while (k < n);// fname << buf size so dont check if j >= bufsize in cycle and after it
	};
	return k;
#undef j
}

fnameSymb *extractFName(const fnameSymb *fname) {
	unsigned int i = strlen(fname) - 1;
	while (i > 0 && fname[i - 1] != '\\') i--;
	fnameSymb *res = (fnameSymb *)calloc(MAX_fNAME_LEN, sizeof(fnameSymb));
	res = strcpy(res, fname + i);
	return res;
}

fnameSymb *extractFpath(const fnameSymb *fname) {
	unsigned int i = strlen(fname) - 1;
	while (i > 0 && fname[i - 1] != '\\') i--;
	fnameSymb *res = strcpy((fnameSymb *)calloc(MAX_fNAME_LEN, sizeof(fnameSymb)), fname);
	res[i] = '\0';
	return res;
}

size_t *MyBinfgets(fEl *dest, size_t max_Len, FILE *f) {
	fEl *buf = (fEl *)calloc(max_Len, sizeof(fEl));
	fpos_t old = ftell(f);
	size_t len = 0;
	if (fread_s(buf, max_Len, sizeof(fEl), max_Len, f) <= 0)
		return 0;
	do {
		dest[len] = buf[len];
	} while ((len < max_Len) && buf[len++]);
	len--;//last iteration len correction
	fseek(f, old + len + 1, SEEK_SET);
	free(buf);
	return len;
}

fpos_t fbytesTillEOF(FILE *f) {
	fpos_t old = ftell(f), pos;
	fseek(f, 0, SEEK_END);
	pos = ftell(f);
	fseek(f, old, SEEK_SET);
	return pos - old;
}

char bufsAreDifferent(void *buf1, void *buf2,size_t bufsize) {
	for (size_t i = 0; i < bufsize; i++)
		if (*((unsigned char *)buf1 + i) - *((unsigned char *)buf2 + i))
			return 1;
	return 0;
}

size_t crc32_bitwise(const void *adr, size_t length, uint32_t *adrprevCrc32) {
	unsigned int j;
	uint32_t crc = ~(*adrprevCrc32);
	size_t i = 0;
	unsigned char *current = (unsigned char *)adr;
	while (++i < length) {
		crc ^= *current++;
		for (j = 0; j < 8; j++)
			crc = ((crc & 1)
				? (crc >> 1) ^ 0xEDB88320
				: (crc >> 1));
	}
	*adrprevCrc32 = ~crc;
	return i;
}

// almost trash_______________________________________

size_t crc32_file(uint32_t *adrSUM, const FILE **adrf) {
	//int len;
	//fpos_t old = ftell(*adrf);
	//fseek(*adrf, 0, SEEK_SET);
	//unsigned char buf[BUFSIZ];
	//uint32_t crc32 = 0;
	//while ((len = fread(buf, sizeof(buf[0]), BUFSIZ, *adrf)) != 0) {
	//	crc32 = crc32_bitwise(buf, len, crc32);
	//}
	//fseek(*adrf, old, SEEK_SET);
	//return crc32;
}

size_t crc32_nfile(uint32_t *adrSUM, const FILE **adrf, size_t n) {
	//int len; size_t res = 0;
	//unsigned char buf[BUFSIZ];
	//uint32_t crc32 = 0;
	//while ((res < n + 1) && (len = fread(buf, sizeof(buf[0]), BUFSIZ,*adrf)) != 0) {
	//		crc32 = crc32_bitwise(buf, len, crc32);
	//}
	//return crc32;
}

size_t fncpy(FILE *fdest, const FILE *fsrc, size_t n) {

}