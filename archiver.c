#include "archiver.h"


//when archiving considering bufsizes >> (archive title + 1 file title)
fEl bufOut[BUFSIZ];
fEl bufInp[BUFSIZ];
size_t bufOutFilled;
size_t bufInpFilled;

const char blank[] = "     ";

errno_t archive(int argc, const char *argv[])
{
    int i = Ind_OF_frst_F_to_archivize_In_Argv;
    Tfcount fcount = argc - Ind_OF_frst_F_to_archivize_In_Argv;
	size_t currFsize;
	fnameSymb fname[MAX_fNAME_LEN];
    FILE *f = NULL, *farch;

	//attempting create arhive file
	if ((farch = fopen(argv[2], "wb")) == NULL) {// Temp  name, if it has the same as in directore  --- warn 
		fprintf(stderr, "Could not open file: %s\n", argv[2]);
		return errno; // Temp  name, if it has the same as in directore  --- warn 
	}else
		setbuf(farch, bufOut);

    //write title to arch
	strcpy(fname, archSignature);
	fwrite(fname, sizeof(fname[0]), strlen(fname) + 1, farch);//null symb is needed
	fwrite(&fcount, sizeof(fcount), 1, farch);	

	//arhive each file 
    while (i != argc) { 

		//attempting open specified file to read
		if ((f = fopen(argv[i], "rb")) == NULL) {
			fprintf(stderr, "Could not open file: %s\n", argv[i]);
			return errno;
		}

        //Write curr file atributes
		strcpy(fname,extractFName(argv[i]));
		Tfnamelen lenfname = strlen(fname);
		fwrite(&lenfname, sizeof(Tfnamelen), 1, farch);
		fwrite(fname, sizeof(fname[0]), strlen(fname) + 1, farch);//null symb is needed
		currFsize = fsize(f);
		fwrite(&currFsize, sizeof(size_t), 1, farch);

		fflush(farch);

        // Write curr file content; calculate checksum
		TCheckSUM checkSum = 0;
		bufInpFilled = 0;
		do
		{
			bufInpFilled = fread_s(bufInp, BUFSIZ, sizeof(fEl), BUFSIZ, f);
			if (bufInpFilled) {
				fwrite(bufInp, sizeof(fEl), bufInpFilled, farch);
				if (bufInpFilled - crc32_bitwise(bufInp, bufInpFilled, &checkSum))
					return err_checkSUM;
			}
		} while (bufInpFilled == BUFSIZ);

		//write check sum
		fwrite(&checkSum, sizeof(TCheckSUM), 1, farch);

		//attempting close curr file
		if (fclose(f) == EOF) {
			fprintf(stderr, "Could not close file: %s\n", argv[i]);
			return errno;
		}
        i++;
    }

	//attempting close archive file

	if (fclose(farch) == EOF) {
		fprintf(stderr, "Could not close file: %s\n", argv[2]);
		return errno;
	}
}

