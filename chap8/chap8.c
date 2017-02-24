#include "syscalls.h"

main() /* copy input to output */ {
	char buf[BUFSIZ]; 
	int n;
	
	while ((n = read(0, buf, BUFSIZ)) > 0) // read BUFSIZ bytes from fd=0=stdin, into buffer buf for until we read EOF or an error occurred. 
		write(1, buf, n); // write as many bytes as we just read, n, from buf, to fd=1=stdout
	
	return 0; 
}

/* getchar: unbuffered single character input */ 
int getchar(void)
{
	char c;

	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF; // read one byte into c from fd=stdin. if it returns 1, we read 1 char which is what we wanted, otherwise, it must have returned EOF or 0 for an error. 

//
// don't forget the reason for this function returning an int instead of a char. 
// it makes it convinient for signaling errors and EOF while simultaneously allowing us to return any valid char value. 
// Also don't forget the reason for the cast to unsigned char. Recall the whether or not
// char is signed or unsigned in arithmetic expressions is machine dependent. If we
// ran this code on a machine where char is signed by default, then the value returned
// could be signed extended and result in a different value begin returned than what was read. 
// e.g. if we just read the value 0x80=128, without the cast to unsigned char we would return
// 0xFFFFFF80 instead of 0x00000080.
//

}


/* getchar: simple buffered version */ 
int getchar(void)
{
	static char buf[BUFSIZ]; 
	static char *bufp = buf; 
	static int n = 0; // remember static variables are only initialized once,
	//at before the start of a program.

	if(n==0){ 
		/*bufferisempty*/ 
		n = read(0, buf, sizeof buf); // read from fd=stdin into destination buffer BUFSIZ bytes
		bufp = buf; // bufp is incremented below so we must reset it to the begginning of buf. 
		//bufp is used to hold the position in buf of the next char we will return. 
	}

	// how can we quickly determine that this expression will work at the boundry conditions. e.g. doesn't try to returns more than n chars, or too few chars. 
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF; // as long as there is something in the buf
	// return the char bufp is currently pointing to, then update bufp to point to the next char , 
	// the char we will return on the next call. if read() returned n=0, indicating
	// EOF, then we return EOF since we are pre-decremention the test would be -1 >= 0 which
	// is false so return EOF. similarly on error, n would be negative already
	// and then get decremented, so we return EOF on error too. 
	//// my version

	if(n > 0){ // n=1. return 1 byte. 
		n--; // n = 0;
		return c;

	}
}


//
#include <stdio.h>
#include <fcntl.h>
#include "syscalls.h"
#define PERMS 0666 /* RW for owner, group, others */

void error(char *, ...);

/*cp: copyf1tof2*/ 
main(int argc, char *argv[]) {
int f1, f2, n; // 2 file descriptors for the source file and the destination file. n the transfer count.
char buf[BUFSIZ]; // buffer to hold the transfered bytes intermediate.

if (argc != 3) 
	error("Usage: cp from to"); // we need both a source and destination file. i.e 2 args. Not the error() doesn't return since it calls exit(1);
if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)  // we need to open a file before using it. the source file must already exist, open returns -1 for error or a nonexisting file. 
	error("cp: can't open %s", argv[1]);
if ((f2 = creat(argv[2], PERMS)) == -1) // creat the destination file. with permissions 0666. if -1 is returned then the destination file could not be created. s
	error("cp: can't create %s, mode %03o", argv[2], PERMS);
// we opened the source file and created the destination file, now we can do the copy!
while ((n = read(f1, buf, BUFSIZ)) > 0) // read from the source file BUFSIZ bytes into buf, for as long as we don't hit EOF or an error. 
	if (write(f2, buf, n) != n) // write as much as we read. An error occured if we didn't write as much as we read. 
		error("cp: write error on file %s", argv[2]); // recall the all files are automatically closed when the program terminates normally. (i.e. returns from main of through exit().)
return 0; 

}


