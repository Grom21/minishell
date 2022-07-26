#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define OTHER_ERROR 0
#define SYNTAX_ERROR 1
#define COMMAND_NOT_FOUND 2
#define SYNTAX_PIPE_ERROR 3
#define HOME_NOT_SET 4
#define NO_SUCH_FILE_OR_DIR 5
#define OLDPWD_NOT_SET 6
#define FILE_NAME_TOO_LONG 7
#define SYNTAX_REDIR_ERROR 8
#define PERMISSION_DENIED 9
#define IS_A_DIRECTORY 10
#define FILE_IS_BUSY 11
#define ONLY_READ 12

int	g_last_exit;

typedef struct s_list
{
	char 			*key;
	char 			*value;
	struct s_list	*next;
} t_list;
/* структура (на односвязанных листах) для хранения и работы с переменными окружения
ключ - переменная
значение - ее состояние */

typedef struct s_lexer
{
	char			*chank;
	struct s_lexer	*next;
} t_lexer;
/* структура (на односвязанных листах) в которую записывается результат работы лексера
после разбивки принятой строки на отдельные части (разбивка по " ", ";", "|",
а также символы "\'" и "\"" разбиваются одним блоком, а "\\" сохраняет следующий символ),
при этом символы разделителя так же сохраняются в отдельных листах */

typedef struct s_shell
{
	t_list			*envp_list;
	char			**envp;
	char			*input;
	char			**comand;
	t_lexer			*lexer;
	struct termios	new_settings;
	struct termios	default_settings;
	int				fd1[2];
	int				fd2[2];
	pid_t			children;
}t_shell;
/* главная структура - хранит в себе все необходимые данные */


/* INIT BLOCK */

/* функция сохраняет в главную структуру t_shell mini базовые настройки
терминала (default_settings) и создает новые настройки (new_settings)
в которых блокируется вывод на экран символов, возникающих
при нажатии ctrl+c и подобных сочетаний */
void	ft_new_term_settings(t_shell *mini);

/* функция возвращает терминал к изначальным настройкам */
void	ft_default_term(t_shell *mini);

/* главная функция блока init: вызывает остальные функци и записывает
начальные значения в структуру t_shell mini */
void	ft_init(t_shell	*mini, char **env);

/*функция запускается при старте прграммы и сохраняет переменные окружения в листы
для последующей работы с ними.
в случае ошибики чистит за собой память и выходит с кодом 1 */
void	ft_init_envp_list(t_list **envp_list, char **env);

/*функция сохраняет в лист одну переменную окружения разбив ее на пару
ключ - значение (разделитель = ) */
void	ft_save_envp_on_list(t_list **list, char *env);

/*функция очистки памяти переменных окружения в листах (без exit!)*/
void	ft_free_memory_envp_list(t_list **envp_list);

/*функция сохраняет переменные окружения в двухмерный массив
в случае ошибки чистит за собой память и возвращает NULL
использует маллок! - для очистки используй ft_free_memory_matrix(char **matrix)
где x - размер "массива первого порядка"*/
char	**ft_new_envp(t_list **envp_list);

/*функция для очиски памяти от двухмерного массива*/
void	ft_free_memory_matrix(char **matrix);


/* PARSER */


/*функция разбивает полученную строку на отдельные блоки
и сохраняет их в односвязанном списке для дальнейшего парсинга
в случае если строка пустая или содержит только пробелы возврашает
пустую строку в lexer->chank */
void	ft_lexer(t_lexer **lexer, char	*input);

/*функция для очиски памяти от односвязанного списка
создаваемого ft_lexer(t_lexer **lexer, char	*input);
после очиски памяти значение *lexer = NULL */
void	ft_free_memory_lexer_list(t_lexer **lexer);

/*функция создает отдельный лист односвязаннго списка lexer
была вынесена поскольку вызывающие ее функции не поместились в один файл
(вызывается из файла lexer_utils.c) */
void	ft_create_lexer(t_lexer **lexer, char *input, int start, int stop);

/*функция сохраняет в листы все что не \ < > << >> " ' ; | или до этих
символов */
void	ft_lexer_word(t_lexer **lexer, char *input, int *start, int *stop);

/*функция в случае встречи пробелов пропускает их все и сохраняет один пробел
в лист */
void	ft_lexer_spase(t_lexer **lexer, char *input, int *start, int *stop);

