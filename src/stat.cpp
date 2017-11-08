/*#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	struct stat sb;

	if (argc != 2) {
		printf("ERROR: %s <pathname>\n", *argv);
		return -1;
	}

	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return -1;
	}

	switch(sb.st_mode & S_IFMT) {

	case S_IFBLK: printf("File type: black device\n"); break;
	case S_IFCHR: printf("File type: character device\n"); break;
	case S_IFDIR: printf("File type: directory\n"); break;
	case S_IFIFO: printf("File type: FIFO/pipe\n"); break;
	case S_IFLNK: printf("File type: symlink\n"); break;
	case S_IFREG: printf("File type: regular file\n"); break;
	case S_IFSOCK: printf("File type: socket\n"); break;
	default: printf("File type: unknown\n"); break;
	}

	printf("I-node number: %ld\n", (long) sb.st_ino);
	printf("Mode: %lo (octal)\n", (unsigned long) sb.st_mode);
	printf("Link count: %ld\n", (long) sb.st_nlink);
	printf("Ownership: UID=%ld, GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	printf("Preferred I/O black size: %ld bytes\n", (long) sb.st_blksize);
	printf("File size: %lld bytes\n", (long long) sb.st_size);
	printf("Blocks allocated: %lld\n", (long long) sb.st_blocks);
	printf("Last status change: %s", ctime(&sb.st_ctime));
	printf("Last file access: %s", ctime(&sb.st_atime));
	printf("Last file modification: %s", ctime(&sb.st_mtime));


}*/
