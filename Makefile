NAME= Container
#************************PARSING************************#

#************************************************#
SRC_PATH= ./
HDR_PATH= ./
OBJ_PATH= objects


SRC_NAME= main.cpp\


HDR_NAME= iterator.hpp\
				NormalIterator.class.hpp\
				ReverseIterator.class.hpp\
				Vector.class.hpp\

OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

H_FLAG= -I $(HDR_PATH)


# FLAGS= -Wall -Wextra -Werror

COMP= clang++

all: $(NAME)

$(NAME) :  $(OBJ)  $(HDR)
	@$(COMP) $(H_FLAG) $(FLAGS) $(OBJ) -o $@
	@echo "   ______            __        _                     "
	@echo "  / ____/___  ____  / /_____ _(_)___  ___  __________ "
	@echo " / /   / __ \/ __ \/ __/ __ \`/ / __ \/ _ \/ ___/ ___/ "
	@echo "/ /___/ /_/ / / / / /_/ /_/ / / / / /  __/ /  (__  )  "
	@echo "\____/\____/_/ /_/\__/\__,_/_/_/ /_/\___/_/  /____/   "
	@echo "		   Compilation of ft_containers: \033[1;32mOK\033[m"
	@./$(NAME)
                                                     



$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp 
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) $(FLAGS) $(H_FLAG) -o $@ -c $<


clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 


fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31m>> $(NAME) is deleted.\033[0m" 

re : fclean clear all

clear:
	clear