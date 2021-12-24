NAME= Container

#*************************PATH*************************#
SRC_PATH= ./
HDR_CONTAINERS_PATH= Containers
HDR_ITERATORS_PATH= Iterators
HDR_NEEDED_PATH= NeededTemplates

OBJ_PATH= Objects

#*************************NAME*************************#
SRC_NAME= mainMap.cpp\

HDR_CONTAINERS_NAME= Vector.class.hpp\
				Map.class.hpp\
				Stack.class.hpp\
				Set.class.hpp\

HDR_ITERATORS_NAME= iterator.hpp\
				NormalIterator.class.hpp\
				ReverseIterator.class.hpp\

HDR_NEEDED_NAME= enable_if.hpp\

OBJ_NAME= $(SRC_NAME:.cpp=.o)

#************************COMPILING************************#
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

HDR_CONTAINERS= $(addprefix $(HDR_CONTAINERS_PATH)/,$(HDR_CONTAINERS_NAME))
HDR_ITERATORS= $(addprefix $(HDR_ITERATORS_PATH)/,$(HDR_ITERATORS_NAME))
HDR_NEEDED= $(addprefix $(HDR_NEEDED_PATH)/,$(HDR_NEEDED_NAME))

HDR_ALL= $(HDR_NEEDED)  $(HDR_CONTAINERS) $(HDR_ITERATORS) 

H_FLAG= -I $(HDR_CONTAINERS_PATH) -I $(HDR_ITERATORS_PATH) -I $(HDR_NEEDED_PATH)


FLAGS= -Wall -Wextra -Werror

COMP= clang++ -std=c++98 -g

all: $(NAME)

$(NAME) :  $(OBJ) $(HDR_ALL)
	@$(COMP) $(H_FLAG) $(FLAGS) $(OBJ) -o $@
	@echo "   ______            __        _                     "
	@echo "  / ____/___  ____  / /_____ _(_)___  ___  __________ "
	@echo " / /   / __ \/ __ \/ __/ __ \`/ / __ \/ _ \/ ___/ ___/ "
	@echo "/ /___/ /_/ / / / / /_/ /_/ / / / / /  __/ /  (__  )  "
	@echo "\____/\____/_/ /_/\__/\__,_/_/_/ /_/\___/_/  /____/   "
	@echo "		   Compilation of ft_containers: \033[1;32mOK\033[m"
	# @./$(NAME)
                                                     



$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HDR_ALL)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) $(FLAGS) $(H_FLAG) -o $@ -c $<

ss:
	@echo "in out in out in out"
clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 


fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31m>> $(NAME) is deleted.\033[0m" 

re : fclean clear all

clear:
	clear