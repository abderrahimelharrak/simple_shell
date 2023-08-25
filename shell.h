#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NOR		0
#define COMD_OR		1
#define COMD_AND		2
#define COMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWECASE	1
#define CONVERT_UNSIGNE		2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILEE	".simple_shell_history"
#define HIST_MAXX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *string;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function
 * @argum: a string containing arguements
 * @argumv:an array of strings generated from arg
 * @pathe: a string path for the current command
 * @argumc: the argument count
 * @line_c: the error count
 * @error_num: the error code for exit()fcts
 * @linec_flag: if on count this line of input
 * @filename: the program filename
 * @envv: linked list local of environ
 * @environn: custom modified copy of environ from LL env
 * @historique: the history node
 * @aliass: the alias node
 * @env_change: on if environ was changed
 * @stat: the return status of the last exec'd comd
 * @cmd_buff: address of pointer to cmd_buf, on if chaining
 * @cmd_buff_type: CMD_type ||, &&, ;
 * @readfiled: the fd from which to read line input
 * @historycount: the history line number count
 */
typedef struct passinfo
{
	char *argum;
	char **argumv;
	char *pathe;
	int argumc;
	unsigned int line_c;
	int error_num;
	int linec_flag;
	char *filename;
	list_t *envv;
	list_t *historique;
	list_t *aliass;
	char **environn;
	int env_change;
	int stat;
	char **cmd_buff;
	int cmd_buff_type;
	int readfiled;
	int historycount;
} info_t;

#define INF_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int hsh(info_t *, char **);
int _findbuiltin(info_t *);
void _findcmd(info_t *);
void _forkcmd(info_t *);


int _iscmd(info_t *, char *);
char *_dupchars(char *, int, int);
char *_findpath(info_t *, char *, char *);


int loophsh(char **);


void eputs_(char *);
int eputchar_(char);
int putfd_(char, int);
int putsfd_(char *, int);


int strlen_(char *);
int strcmp_(char *, char *);
char *_startswith(const char *, const char *);
char *strcat_(char *, char *);


char *strcpy_(char *, char *);
char *strdup_(const char *);
void puts_(char *);
int putchar_(char);


char *strncpy_(char *, char *, int);
char *strncat_(char *, char *, int);
char *strchr_(char *, char);


char **strtow_(char *, char *);
char **strtow2_(char *, char);


char *memset_(char *, char, unsigned int);
void ffree_(char **);
void *realloc_(void *, unsigned int, unsigned int);


int bfree_(void **);


int inter_active(info_t *);
int _isdelim(char, char *);
int is_alpha(int);
int atoi_(char *);


int erratoi_(char *);
void print_err(info_t *, char *);
int _printd(int, int);
char *_convertnumber(long int, int, int);
void _removecomments(char *);


int myexit_(info_t *);
int mycd_(info_t *);
int myhelp_(info_t *);


int myhistory_(info_t *);
int myalias_(info_t *);


ssize_t _getinput(info_t *);
int getline_(info_t *, char **, size_t *);
void sigintHandler_(int);


void _clearinfo(info_t *);
void _setinfo(info_t *, char **);
void _freeinfo(info_t *, int);


char *getenv_(info_t *, const char *);
int myenv_(info_t *);
int mysetenv_(info_t *);
int myunsetenv_(info_t *);
int _populateenv_list(info_t *);


char **_getenviron(info_t *);
int unsetenv_(info_t *, char *);
int setenv_(info_t *, char *, char *);


char *_gethistory_file(info_t *info);
int _writehistory(info_t *info);
int _readhistory(info_t *info);
int _buildhistory_list(info_t *info, char *buf, int linecount);
int _renumberhistory(info_t *info);


list_t *_addnode(list_t **, const char *, int);
list_t *_addnode_end(list_t **, const char *, int);
size_t _printlist_str(const list_t *);
int _deletenode_at_index(list_t **, unsigned int);
void _freelist(list_t **);


size_t _listlen(const list_t *);
char **_listto_strings(list_t *);
size_t _printlist(const list_t *);
list_t *_nodestarts_with(list_t *, char *, char);
ssize_t _getnode_index(list_t *, list_t *);


int _ischain(info_t *, char *, size_t *);
void _checkchain(info_t *, char *, size_t *, size_t, size_t);
int _replacealias(info_t *);
int _replacevars(info_t *);
int _replacestring(char **, char *);

#endif