errno_t unArchive(int argc, const char *argv[])
{
	FILE *farch = NULL, *f = NULL;
	Tfcount fcount = 0;
	fnameSymb *fname = (fnameSymb *)calloc(MAX_fNAME_LEN, sizeof(fnameSymb));


	//opening farch for read
	if ((farch = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "Could not open file: %s\n", argv[2]);
		return errno;
	}

	//reading arch title
	bufInpFilled = fread(bufInp, sizeof(fEl), BUFSIZ, farch);//All archive head info will read cause its len << BUFSIZ; 
	strcpy_s(fname, MAX_fNAME_LEN * sizeof(fnameSymb), bufInp);//reading signature to fname, cause eco
	
	//Cheking if signature valid	
	//if (strcmp(fname, archSignature)) {			
	//	fprintf(stderr, "Mismatch of specified file and archive signatures: %s\n", argv[2]);
	//	return err_wrong_signature;
	//};

	//reading archived files count
	fcount = (Tfcount)*(bufInp + strlen(fname) + 1); //+ 1 to skip nullterminetion 

	// j - index of bufInp element which is to be processed next
	offset j = strlen(fname) + 1 + sizeof(fcount); 
	//unarch each file
	for (Tfcount i = 0; i < fcount; i++)
	{
		size_t currFsize;

		//skipping f name len, its was alredy checked before calling func unarch in func archSizeNotValid
		readBufedNelmnts((Tfnamelen *)&currFsize, sizeof(Tfnamelen), bufInp, &bufInpFilled, &j, BUFSIZ, farch);
		//reading curr f name considering part of it can be not load to buf
		readBufedNULLTermStr(fname, bufInp, &bufInpFilled, &j, BUFSIZ, farch);
		//reading curr f size considering part of it can be not load to buf
		readBufedNelmnts((fEl *)&currFsize, sizeof(size_t), bufInp, &bufInpFilled, &j, BUFSIZ, farch);
		
		//attempting to create unarchived file for write
		if ((f = fopen(strcat(extractFpath(argv[2]), fname), "wb")) == NULL) {
			fprintf(stderr,"Could not open file: %s\n", fname);
			return errno; // Temp  name, if it has the same as in directore  --- warn 
		}
		else setbuf(f, bufOut);

		//read archive file and unarch curr file
		size_t elmntsLeft = currFsize;
		while (elmntsLeft > 0) {
			if (elmntsLeft < BUFSIZ - j) {
				fwrite(bufInp + j, sizeof(fEl), elmntsLeft, f);
				j += elmntsLeft;
				elmntsLeft = 0;
			}
			else {
				fwrite(bufInp + j, sizeof(fEl), BUFSIZ - j, f);
				elmntsLeft -= (BUFSIZ - j);
				bufInpFilled = fread(bufInp, sizeof(fEl), BUFSIZ, farch);
				j = 0;
			}
		}

		//skipping checksum
		TCheckSUM dummy;
		readBufedNelmnts((fEl *)&dummy, sizeof(TCheckSUM)/sizeof(fEl), bufInp, &bufInpFilled, &j, BUFSIZ, farch);

		//attempting to close curr file
		if (fclose(f) == EOF) {
			fprintf(stderr, "Could not close file: %s\n", fname);
			return errno;
		}
	}
	
	//attempting to close farch
	if (fclose(farch) == EOF) {
		fprintf(stderr, "Could not close file: %s\n", argv[2]);
		return errno;
	}
}

