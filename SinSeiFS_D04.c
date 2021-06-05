#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>

static const char *dirpath = "/home/thomasfelix/Downloads";
static const char *logpath = "/home/thomasfelix/SinSeiFS.log";

void getDirAndFile(char *dir, char *file, char *path) {
	char buff[1000];
  	
	memset(dir, 0, 1000);
  	memset(file, 0, 1000);
  	strcpy(buff, path);
  	
	char *token = strtok(buff, "/");
	
  	while(token != NULL) {
    	sprintf(file, "%s", token);
    	token = strtok(NULL, "/");
	
		if (token != NULL) {
    		sprintf(dir, "%s/%s", dir, file);
    	}
  	}
}

void atbashCode(char *string) {
	int i = 0;

	while (string[i] != '\0') {
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = 'Z' + 'A' - string[i];
		}

		else if (string[i] >= 'a' && string[i] <= 'z') {
			string[i] = 'z' + 'a' - string[i];
		}

		i++;
	}
}

void changePath(char *fpath, const char *path, int isWriteOperation, int isFileAsked) {
  	char *ptr = strstr(path, "/AtoZ_");
  	int state = 0;
  	
	if (ptr != NULL) {
    	if (strstr(ptr + 1, "/") != NULL) {
			state = 1;
		}
  	}
  	
	char fixPath[1000];
  	
	memset(fixPath, 0, sizeof(fixPath));
  	
	if (ptr != NULL && state) {
    	ptr = strstr(ptr + 1, "/");
    	char pathEncvDirBuff[1000];
    	char pathEncryptedBuff[1000];
    	
		strcpy(pathEncryptedBuff, ptr);
    	strncpy(pathEncvDirBuff, path, ptr - path);
    
		if (isWriteOperation) {
      		char pathFileBuff[1000];
      		char pathDirBuff[1000];
      		
			getDirAndFile(pathDirBuff, pathFileBuff, pathEncryptedBuff);
      		atbashCode(pathDirBuff);
			//decrypt(pathDirBuff, 0);
      		sprintf(fixPath, "%s%s/%s", pathEncvDirBuff, pathDirBuff, pathFileBuff);
    	}
		
		else if (isFileAsked) {
      		char pathFileBuff[1000];
      		char pathDirBuff[1000];
      		char pathExtBuff[1000];
      		
			getDirAndFile(pathDirBuff, pathFileBuff, pathEncryptedBuff);
      		
			char *whereIsExtension = strrchr(pathFileBuff, '.');
      	
		  	if (whereIsExtension-pathFileBuff < 1) {
				atbashCode(pathDirBuff);
				atbashCode(pathFileBuff);
        		//decrypt(pathDirBuff, 0);
        		//decrypt(pathFileBuff, 0);
        		sprintf(fixPath, "%s%s/%s", pathEncvDirBuff, pathDirBuff, pathFileBuff);
      		}
			  
			else {
        		char pathJustFileBuff[1000];
        	
				memset(pathJustFileBuff, 0, sizeof(pathJustFileBuff));
        		strcpy(pathExtBuff, whereIsExtension);
        		snprintf(pathJustFileBuff, whereIsExtension-pathFileBuff+1, "%s", pathFileBuff);
        		atbashCode(pathDirBuff);
				atbashCode(pathJustFileBuff);
				//decrypt(pathDirBuff, 0);
        		//decrypt(pathJustFileBuff, 0);
        		sprintf(fixPath, "%s%s/%s%s", pathEncvDirBuff, pathDirBuff, pathJustFileBuff, pathExtBuff);
      		}
    	}
		
		else {
			atbashCode(pathEncryptedBuff);
      		//decrypt(pathEncryptedBuff, 0);
      		sprintf(fixPath, "%s%s", pathEncvDirBuff, pathEncryptedBuff);
   		}
  	}
	
	else {
    	strcpy(fixPath, path);
  	}
  	
	if (strcmp(path, "/") == 0) {
    	sprintf(fpath, "%s", dirpath);
  	}
	
	else {
    	sprintf(fpath, "%s%s", dirpath, fixPath);
  	}
}

void fileLog(char *level, char *cmd, int lenDesc, const char *desc[]) {
	FILE *file = fopen(logpath, "a");
  	time_t t;
  	struct tm *temp;
  	char timeBuffer[100];

  	time(&t);
  	temp = localtime(&t);

  	strftime(timeBuffer, sizeof(timeBuffer), "%y%m%d-%H:%M:%S", temp);
	
  	fprintf(file, "%s::%s::%s", level, timeBuffer, cmd);
  	
	for (int i = 0; i < lenDesc; i++) {
   		if ((strcmp(cmd, "RENAME") == 0) || (strcmp(cmd, "MKDIR") == 0)) {
			fprintf(file, "::/home/thomasfelix/Downloads%s", desc[i]);
		}

		else {
			fprintf(file, "::%s", desc[i]);
		}
  	}
  	
	fprintf(file, "\n");

  	fclose(file);
}


