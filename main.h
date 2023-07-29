#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFSIZE 1024
#define TOK_DELIM "\t\r\n\a"
#define TOK_BUFSIZE 128

extern char **environ;

/**
 * struct data - Contains all required data on runtime.
 *
 * @av: Argument vector.
 * @pid: Shell process id.
 * @our_environ: Environment variable.
 * @status: Last call of shell.
 * @count: Counts lines.
 * @args: Command line tokens.
 * @command: User input to shell.
 */

typedef struct data
{
	char **av;
	char *pid;
	char **our_environ;
	int status;
	int count;
	char **args;
	char *command;
} shell_info;

/**
 * struct line_list_s - Single linked list.
 * @line: Command line.
 * @next: Next node.
 * Description: Linked list to store command lines.
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} rd_var;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} list_separator;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shell_info *datastruct);
} builtin_t;

/* String functions */
char *str_cat(char *dest, const char *src);
char *str_copy(char *dest, char *src);
int str_cmp(char *st1, char *st2);
int str_spin(char *s, char *acc);
char *str_chr(char *s, char c);

/* cmd.c */
int curr_dir(char *path, int *n);
char *locate_cmd(char *cmd, char **our_environ);
int check_executable(shell_info *datastruct);
int error_command(char *dir, shell_info *datastruct);
int command_line(shell_info *datastruct);

/* cd_error.c */
char *ctcd_err(shell_info *, char *, char *, char *);
char *error_cd(shell_info *datastruct);
char *not_found(shell_info *datastruct);
char *shell_exit(shell_info *datastruct);

/* lists.c */
list_separator *end_separator(list_separator **head, char *separator);
void free_list_separator(list_separator **head);
line_list *end_line_node(line_list **head, char *line);
void free_line_list(line_list **head);

/* functions */
char *str_cat(char *dest, const char *src);
char *str_copy(char *dest, char *src);
int str_comp(char *st1, char *st2);
char *str_char(char *st, char ch);
int str_spin(char *seg, char *acc);

/* lists2.c */
rd_var *add_node_rdvar(rd_var **head, int lenvar, char *valvar, int lenval);
void free_rdvar_list(rd_var **head);

/* string2.c*/
char *str_dup(const char *st);
int str_len(const char *st);
int chars_comp(char st[], const char *delim);
char *str_tok(char st[], const char *delim);
int is_digit(const char *st);

/* memory.c */
void mem_copy(void *destptr, const void *ptr, unsigned int size);
void *mem_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
char **dpmem_realloc(char **ptr, unsigned int new_size, unsigned int prev_size);

/* help.c */
int get_help(shell_info *datastruct);

/* helper2.c */
void help_helper(void);
void alias_helper(void);
void cd_helper(void);

/* helper.c*/
void env_helper(void);
void setenv_helper(void);
void unsetenv_helper(void);
void general_helper(void);
void exit_helper(void);

/* signature.c */
void get_signature(int signal);

/* errors.c */
int get_error(shell_info *datastruct, int errval);

/* file.c */
char *environ_err(shell_info *datastruct);
char *error_path(shell_info *datastruct);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_get_alias(char **args);

/* cd_error.c */
char *ctcd_err(shell_info *datastruct, char *mssg, char *error, char *cnt_str);
char *error_cd(shell_info *datastruct);
char *not_found(shell_info *datastruct);
char *shell_exit(shell_info * datastruct);

/* standard.c*/
int len_no(int n);
char *conv_str(int n);
int conv_int(char *s);

/* exit.c */
int exit_shell(shell_info *datastruct);

/* builtin.c */
int (*get_builtin(char *cmd))(shell_info *);

/* change.c */
int cd_action(shell_info *datastruct);

/* chdir.c*/


/* environ2.c */
char *cote_enas(char *name, char *value);
void set_environ(char *name, char *value, shell_info *datastruct);
int set_env(shell_info *datastruct);
int del_set_environ(shell_info *datastruct);

/* environ.c */
int environ_comp(const char *envname, const char *name);
char *get_env(const char *name, char **our_environ);

/* cmd.c */
int curr_dir(char *path, int *n);
char *locate_cmd(char *cmd, char **our_environ);
int check_executable(shell_info *datastruct);
int error_command(char *dir, shell_info *datastruct);
int command_line(shell_info *datastruct);

/* line_executor.c */
int line_executor(shell_info *datastruct);

/* line.c */
void obtain_line(char **buffline, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **buffline, size_t *n, FILE *stream);

/*var.c */
void check_env(rd_var **h, char *in, shell_info *data);
int check_vars(rd_var **h, char *in, char *st, shell_info *data);
char *repl_vars(rd_var **head, char *input, char *new_input, int new_len);
char *rep_var(char *input, shell_info *datastruct);

/* splitter.c */
char *swap_char(char *input, int bool);
void add_nodes(list_separator **head_sep, line_list **head_list, char *input);
void go_next(list_separator **list_sep, line_list **list_li, shell_info *datastruct);
int split_commands(shell_info *datastruct, char *input);
char **split_line(char *input);

/* rdline.c */
char *read_line(int *rtn);

/* loop.c */
char *delete_comment(char *in);
void shell_loop(shell_info *datastruct);

/* syntax.c  */
int index_first_char(char *input, int *i);
int rpt_char(char *input, int i);
int syntax_err(char *input, int i, char lst);
void print_syntax_err(shell_info *datastruct, char *input, int i, int bool);
int check_syntax_err(shell_info *datastruct, char *input);

/* string3.c  */
void rev_str(char *st);

#endif
