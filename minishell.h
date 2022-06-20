#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h> //printf only?
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#define SYNTAX_ERROR 1
#define COMMAND_NOT_FOUND 2
#define SYNTAX_PIPE_ERROR 3


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
	t_list	*envp_list;
	char	**envp;
	char	*input;
	char	**comand;
	t_lexer	*lexer;
}t_shell;
/* главная структура - хранит в себе все необходимые данные */


/* INIT BLOCK */


void	ft_init(t_shell	*mini, char **env);
/* главная функция блока init: вызывает остальные функци и записывает 
начальные значения в структуру t_shell mini */

void	ft_init_envp_list(t_list **envp_list, char **env);
/*функция запускается при старте прграммы и сохраняет переменные окружения в листы
для последующей работы с ними
использует маллок! - для очистки используй ft_free_memory_envp_list(t_list **envp_list);
в случае ошибики чистит за собой память и выходит с кодом 1 */

void	ft_free_memory_envp_list(t_list **envp_list);
/*функция очистки памяти переменных окружения в листах (без exit!)*/

char	**ft_new_envp(t_list **envp_list);
/*функция сохраняет переменные окружения в двухмерный массив
в случае ошибки чистит за собой память и возвращает NULL
использует маллок! - для очистки используй ft_free_memory_matrix(char **matrix)
где x - размер "массива первого порядка"*/

void	ft_free_memory_matrix(char **matrix);
/*функция для очиски памяти от двухмерного массива*/


/* PARSER */


void	ft_lexer(t_lexer **lexer, char	*input);
/*функция разбивает полученную строку на отдельные блоки
и сохраняет их в односвязанном списке для дальнейшего парсинга 
в случае если строка пустая или содержит только пробелы возврашает
пустую строку в lexer->chank */


void	ft_free_memory_lexer_list(t_lexer **lexer);
/*функция для очиски памяти от односвязанного списка 
создаваемого ft_lexer(t_lexer **lexer, char	*input);
после очиски памяти значение *lexer = NULL */

void	ft_create_lexer(t_lexer **lexer, char *input, int start, int stop);
/*функция создает отдельный лист односвязаннго списка lexer
была вынесена поскольку вызывающие ее функции не поместились в один файл
(вызывается из файла lexer_utils.c) */

void	ft_lexer_word(t_lexer **lexer, char *input, int *start, int *stop);
/*функция сохраняет в листы все что не \ < > << >> " ' ; | или до этих
символов */

void	ft_lexer_spase(t_lexer **lexer, char *input, int *start, int *stop);
/*функция в случае встречи пробелов пропускает их все и сохраняет один пробел
в лист */

void	ft_lexer_delim(t_lexer **lexer, char *input, int *start, int *stop);
/*если "\\" идет в конце строки то сохранен будет только "\\"!
проверить в парсере!!!!! */

void	ft_lexer_s_quotes(t_lexer **lexer, char *input, int *start, int *stop);
/*функция сохраняет в лист все что между ' , а если нет закрывающей, то
до конца строки
одинарные ковычки экранируют все: "$" и "\" */

void	ft_lexer_d_quotes(t_lexer **lexer, char *input, int *start, int *stop);
/*функция сохраняет в лист все что между " , а если нет закрывающей, то
до конца строки
в данной функции отдельно обработан случай "\"\0 - будет сохранено в лист "\ ,
что легко отловить через проверку открыл кавычки - закрыл кавычки 
следует учитывать что двойные кавычки не экранируют $ */

void	ft_lexer_run_space(t_lexer **lexer, char *input, int *start, int *stop);
/*функция пропускает все пробелы в начале строки
в случае если строка пустая или состоит только из пробелов
создает лист с пустой строой*/

void	ft_lexer_redirect(t_lexer **lexer, char *input, int *start, int *stop);
/*функция сохраняет в листы алмазные кавычки
в случае если ковычек больше 2 сохраняет попарно в новый лист*/

int	ft_parser(t_shell *mini);
/*главная функция парсера - запускается после лексера и вызывает остальные 
функции проверки */

int	ft_exam_backslash(t_shell *mini);
/*функция проверяет есть ли любой знак после \ в конце строки
если нет, то выводит сообщение об ошибке */

int	ft_exam_pipe_first_last_double(t_shell *mini);
/*функция проверяет есть ли хоть чтото перед | и нет ли | в конце строки,
а так же не стоят ли друг за другом ; и | и нет ли двойного написания ; и |
если да, то выводит сообщение об ошибке */

int	ft_exam_syntax_quotes(t_shell *mini);
/*функция проверяет были ли закрыты кавычки, если нет то выводит сооббщение
об ошибке */

int	ft_exam_double_redirect(t_shell *mini);
/*функция проверяет нет ли идущих друг за другом редиректа, включая разделенных
пробелом. если да, то выводит сообщение об ошибке */

// int	ft_exam_double_pipe(t_shell *mini);
/*функция проверяет нет ли идущих друг за другом пайпа, включая разделенных
пробелом. если да, то выводит сообщение об ошибке */

void	ft_print_parser_error(t_lexer **lexer, int exeption);
/*функция вывода сообщений об ошибках во 2 поток */

/* libft */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	ft_free_memory_split(char **matrix, int x);
size_t	ft_strlen_value(const char *s);
size_t	ft_strlen_key(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);		//check this ft!!
char	*ft_itoa(int n);

/* get next line */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 210
# endif

char	*get_next_line(int fd);
char	*ft_read_file(char *line, char *reminder, int fd);
char	*ft_find_line(char *reminder);
void	ft_new_reminder(char *reminder);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_free_reminder(char *reminder);
char	*ft_copy_in_line(char *line, char *reminder);
char	*ft_copy_from_read(char *line, char *reminder);

#endif