errno_t verify(int argc, const char *argv[])
{
	//uses bufInp(for farch) and bufOut(for actual file) for comparison
	int i = Ind_OF_frst_F_to_archivize_In_Argv;
	Tfcount realfcount = argc - Ind_OF_frst_F_to_archivize_In_Argv;
	size_t realFsize, readFsize;
	fnameSymb realfname[MAX_fNAME_LEN], readfname[MAX_fNAME_LEN];
	FILE *f = NULL, *farch;
	
	//attempting open arhive file
	if ((farch = fopen(argv[2], "rb")) == NULL) {// Temp  name, if it has the same as in directore  --- warn 
		fprintf(stderr, "Could not open file: %s\n", argv[2]);
		return errno; // Temp  name, if it has the same as in directore  --- warn 
	}

	//validate signature of arch
	bufInpFilled = fread(bufInp, sizeof(fEl), BUFSIZ, farch);
	strcpy_s(realfname, MAX_fNAME_LEN * sizeof(fnameSymb), bufInp);
	if (strcmp(realfname, archSignature)) {//Cheking if signature valid				
		fprintf(stderr, "Mismatch of specified file and archive signatures.\n");
		return err_wrong_signature;
	};

	//reading count of archived files
	Tfcount fcount = (Tfcount)*(bufInp + strlen(realfname) + 1); //+ 1 to skip nullterminetion 

	//cheking if fcount = specified in console fcount
	if (fcount != realfcount)
	{
		fprintf(stderr, "Mismatch of specified in archive and real file count: %d <> %d\n", fcount, realfcount);
		return err_corrupt;
	}
	
	//setting farch pos to first archived file pos
	fseek(farch, strlen(archSignature) + 1 + sizeof(fcount), SEEK_SET); //+ 1 considering null termination

	//validate each file
	while (i != argc) {
		//reading fname len
		Tfnamelen readLenfname;
		fread(&readLenfname, sizeof(Tfnamelen), 1, farch);
		//read fname and look for file with such name in argv
		size_t realLenFname;
		if ((!(realLenFname = MyBinfgets(readfname, MAX_fNAME_LEN, farch))) || (readfname[realLenFname] != '\0') \
			|| (realLenFname - readLenfname)) {
			fprintf(stderr, "Invalid name of file number %d \n", CURR_FILE_ORD(i));
			return err_corrupt;
		}
		realfname[0] = '\0';
		for (size_t j = Ind_OF_frst_F_to_archivize_In_Argv; j < argc; j++)
			if (!strcmp(readfname, extractFName(argv[j]))) {
				strcpy(realfname, argv[j]);
				break;
			}
		if (!realfname[0]) {
			fprintf(stderr, "Unexpected file in archive: %s\n", readfname);
			return err_corrupt;//no such file in argv
		}

		//attempting open specified file to read
		if ((f = fopen(realfname, "rb")) == NULL) {
			fprintf(stderr,"Could not open file: %s\n", argv[i]);
			return errno;
		}


		//read fsize and compare with real f size
		if (!fread_s((size_t *)&readFsize, BUFSIZ, sizeof(size_t), 1, farch) \
			|| ((realFsize = fsize(f)) != readFsize)) {
			fprintf(stderr, "Mismatch of specified in archive and real size of file number %d: %d <> %d \n", CURR_FILE_ORD(i), readFsize, realFsize);
			return err_corrupt;
		}
		
		
		//compare file and archive contents, checksum cmp
		TCheckSUM realcheckSum = 0, readcheckSum = 0;
		bufOutFilled = 0;
		bufInpFilled = 0;
		do
		{
			bufInpFilled = fread_s(bufInp, BUFSIZ, sizeof(fEl), BUFSIZ, f);
			if (bufInpFilled) {
				bufOutFilled = fread_s(bufOut, BUFSIZ, sizeof(fEl), bufInpFilled, farch);
				if (bufInpFilled - crc32_bitwise(bufInp, bufInpFilled, &realcheckSum)) return err_checkSUM;
				if ((bufOutFilled < bufInpFilled) || (bufsAreDifferent(bufInp, bufOut, bufInpFilled))) {
					fprintf(stderr, "Archived content of file number %d is invalid.\n", CURR_FILE_ORD(i));
					return err_corrupt;
				}
			}
		} while (bufInpFilled == BUFSIZ);
		fread(&readcheckSum, sizeof(TCheckSUM), 1, farch);
		if (readcheckSum - realcheckSum) {
			fprintf(stderr, "Check sum of file number %d is invalid\n", CURR_FILE_ORD(i));
			return err_checkSUM;
		}

		//attempting close curr file
		if (fclose(f) == EOF) {
			fprintf(stderr,"Could not close file: %s\n", argv[2]);
			return errno;
		}
		i++;
	}

	//attempting close archive file
	if (fclose(farch) == EOF) {
		fprintf(stderr, "Could not close file: %s\n", argv[2]);
		return errno;
	}
}