static int xmp_getattr(const char *path, struct stat *stbuf) {
	char fpath[1000];
  	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	res = lstat(fpath, stbuf);

  	const char *desc[] = {path};
  	fileLog("INFO", "GETATTR", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_access(const char *path, int mask) {
	char fpath[1000];
	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, 1000);
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	res = access(fpath, mask);

  	const char *desc[] = {path};
  	fileLog("INFO", "ACCESS", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size) {
	char fpath[1000];
	
	changePath(fpath, path, 0, 1);

	int res;

	res = readlink(fpath, buf, size - 1);

  	const char *desc[] = {path};
  	fileLog("INFO", "READLINK", 1, desc);

	if (res == -1) {
		return -errno;
	}

	buf[res] = '\0';
	
	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
	char fpath[1000];
	
	changePath(fpath, path, 0, 0);

	DIR *dp;
	struct dirent *de;
	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	
	if (dp == NULL) {
		const char *desc[] = {path};
    	fileLog("INFO", "READDIR", 1, desc);
    
		return -errno;
  	}

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		
		memset(&st, 0, sizeof(st));
		
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
    	
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
			continue;
		}
    	
		if (strstr(path, "/AtoZ_") != NULL) {
      		char encodeThis[1000];
      		
			strcpy(encodeThis, de->d_name);
      		
			if (de->d_type == DT_REG) {
        		char *whereIsExtension = strrchr(encodeThis, '.');
        		
				if (whereIsExtension - encodeThis < 1) {
					atbashCode(encodeThis);
          			//decrypt(encodeThis, 1);
        		}
				
				else {
          			char pathFileBuff[1000];
          			char pathExtBuff[1000];
          			
					strcpy(pathExtBuff, whereIsExtension);
          			snprintf(pathFileBuff, whereIsExtension - encodeThis + 1, "%s", encodeThis);
          			atbashCode(pathFileBuff);
					//decrypt(pathFileBuff, 1);
          			memset(encodeThis, 0, sizeof(encodeThis));
          			sprintf(encodeThis, "%s%s", pathFileBuff, pathExtBuff);
        		}
      		}
			
			else if (de->d_type == DT_DIR) {
				atbashCode(encodeThis);
        		//decrypt(encodeThis, 1);
      		}

  			if (filler(buf, encodeThis, &st, 0)) {
				break;
			}
    	}
		
		else {
      		if (filler(buf, de->d_name, &st, 0)) {
				break;
			}
    	}
	}

  	const char *desc[] = {path};
  	fileLog("INFO", "READDIR", 1, desc);

	closedir(dp);
	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode) {
	char fpath[1000];

	changePath(fpath, path, 1, 0);

  	char *ptr = strrchr(path, '/');
  	char *filePtr = strstr(ptr, "/AtoZ_");
  	
	if (filePtr != NULL) {
    	if (filePtr - ptr == 0) {
      		const char *desc[] = {path};
      		fileLog("SPECIAL", "ENCV1", 1, desc);
    	}
  	}

	int res;

	res = mkdir(fpath, mode);

  	const char *desc[] = {path};
  	fileLog("INFO", "MKDIR", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_unlink(const char *path) {
	char fpath[1000];

	changePath(fpath, path, 0, 1);

	int res;

	res = unlink(fpath);

  	const char *desc[] = {path};
  	fileLog("WARNING", "UNLINK", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_rmdir(const char *path) {
	char fpath[1000];
	
	changePath(fpath, path, 0, 0);
	
	int res;

	res = rmdir(fpath);

  	const char *desc[] = {path};
  	fileLog("WARNING", "RMDIR", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_symlink(const char *from, const char *to) {
	char ffrom[1000];
	char fto[1000];

	changePath(ffrom, from, 0, 1);
	changePath(fto, to, 0, 1);

	int res;

	res = symlink(ffrom, fto);

  	const char *desc[] = {from, to};
  	fileLog("INFO", "SYMLINK", 2, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_rename(const char *from, const char *to) {
	char ffrom[1000];
	char fto[1000];

	changePath(ffrom, from, 0, 1);
	changePath(fto, to, 0, 1);
  	
	if (access(ffrom, F_OK) == -1) {
    	memset(ffrom, 0, sizeof(ffrom));
    	changePath(ffrom, from, 0, 0);
  	}
  	
	if (access(fto, F_OK) == -1) {
    	memset(fto, 0, sizeof(fto));
    	changePath(fto, to, 0, 0);
  	}

  	char *toPtr = strrchr(to, '/');
	char *toStartPtr = strstr(toPtr, "/AtoZ_");
  	
	if (toStartPtr != NULL) {
    	if (toStartPtr - toPtr == 0) {
      		const char *desc[] = {fto};
      		fileLog("SPECIAL", "ATOZ", 1, desc);
    	}
  	}

	int res;

	res = rename(ffrom, fto);

  	const char *desc[] = {from, to};
  	fileLog("INFO", "RENAME", 2, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_link(const char *from, const char *to) {
	char ffrom[1000];
	char fto[1000];
	
	changePath(ffrom, from, 0, 1);
	changePath(fto, to, 0, 1);

	int res;

	res = link(ffrom, fto);

  	const char *desc[] = {from, to};
 	fileLog("INFO", "LINK", 2, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode) {
	char fpath[1000];
	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	res = chmod(fpath, mode);

  	char modeBuff[100];
  	
	sprintf(modeBuff, "%d", mode);
  	
	const char *desc[] = {path, modeBuff};
  	fileLog("INFO", "CHMOD", 2, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid) {
	char fpath[1000];
  	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	res = lchown(fpath, uid, gid);

  	char uidBuff[100];
  	char gidBuff[100];
  	
	sprintf(uidBuff, "%d", uid);
  	sprintf(gidBuff, "%d", gid);
	
	const char *desc[] = {path, uidBuff, gidBuff};
  	fileLog("INFO", "CHOWN", 3, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_truncate(const char *path, off_t size) {
	char fpath[1000];
  	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	res = truncate(fpath, size);

  	const char *desc[] = {path};
  	fileLog("INFO", "TRUNCATE", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2]) {
	char fpath[1000];
  	
	changePath(fpath, path, 0, 1);
  	
	if (access(fpath, F_OK) == -1) {
    	memset(fpath, 0, sizeof(fpath));
    	changePath(fpath, path, 0, 0);
  	}

	int res;

	/* don't use utime/utimes since they follow symlinks */
	res = utimensat(0, fpath, ts, AT_SYMLINK_NOFOLLOW);

  	const char *desc[] = {path};
  	fileLog("INFO", "UTIMENSAT", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
	char fpath[1000];
  	
	changePath(fpath, path, 1, 0);

	int res;

	res = open(fpath, fi->flags, mode);

  	const char *desc[] = {path};
  	fileLog("INFO", "CREAT", 1, desc);

	if (res == -1) {
		return -errno;
	}

	fi->fh = res;

	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi) {
	char fpath[1000];
  	
	changePath(fpath, path, 0, 1);

	int res;

	res = open(fpath, fi->flags);

  	const char *desc[] = {path};
  	fileLog("INFO", "OPEN", 1, desc);

	if (res == -1) {
		return -errno;
	}

	fi->fh = res;
	
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	char fpath[1000];

	changePath(fpath, path, 0, 1);

	int fd;
	int res;

	if (fi == NULL) {
		fd = open(fpath, O_RDONLY);
	}
	
	else {
		fd = fi->fh;
	}

	if (fd == -1) {
		return -errno;
	}

	res = pread(fd, buf, size, offset);

  	const char *desc[] = {path};
  	fileLog("INFO", "READ", 1, desc);

	if (res == -1) {
		res = -errno;
	}

	if (fi == NULL) {
		close(fd);
	}

	return res;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	char fpath[1000];

	changePath(fpath, path, 1, 0);

	int fd;
	int res;
	(void) fi;

	if (fi == NULL) {
		fd = open(fpath, O_WRONLY);
	}
	
	else {
		fd = fi->fh;
	}

	if (fd == -1) {
		return -errno;
	}

	res = pwrite(fd, buf, size, offset);


  	const char *desc[] = {path};
  	fileLog("INFO", "WRITE", 1, desc);

	if (res == -1) res = -errno;

	if(fi == NULL) close(fd);
	return res;
}

static int xmp_statfs(const char *path, struct statvfs *stbuf) {
	char fpath[1000];

	changePath(fpath, path, 0, 1);
	int res;

	res = statvfs(fpath, stbuf);

  	const char *desc[] = {path};
  	fileLog("INFO", "STATFS", 1, desc);

	if (res == -1) {
		return -errno;
	}

	return 0;
}

static int xmp_release(const char *path, struct fuse_file_info *fi) {
	(void) path;
	
	close(fi->fh);
  	
	const char *desc[] = {path};
  	fileLog("INFO", "RELEASE", 1, desc);
	
	return 0;
}


static const struct fuse_operations _oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.create 	= xmp_create,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.release	= xmp_release,
};

int main(int argc, char *argv[]) {
	umask(0);
	return fuse_main(argc, argv, &_oper, NULL);
}
