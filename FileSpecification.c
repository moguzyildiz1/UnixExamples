#include <stdlib.h>	//for realpath
#include <stdio.h>	//for printf()
#include <sys/types.h>
#include <string.h>
#include <errno.h>	//for strerror()
#include <ftw.h>
#include <dirent.h>	//readdir are defined here.
#include <sys/param.h> //"PATH_MAX" defined here.
#include <sys/stat.h> //"PATH_MAX" defined here.

extern char* program_invocation_name;
/**
	Displays the full file path to the current executable on Unix.
*/
static void realpath_call(char *path){

	char resolved_path[PATH_MAX];

	if(realpath(path,resolved_path)==0){
		fprintf(stderr, "realpath failed: %s\n",strerror(errno));
	}else{
		printf("Program's full path is: %s\n",resolved_path);
	}
}

void testRealPathCall(){

	char* pg="fse";
	printf("Program called as: %s\n",pg);
	realpath_call(pg);
	realpath_call(program_invocation_name);
}
/////////////////////////////////////////////////////////////////////////////////
/**
	Displays getting file size using the Unix system call stat.
*/
static unsigned filesize(char *filename){

	struct stat sb;
	if(stat(filename,&sb)!=0){
		fprintf(stderr, "'stat' failed on:%s : %s\n",filename,strerror(errno));
		exit(EXIT_FAILURE);
	}
	return sb.st_size;
}

void testFilesize(){

	char* pg="ListDirectoryRec.c";
	printf("Program called with: %s and program_invocation_name\n",pg);
	printf("Size of files: %d and %d bytes...\n",filesize(pg),filesize(program_invocation_name));
}
/////////////////////////////////////////////////////////////////////////////////
/**
	Displays what type of buffering is being used for open files:
	-no buffering
	-line buffering
	-full buffering
*/
static unsigned buffer_detect(const char *filename, FILE *fp){

	printf("Stream = %s, ",filename);
	if(fp->_flags&_IONBF)
		printf("unbuffered");
	else if(fp->_flags & _IOLBF)
		printf("line buffered");
	else 
		printf("fully buffered");
	printf(", buffer size\n");
}

void testBufferDetector(){

	FILE *fp;
	#if 0
		fputs("enter any character\n",stdout);
		if(getchar()==EOF)
			err(1,"getchar error");
		fputs("one line to standart error\n",stderr);
	#endif
	buffer_detect("stdin",stdin);
	buffer_detect("stdout",stdout);
	buffer_detect("stderr",stderr);
	fp=fopen("/etc/motd","r");
	if(fp==0)
		printf("fopen error\n");
	if(getc(fp)==EOF)
		printf("getchar error\n");
	buffer_detect("/etc/motd",fp);	
}

/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char const *argv[])
{
	//testRealPathCall();
	//testFilesize();
	testBufferDetector();
	return 0;
}