errno_t archNotValid(int argc, const char *argv[])
{
	FILE *farch = NULL;
	Tfcount fcount = 0;
	fnameSymb *fname = (fnameSymb *)calloc(MAX_fNAME_LEN, sizeof(fnameSymb));

	//attempting open farch for read
	if ((farch = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "Could not open file: %s\n", argv[2]);
		return errno;
	}

	//reading arch title
	bufInpFilled = fread(bufInp, sizeof(fEl), BUFSIZ, farch);//All archive head info will read cause its len << BUFSIZ; 
	strcpy_s(fname, MAX_fNAME_LEN * sizeof(fnameSymb), bufInp);
	if (strcmp(fname, archSignature)) {//Cheking if signature valid				
		fprintf(stderr, "Mismatch of specified file and archive signatures: %s\n", argv[2]);
		return err_wrong_signature;
	};

	//reading archived file count
	fcount = (Tfcount)*(bufInp + strlen(fname) + 1); //+ 1 to skip nullterminetion of farch signature

	//setting farch pos to first archived file pos
	fseek(farch, strlen(archSignature) + 1 + sizeof(fcount), SEEK_SET); //+ 1 considering null termination
	
	//cheking size of each file
	for (Tfcount i = 0; i < fcount; i++)
	{
		size_t currFsize; fpos_t missedBytes;
		Tfnamelen realLenFname, readLenFname;

		//reading specified in archive Len(fname) 
		fread_s(&readLenFname, sizeof(Tfnamelen), sizeof(Tfnamelen), 1, farch);

		//reading curr f name considering part of it can be not load to buf 
		//checking if size(fname) was enought to read from arch 
		if ((!(realLenFname = MyBinfgets(fname, MAX_fNAME_LEN, farch))) || (fname[realLenFname] != '\0')\
			|| (realLenFname - readLenFname)) {
			fprintf(stderr, "Mismatch of specified in archive and real length of file name number %d.\n", i + 1);
			return err_corrupt;
		}

		//attempting to read curr fsize
		if (!fread((void *)&currFsize, sizeof(size_t), 1, farch)) {
			fprintf(stderr, "Invalid size of file number %d.\n", i + 1);
			return err_corrupt;
		}

		//attempting to determin conformity of specified and real fsize 
		if ((missedBytes = fbytesTillEOF(farch) - currFsize) < 0) {
			fprintf(stderr, "%s%s miss %d bytes\n", blank, fname, -missedBytes);
			return err_corrupt;
		}

		//process check SUM of current file and compare to defined in file
		TCheckSUM realcheckSum = 0, readcheckSum = 0;
		size_t bytesChecked = 0;
		bufInpFilled = 0;
		do
		{
			bytesChecked += (bufInpFilled = fread_s(bufInp, BUFSIZ, sizeof(fEl), (currFsize - bytesChecked) > BUFSIZ? BUFSIZ : (currFsize - bytesChecked), farch));
			if (bufInpFilled) {
				if (bufInpFilled - crc32_bitwise(bufInp, bufInpFilled, &realcheckSum)) return err_checkSUM;
			}
		} while ((bufInpFilled == BUFSIZ) && (bytesChecked < currFsize));
		fread(&readcheckSum, sizeof(TCheckSUM), 1, farch);
		if (readcheckSum - realcheckSum) {
			fprintf(stderr, "Check sum of file number %d is invalid\n", i + 1);
			return err_checkSUM;
		}

	}

	//attempting to close archive file
	if (fclose(farch) == EOF) {
		fprintf(stderr, "Could not close file: %s\n", argv[2]);
		return errno;
	}
}

errno_t archStats(int argc, const char *argv[])
{
	FILE *farch = NULL;
	Tfcount fcount = 0;
	fnameSymb *fname = (fnameSymb *)calloc(MAX_fNAME_LEN, sizeof(fnameSymb));


	//opening farch for read
	if ((farch = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr,"Could not open file: %s\n", argv[2]);
		return errno;
	}

	//reading arch title
	bufInpFilled = fread(bufInp, sizeof(fEl), BUFSIZ, farch);//All archive head info will read cause its len << BUFSIZ; 
	strcpy_s(fname, MAX_fNAME_LEN * sizeof(fnameSymb), bufInp);
	if (strcmp(fname, archSignature)) {//Cheking if signature valid				
		fprintf(stderr, "Mismatch of specified file and archive signatures: %s\n", argv[2]);
		return err_wrong_signature;
	};

	//reading count of archived files
	fcount = (Tfcount)*(bufInp + strlen(fname) + 1); //+ 1 to skip nullterminetion 
	fprintf(stdout, "Archive %s: file count = %u\n", argv[2], fcount);

	//setting farch pos to first archived file pos
	fseek(farch, strlen(archSignature) + 1 + sizeof(fcount), SEEK_SET); //+ 1 considering null termination
	
	//listing each file
	for (Tfcount i = 0; i < fcount; i++)
	{
		size_t currFsize;
		//skipping fname len
		fseek(farch, sizeof(Tfnamelen), SEEK_CUR);

		//reading curr arhived file name 
		MyBinfgets(fname, MAX_fNAME_LEN, farch);

		//reading curr arhived file size
		fread((void *)&currFsize, sizeof(size_t), 1, farch);
		fprintf(stdout, "%s%s: file size = %d\n", blank, fname, currFsize);

		//setting farch pos to next archived file pos
		fseek(farch, currFsize + sizeof(TCheckSUM), SEEK_CUR);	
	}

	//attempting to close farch
	if (fclose(farch) == EOF) {
		fprintf(stderr, "Could not close file: %s\n", argv[2]);
		return errno;
	}
}
