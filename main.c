#include "main.h"
//#define DEBUG
//проверка на длину скопированной с буфера строки

errno_t err;
char error_buf[MSG_LEN];

const char cmd_archive[] = "-a";
const char cmd_unarchive[] = "-u";
const char cmd_list[] = "-l";
const char cmd_verify[] = "-v";

#ifdef DEBUG
int main() {

	//int argc = 7;
	//unsigned char *argv[255];
	//for (int i = 0; i < 255; i++)
	//	argv[i] = (char *)calloc(255, sizeof(char));
	//strcpy(argv[1], "-v");
	//strcpy(argv[2], "10 + pdf1 + vid + winter");
	//strcpy(argv[3], "test\\10.txt");
	//strcpy(argv[4], "test\\pdf1.pdf");
	//strcpy(argv[5], "test\\vid.mp4");
	//strcpy(argv[6], "test\\winter.jpg");

	
	int argc = 3;
	unsigned char *argv[255];
	for (int i = 0; i < 255; i++)
		argv[i] = (char *)calloc(255, sizeof(char));
	strcpy(argv[1], "-u");
	strcpy(argv[2], "511+513");
	//strcpy(argv[3], "test\\511.txt");
	//strcpy(argv[4], "test\\513.txt");

	//int argc = 9;
	//unsigned char *argv[255];
	//for (int i = 0; i < 255; i++)
	//	argv[i] = (char *)calloc(255, sizeof(char));
	//strcpy(argv[1], "-a");  
	//strcpy(argv[2], "E:\\a");
	//strcpy(argv[3], "D:\\АрхивУчебный\\Лабы2Сем\\lab3zad3.docx");
	//strcpy(argv[4], "D:\\АрхивУчебный\\Лабы2Сем\\блок7\\Вариант15_lab7.doc");
	//strcpy(argv[5], "D:\\АрхивУчебный\\Лабы2Сем\\Блок6\\6.3\\Win32\\Debug\\Lab6Task3.exe");
	//strcpy(argv[6], "D:\\АрхивУчебный\\ucheba\\Фотки начерталки\\Тетрадь решение\\14.jpg");
	//strcpy(argv[7], "D:\\$ 3 сем\\ТИ\\Лаба 3 RSA\\Win32\\Debug\\тес\\Win.wav");
	//strcpy(argv[8], "D:\\$ 3 сем\\ТИ\\Лаба 3 RSA\\Win32\\Debug\\тес\\Landscape - 757.mp4");

	
	int m = atoi("b13.txt");
#endif // DEBUG

#ifndef DEBUG
int main(int argc, const char *argv[]) {
#endif 
 
//#define test
#ifdef  test
	printf(stdout, "Start loop argv v chek");
	for (size_t i = 0; i < argc; i++)
		fprintf(stdout, "%s ", argv[i]);
	printf(stdout, "End loop argv v chek");
	system("pause");
#endif //  test


	if ((strcmp(argv[1], cmd_archive) == 0) && argc >= 4)
	{
		err = archive(argc, argv);
		if (!err)
			fprintf(stdout, "Archive created.\n");
		else errproc(err);
	}
   
    else if ((strcmp(argv[1], cmd_unarchive) == 0) && argc == 3)
    {

		if (!(err = archNotValid(argc, argv)) && !(err = unArchive(argc, argv)))
			fprintf(stdout, "Archive unpacked.\n");
		else errproc(err);
    }

	else if ((strcmp(argv[1], cmd_list) == 0) && argc == 3)
	{
		if (!(err = archNotValid(argc, argv)) && !(err = archStats(argc, argv)))
			fprintf(stdout,"Archive is valid.\n");
		else errproc(err);
	}

    else if((strcmp(argv[1], cmd_verify) == 0) && argc >= 4)
    {
		if (!(err = verify(argc, argv)))
			fprintf(stdout, "Archive verified.\n");
		//else errproc(err);
    }
    
    else {
		err = err_inv_args;
		errproc(err);
    }

#ifdef  test
	system("pause");
#endif //  test
}


void errproc(errno_t error_num) {
	errno_t error;
	switch (error_num)
	{
	case err_wrong_signature:
			fprintf(stderr, "Error message: wrong file signature\n");
		break;
	case err_corrupt:
		fprintf(stderr, "Error message: archive corrupted\n");
		break;
	case err_inv_args:
		fprintf(stderr, "Error message: invalid arguments\n");
		break;
	case err_checkSUM:
		fprintf(stderr, "Error message: invalid checksum\n");
		break;	
	default:
		error = strerror_s(error_buf, MSG_LEN, error_num);

		//error =  result of determing error_num message
		switch (error) {
		case EINVAL:
			fprintf(stderr, "strerror_r() failed: invalid error code, %d\n", error);
			break;
		case ERANGE:
			fprintf(stderr, "strerror_r() failed: buffer too small: %d\n", MSG_LEN);
		case 0:
			fprintf(stderr, "Error message : %s\n", error_buf);
			break;
		default:
			fprintf(stderr, "strerror_r() failed: unknown error, %d\n", error);
			break;
		}
		break;
	}
}
