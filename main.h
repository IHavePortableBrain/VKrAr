#pragma once
#include <string.h>
#include <errno.h>

#include "archiver.h"

#define MSG_LEN 1024 

void errproc(errno_t error_num);