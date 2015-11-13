#include "init.h"

int repo_status()
{
	struct stat st;

	if (stat(".nako", &st) != -1)
		return 1;
	else
		return 0;
}

int init_repo()
{
	if (repo_status() == 0) {
		mkdir(".nako", 0777);
		mkdir(".nako/objects", 0777);
		mkdir(".nako/branches", 0777);
		mkdir(".nako/snaps", 0777);
		mkdir(".nako/tags", 0777);
	} else
		printf("Error. There is already a repo in this directory.\n");
	return 0;
}

int unlink_all(const char *fpath, const struct stat *sb,
	       int typeflag, struct FTW *ftwbuf)
{
	int rv = remove(fpath);

	if (rv != 0)
		perror(fpath);

	return rv;
}

/*
 * Deleting files by "File Tree Walk" using nftw()
 */
int rmrf(char *path)
{
	return nftw(path, unlink_all, 64, FTW_DEPTH | FTW_PHYS);
}

int remove_repo()
{
	rmrf(".nako");
	return 0;
}
