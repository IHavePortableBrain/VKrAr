#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "fops.h"

#define err_wrong_signature -1
#define err_corrupt -2
#define err_inv_args -3 
#define err_checkSUM -4 

#define Ind_OF_frst_F_to_archivize_In_Argv 3
#define CURR_FILE_ORD(i) (i) + 1 - Ind_OF_frst_F_to_archivize_In_Argv
#define archSignature ("VKr")


errno_t archive(int argc, const char *argv[]);

errno_t unArchive(int argc, const char *argv[]);

//res = 0 if archive is invalid; res <> 0 if error occured 
//needs access for files witch were archived in this archive
errno_t verify(int argc, const char *argv[]);

//return err_fclose - this err is not critical so may print arch size is verified
//can determin only if each file size is valid, in case of corruption more likely wont determine what file size is unsaficient
errno_t archNotValid(int argc, const char *argv[]);

errno_t archStats(int argc, const char *argv[]);