/*если "\\" идет в конце строки то сохранен будет только "\\"!
проверить в парсере!!!!! */
void	ft_lexer_delim(t_lexer **lexer, char *input, int *start, int *stop);

/*функция сохраняет в лист все что между ' , а если нет закрывающей, то
до конца строки
одинарные ковычки экранируют все: "$" и "\" */
void	ft_lexer_s_quotes(t_lexer **lexer, char *input, int *start, int *stop);

/*функция сохраняет в лист все что между " , а если нет закрывающей, то
до конца строки
в данной функции отдельно обработан случай "\"\0 - будет сохранено в лист "\ ,
что легко отловить через проверку открыл кавычки - закрыл кавычки
следует учитывать что двойные кавычки не экранируют $ */
void	ft_lexer_d_quotes(t_lexer **lexer, char *input, int *start, int *stop);

/*функция пропускает все пробелы в начале строки
в случае если строка пустая или состоит только из пробелов
создает лист с пустой строой*/
void	ft_lexer_run_space(t_lexer **lexer, char *input, int *start, int *stop);

/*функция сохраняет в листы алмазные кавычки
в случае если ковычек больше 2 сохраняет попарно в новый лист*/
void	ft_lexer_redirect(t_lexer **lexer, char *input, int *start, int *stop);

/*главная функция парсера - запускается после лексера и вызывает остальные
функции проверки */
int	ft_parser(t_shell *mini);

/*функция проверяет есть ли хоть чтото перед | и нет ли | в конце строки,
а так же не стоят ли друг за другом ; и | и нет ли двойного написания ; и |
если да, то выводит сообщение об ошибке */
int	ft_exam_pipe_first_last_double(t_shell *mini);

/*функция проверяет были ли закрыты кавычки, если нет то выводит сооббщение
об ошибке */
int	ft_exam_syntax_quotes(t_shell *mini);

/*функция проверяет нет ли идущих друг за другом редиректа, включая разделенных
пробелом. если да, то выводит сообщение об ошибке */
int	ft_exam_double_redirect(t_shell *mini);

/*функция проверяет есть ли что-то после редиректа, если нет, выводит сообщение
об ошибке */
int	ft_exam_last_redirect(t_shell *mini);

/*функция вывода сообщений об ошибках во 2 поток */
void	ft_print_parser_error(t_lexer **lexer, int exeption);

/*создает новый лист в lexer в котором будут пересохранены аргументы
к команде*/
void	ft_parser_create(t_lexer **new);

/*сохраняет один символ (с помошью strjoin) в переданный
lexer->chank*/
int	ft_save_char(t_lexer *new, char c);

/*функция которая подставляет вместо ключа переменной окружения
его значение*/
int	ft_take_envp(t_lexer *new, t_lexer *old, int i, t_list *envp);

/*функция проверяет что сохранено в чанке (" или ')
 и запускает соответствующую функцию для оработки*/
int	ft_parser_save(t_lexer *new_copy, t_lexer *old_copy, t_list *envp_list);

/* EXECUTION */

/*основная функция исполнения команд*/
void	ft_execution(t_shell *mini);

/* закрывает файловые дискрипторы пайпов*/
void	ft_close_fd(t_shell *mini, int i);

/* вывод сообщение об ошибке форка*/
void	ft_error_fork(t_shell *mini, int i);

/* функция ищет редиректы между пайпами
если находит возвращает 1 иначе 0*/
int	ft_found_redirect_in_command(t_lexer *lexer);

/* отдельная функция обработки команд тип exit << eof*/
void	ft_exit_with_redirect(t_shell *mini, t_lexer *copy, int count, int i);

/* функция ищет << между пайпами если находит возвращает -3 иначе g_last_exit*/
int	found_heredoc(t_lexer *lexer);

/* функция считает сколько всего пайпов, если 0 то возвращает -1*/
int	ft_found_command_with_pipe(t_lexer *lexer);

/*кастомное эхо, работает с флагом -n*/
int	ft_echo(t_lexer *lexer);

/*меняет директорию, cd - возврат к старой директории
cd ~ эквивалентно cd */
int	ft_cd(t_lexer *lexer, t_shell *mini);

/*выводит сообщение об ошибках при работе cd*/
int	ft_cd_error(int exeption, char *str);

