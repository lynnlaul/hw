#ifndef _FILEAPI_H
#define _FILEAPI_H

#define	 size_t	  int

typedef struct 
{
    int     fileid;		 
    U32    offset;		 
    U32    filesize;
    U16	   dir_set;		 
    U16	   dir_lg;
    U16    flag;		 
    
}FS_FILE;
 
#define	FS_SEEK_SET	0	/* set file offset to offset */
#define	FS_SEEK_CUR	1	/* set file offset to current plus offset */
#define	FS_SEEK_END	2	/* set file offset to EOF plus offset */

int FS_Init(void);

int FS_creatfile(char *filename,char attr);
int FS_deletefile(char *filename);
int FS_find(char *filename);

int FS_findfirst(char *s);
int FS_findnext(char *s);
int FS_findfile(char *filename,char *s);
int FS_filelist(char *filname,char *filelist);
long FS_diskspace(void);

int FS_geterror(void);
FS_FILE *FS_fopen(char * /*filename*/, char * /*mode*/);	
int FS_fclose(FS_FILE * /*stream*/);
size_t FS_fread(void * /*ptr*/,size_t /*size*/, size_t /*nmemb*/, FS_FILE * /*stream*/); 
size_t FS_fwrite(void * /*ptr*/,size_t /*size*/, size_t /*nmemb*/, FS_FILE * /*stream*/); 
int FS_fseek(FS_FILE * /*stream*/, long int /*offset*/, int /*whence*/);
int FS_feof(FS_FILE * /*stream*/);
void FS_rewind(FS_FILE * /*stream*/);
long FS_length(FS_FILE *stream);

int FS_loadapptoram(char *filename);
#endif
