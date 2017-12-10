##
## Makefile for  in Makefile
## 
## Made by Lucas Santoni
## Login   <lucas.santoni@epitech.eu>
## 
## Started on  Sun Apr  9 23:47:22 2017 Bilel Fourati
## Last update Fri Apr 28 19:09:58 2017 Bilel Fourati
##

CC	= gcc -g3

CFLAGS	+= -Iincludes

SRCS	+= srcs/main.c \
	   srcs/chip8.c 

OBJS	= $(SRCS:.c=.o)

NAME	= chip8

RM	= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
