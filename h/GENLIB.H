
#ifndef _GENLIB_H
#define _GENLIB_H

 
#define sizeof (int)sizeof

extern int abs(int);

extern int atoi(char *);
extern long atol(char *);

extern int memcmp(char *, char *, int);


extern char *memccpy(char *, char *, int, int);
extern char *memchr(char *, char, int);
extern char *memcpy(char *, char *, int);
extern char *memset(char *, char, int);

extern int strcmp(char *, char *);
extern int strncmp(char *, char *, int);
extern int strlen(char *);
extern int strspn(char *, char *);
extern char *strcat(char *, char *);
extern char *strchr(char *, char);
extern char *strstr(char *, char *);
extern char *strcpy(char *, char *);
extern char *strncat(char *, char *, int);
extern char *strncpy(char *, char *, int);
extern char *strpbrk(char *, char *);
extern char *strrchr(char *, char);
extern char *strtok(char *, char *);
extern char *strtolower(char *string);
extern char *strtoupper(char *string);
extern long strtol(char *, char **, int);

extern unsigned short swap2(unsigned short);
extern unsigned long swap4(unsigned long);
extern unsigned long strtoul(char *, char **, int);

extern char *malloc(int size);
extern void  free(char *cp);
extern char *calloc(int nelem, int elsize);
extern char *realloc(char *cp,int size);


extern int	my_sprintf(const char *, ...);
extern int	my_snprintf(const char *, ...);
extern int	my_printf(const char *, ...);
extern int	my_cprintf(const char *, ...);
extern int	my_printfk(const char *, ...);

#define printf my_printf
#define sprintf my_sprintf
#define cprintf my_cprintf

#define printfk my_printfk

extern void des_code(	unsigned char k,		//k=0为加密。/k=1为解密
				unsigned char *pdata,	//输入数据
				unsigned char * dkey,	//密钥
				unsigned char *result);	//输出数据


char *dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve);
double strtod(char *s00, char **se);

#endif