/*функция поиска в envp_list нужного листа по key
возвращает указатель на найденный лист или NULL если не найдено*/
t_list *ft_found_in_envp(t_list *envp_list, char *key);

/* функция обновляет значение OLDPWD в mini->envp_list */
int	ft_update_envp_old_pwd(t_list *envp_list, char *old_pwd);

int	ft_free_envp_old_pwd(char *old_pwd);

/* функция обновляет значение PWD в mini->envp_list */
int	ft_update_envp_pwd(t_list *envp_list);

/*выводит путь независимо от переданных аргументов*/
int	ft_pwd(void);

/*выводит переменные окружения*/
int	ft_env(t_list *envp_list);

/*добавляет новые переменные окружения в env
возможно добавление нескольких переменных разделенный пробелом*/
int	ft_export(t_lexer *lexer, t_list *envp_list);

/*функция проверяет есть ли строка в виде ключ=значение в
envp_list и если есть меняет значение, иначе добавляет новое*/
int	ft_export_run(char *str, t_list *envp_list, int len);

/*проверяет переданы ли аргументы в функцию экспорт
если аргументов нет, выводит полный список env*/
int	ft_exam_void(t_lexer *lexer, t_list *envp_list);

/*функция проверяет допустимо ли значение ключа
новой переменной окружения. которую хотят добавить*/
int	ft_exam_export_key(char *str, char *key);

/*выводит сообщение об ошибках при работе экспорта*/
int	ft_print_export_error(char *str);

/*функция удаляет переменные окружения из списка env
может быть передано несколько переменных через пробел*/
int	ft_unset(t_lexer *lexer, t_list **envp_list);

/*печать сообщений об ошибках функции unset*/
int	ft_print_unset_error(char *str);

/*функция выхода если передана команда exit
в качестве аргумента принимает число - с каким кодом происход выход*/
int	ft_exit(t_shell *mini, t_lexer *lexer);

/*функция запуска сторонних бинарников в отдельном процессе
так же в ней реализованы пайпы*/
void	ft_children_run(t_shell *mini, t_lexer *lexer, int i, int count);

/*функция поиска кастомных команд, реализованных в минишелле*/
int	ft_found_in_castom(t_shell *mini, t_lexer *lexer);

/* функция работы с файловыми дискрипоторами в дочернем процессе*/
void	ft_work_with_fd(t_shell *mini, int i, int count);

/* функция работы с файловыми дискрипоторами в дочернем процессе (последний пайп)*/
void	ft_work_with_fd_last_command(t_shell *mini, int i, int count);

/* функция работы с файловыми дискрипоторами в случае редиректа в команде*/
void	ft_redirect(t_shell *mini, t_lexer *lexer, int i, int count);

/*вывод ошибок при работе с редиректом*/
int	ft_redirect_error(t_lexer **lexer, int exeption);

/* функция поиска и запуска команды если есть редирект*/
void	ft_run_redirect(t_shell *mini, t_lexer *lexer, int *fd);

/* функция обработки heredoc*/
int	ft_redirect_out_file2(t_lexer *lexer, t_lexer *now);

/* функция возвращает файловый дискриптор файла куда запишется heredoc
или откуда надо читать heredoc*/
int ft_open_heredoc(t_lexer *lexer, int flag);

/*функция поиска и запуска бинарников в PATH*/
void	ft_run_from_path(t_shell *mini, t_lexer *copy);

/* функция создания массива argv для запуска бинарника*/
char	**ft_create_argv(t_shell *mini, t_lexer *copy);

/* функция вывода сообщений об ошибках exec*/
void	ft_error_exec(t_shell *mini, int exeption, char *str, char **argv);

/* OTHER */

/*функция обработки нажатия ctrl+c: происходи очищение памяти буффера
readline, перевод каретки на новую строку и вывод на экран нового
promt сообщения */
void	ft_signal(int sig);

/*функция обработки нажатие ctrl+d: в этом случае readline возвращает
NULL и происходит очиска всей занятой памяти, выводиться сообщение о
выходе, настройки терминала возвращаются в исходное состояние и
программа завершается с кодом 0 */
void	ft_exit_signal(t_shell *mini);


/* libft */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	ft_free_memory_split(char **matrix, int x);
size_t	ft_strlen_value(const char *s);
size_t	ft_strlen_key(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_echo(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
long long int	ft_atoi_long(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isalpha(int c);
int		ft_isdigit(int c);

#endif
