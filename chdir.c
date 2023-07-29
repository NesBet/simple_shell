#include "main.h"

/**
 * cd_par - Changes to parent directory.
 * @datastruct: Relevant data.
 *
 * Return: Nothing.
 */

void cd_par(shell_info *datastruct)
{
	char pwd[PATH_MAX];
	char *par_pwd, *par_oldpwd, *chp_pwd, *chp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	chp_pwd = str_dup(pwd);

	par_oldpwd = set_environ("OLDPWD", datastruct->our_environ);
	if (par_oldpwd == NULL)
		chp_oldpwd = chp_pwd;
	else
		chp_oldpwd = str_dup(par_oldpwd);
	set_environ("OLDPWD", chp_pwd, datastruct);

	if (child_dir(chp_oldpwd) == -1)
		set_environ("PWD", chp_pwd, datastruct);
	else
		set_environ("PWD", chp_oldpwd, datastruct);

	par_pwd = set_environ("PWD", datastruct->our_environ);

	write(STDOUT_FILENO, par_pwd, str_len(par_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(chp_pwd);
	if (par_oldpwd)
		free(chp_oldpwd);
	datastruct->status = 0;
}

/**
 * cd_to - Changes to a directory given.
 * @datastruct: Data relevant.
 *
 * Return: Nothing.
 */
void cd_to(shell_info *datastruct)
{
	char pwd[PATH_MAX];
	char *dir, *chp_pwd, *cp_dir;

	obt_cwd(pwd, sizeof(pwd));

	dir = datastruct->args[1];
	if (child_dir(dir) == -1)
	{
		find_error(datastruct, 2);
		return;
	}

	chp_pwd = str_dup(pwd);
	set_environ("OLDPWD", chp_pwd, datastruct);

	cp_dir = str_dup(dir);
	set_environ("PWD", cp_dir, datastruct);

	free(chp_pwd);
	free(cp_dir);

	datastruct->status = 0;
	chdir(dir);
}

/**
 * cd_previous - Changes to the previous directory.
 * @datastruct: Data relevant.
 *
 * Return: Nothing.
 */
void cd_previous(shell_info *datastruct)
{
	char pwd[PATH_MAX];
	char *par_pwd, *par_oldpwd, *chp_pwd, *chp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	chp_pwd = str_dup(pwd);

	par_oldpwd = set_environ("OLDPWD", datastruct->our_environ);

	if (par_oldpwd == NULL)
		chp_oldpwd = chp_pwd;
	else
		chp_oldpwd = str_dup(par_oldpwd);

	set_environ("OLDPWD", chp_pwd, datastruct);

	if (chdir(chp_oldpwd) == -1)
		set_environ("PWD", chp_pwd, datastruct);
	else
		set_environ("PWD", chp_oldpwd, datastruct);

	par_pwd = set_environ("PWD", datastruct->our_environ);

	write(STDOUT_FILENO, par_pwd, str_len(par_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(chp_pwd);
	if (par_oldpwd)
		free(chp_oldpwd);

	datastruct->status = 0;
	chdir(par_pwd);
}

/**
 * cd_home - Changes to home directory.
 * @datastruct: Relevant data.
 *
 * Return: Nothing.
 */

void cd_home(shell_info *datastruct)
{
	char *par_pwd, *home;
	char pwd[PATH_MAX];

	obt_cwd(pwd, sizeof(pwd));
	par_pwd = str_dup(pwd);

	home = set_environ("HOME", datastruct->our_environ);
	if (home == NULL)
	{
		set_environ("OLDPWD", par_pwd, datastruct);
		free(par_pwd);
		return;
	}

	if (child_dir(home) == -1)
	{
		find_err(datastruct, 2);
		free(par_pwd);
		return;
	}

	set_environ("OLDPWD", par_pwd, datastruct);
	set_environ("PWD", home, datastruct);
	free(par_pwd);
	datastruct->status = 0;
}
