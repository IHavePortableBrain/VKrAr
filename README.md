# Archiver
A C Program which has the capability to archive files, 
unpack an archive file, display data about an archive file, 
and check the status of an archive file.

Command Line Formats : archiver [-a|-u|-l|-v] [archiveSize] archivename [file1 file2 . . . fileN]

• archiver -a archivename file1 file2 ... fileN
Create an archive with the specified 
name from the specified files. The original files should remain unchanged.
The number of files can vary.

• archiver -u archivename  
Unnpacked files in the directory of archive
“Unpack” the specified archive and generate each file contained
within. The original archive should remain unchanged.

• archiver -l archivename
Determines arhived files have specified size.
Prints the total size of the archive, the number of files in the archive, 
and each filename along with the corresponding file size (one file name and size per line)

• archiver -v archivename file1 file2 ... fileN 
Determine whether or not the specified archive is damaged. 

There are three possible outcomes for the -v flag:
The archive correctly contains all N files. In this case, the program should print the
message “Archive verified.".
– The archive is missing some data. In this case, your program should print “Archive is
missing X bytes”, where X is the number of missing bytes.
– The archive has N files, and is the correct size to contain the specified files, but some
of the data is incorrect. In this case, your program should print to stdout the message
“Archive is corrupted”.

COde of check sum borrowed from http://www.cyberforum.ru/c-beginners/thread1306788.html author - schdub