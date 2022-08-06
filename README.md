# Minishell
> As beautiful as a shell

A 42 project (with [Acuna @ojospeh](https://github.com/acunathink)), where we implemented a simple POSIX Shell in C. The program parses a prompt, launches with arguments and executables, and also works with built-in commands which were written by our team. The development was guided by the behavior of the bash shell.  

## Common Instructions
A detailed description of common instructions located in the root of repository in the file [en.subject.pdf](en.subject.pdf)

## Install
Compatible with Linux and MacOS, the program requires an installed **readline** library:

    git clone https://github.com/Mulwe/minishell.git
	  cd minishell
	  make

## How it works

![image](https://user-images.githubusercontent.com/22121138/183248245-4875f19b-361c-4960-8968-9f621fef1f4a.png "minishell test")

## Final grade: 100/115

Mandatory part: 100/100
Bonus part: 0/15

It tooks about two weeks to complete the task. I was responsible for the parsing, argument checking, execution, redirection and piping.

# Minishell

Командный проект сделанный в рамках school 21 (Ecole 42) (с [Acuna @ojospeh](https://github.com/acunathink)), в котором мы реализовали простой POSIX Shell на C. Программа парсит приглашение, запускается с аргументами и исполняемыми командами, а также работает со встроенными командами (builtins), которые были написаны нашей командой. При разработке ориентировались на поведение bash оболочки.

## Общие инструкции
Подробное описание всех инструкций находится в корне репозитория в файле [en.subject.pdf](en.subject.pdf)

## Установка
Программа совместима с Linux и MacOS, для работы требуется установленная библиотека **readline**:

    	git clone https://github.com/Mulwe/minishell.git
	cd minishell
	make

## Как это работает

![image](https://user-images.githubusercontent.com/22121138/183248245-4875f19b-361c-4960-8968-9f621fef1f4a.png "minishell test")

## Итоговая оценка: 100/115

Обязательная часть: 100/100
Бонусная часть: 0/15 

На выполнение задания было потрачено около двух недель. Я отвечала за парсинг и проверку аргументов, выполнение встроенных команд, перенаправление и работу piping (конвеера или трубы (pipe)).
Pipe, или конвеер обеспечивает асинхронное выполнение команд с использованием буферизации ввода/вывода. Таким образом все команды в конвеере работают параллельно, каждая в своем процессе.
