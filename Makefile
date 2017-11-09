#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/10/23 17:48:20 by psebasti          #+#    #+#             *#
#*   Updated: 2017/11/09 12:16:22 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME		=	minishell

NOC			=	\033[0m
DEBC		=	\033[36m
OKC			=	\033[32m
ERC			=	\033[31m
WAC			=	\033[33m

CMP			=	gcc

DEBUG_F		=	-g3 -fsanitize=address

FLAGS		=	-Wall -Wextra -Werror 

OBJDIR		=	./obj/
INCDIR		=	./includes/
SRCDIR		=	./srcs/

LFTDIR		=	./libft/
LIBS		=	-lft -framework OpenGL -framework AppKit

OBJNAME		=	$(SRCNAME:.c=.o)
INCNAME		=	minishell.h \
				minishell_define.h \
				minishell_struct.h
SRCNAME 	=	minishell.c \

SRC		= 	$(addprefix $(SRCDIR),$(SRCNAME))
OBJ		= 	$(addprefix $(OBJDIR),$(OBJNAME))
INC		= 	$(addprefix -I,$(INCDIR),$(INCNAME))

EXT			=	Makefile

debug : all

all: $(NAME) $(EXT)

$(NAME): $(OBJ)
	@echo
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@echo "$(DEBC)$(NAME):\t\t$(NAME) DEBUG MODE$(NOC)"
	@echo "$(DEBC)IF YOU WANT TO SWITCH TO RELEASE VERSION 'make re'$(NOC)"
	@echo "$(DEBC)⤜(ʘvʘ)⤏$(NOC)"
	@make debug -C $(LFTDIR)
	@$(CMP) $(FLAGS) $(DEBUG_F) -o $(NAME) -L $(LFTDIR) $(LIBS) $^ -o $@
else
	@make -C $(LFTDIR)
	@$(CMP) $(FLAGS) -o $(NAME) -L $(LFTDIR) $(LIBS) $^ -o $@
	@echo "$(OKC)$(NAME):\t\t$(NAME) READY$(NOC)"
	@echo "$(OKC)¯\_ツ_/¯$(NOC)"
endif

$(OBJDIR)%.o: $(SRCDIR)%.c
ifneq (,$(filter debug,$(MAKECMDGOALS)))
	@mkdir -p $(OBJDIR) 2> /dev/null || true
	@$(CMP) -c -o $@ $< $(INC) $(FLAGS) $(DEBUG_F)
	@echo -n .
else
	@mkdir -p $(OBJDIR) 2> /dev/null || true
	@$(CMP) -c -o $@ $< $(INC) $(FLAGS)
	@echo -n .
endif

clean:
	@make -C $(LFTDIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(WAC)$(NAME):\t\tRemoving OBJ dir: ./obj/$(NOC)"

fclean: clean
	@make -C $(LFTDIR) fclean
	@rm -f $(NAME)
	@echo "$(WAC)$(NAME):\t\tRemoving $(NAME) executables$(NOC)"

re: fclean all

.PHONY: $(NAME) all clean fclean re
