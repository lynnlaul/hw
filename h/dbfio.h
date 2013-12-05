#ifndef _DBFIO_H
#define _DBFIO_H

int libuse(char *fname,char dbno);
int libopen(char n);
int libclose(char n);
int libsumr(void);
char libsumf(void);
int libgetr(void);
char libgetf(void);
int libset(unsigned int n, unsigned  char m);
int libread( char *s);
int libwrite( char *s);
int libdel(void);
int libapp(void);
int libwriterec(unsigned char *s );
int libreadrec(unsigned char *s );

#endif
