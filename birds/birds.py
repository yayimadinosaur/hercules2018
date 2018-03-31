# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    birds_new.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wfung <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/30 15:24:09 by wfung             #+#    #+#              #
#    Updated: 2018/03/30 23:52:51 by wfung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import os
import shutil
#import os.path

#if arg2 == create AND arg3 exists

def create_files_flag(arg2):
    print("files flag test arg3[%s]" % arg2)
    x = sys.argv[3]
    if x[0] == '/':
        print("Invalid filename")
        exit()
    if arg2 == "-f":
        print("-f passes")
        if check_file_status(arg2) == 0:
            if x[0] == '/':
                print("Invalid filename")
                exit()
            create_file(sys.argv[3])
    elif arg2 == "-d":
        print("-d passes")
        if check_dir_status(arg2) == 0:
            if x[0] == '/':
                print("Invalid filename")
                exit()
            create_dir(sys.argv[3])
    elif arg2 == "-e":
        print("-e passes")

def usage_flags_create(arg3):
    print("checking flag %s" % arg3)
    if arg3 == "-f":
        print("-f creates file")
        return True
    elif arg3 == "-d":
        print("-d creates dir")
        return True
    elif arg3 == "-e":
        print("-e creates empty file")
        return True
    elif arg3 == "--help":
        print("usage:\n create: \n      -d for directory\n      -f for file\n     -e for empty files")
        return True
    else:
        print("%s is not a valid flag" % arg3) #
        return False

#validates arg1

def validate(check_input):
    print("validating commands") #
    print("[check_input is [%s]" % check_input) #
    if check_input == "create":
        if usage_flags_create(sys.argv[2]):
            print("flag detected, missing 1 arg for name")
            exit()
        if sys.argv[2] == ".gitignore":
            print("found gitignore")
            check_exist()
            create_git_ignore()
            exit()
        if sys.argv[2] == "-c_projects":
            print("found c_projects")
            create_c_projects()
            exit()
        check_exist()
        create_file(sys.argv[2])

def parse_filename():
    print("parsing filename")

#usages

def show_usage_specific(arg1):
    if arg1 == "create":
        print("create : creates empty files (by default)\n   usage: create [-d -f -e] [filename]")
    elif arg1 == "hi":
        print("feature coming soon!")
    else:
        print("[%s] command not found" % arg1)
    exit()

def show_usage():
    print("Usage: birds.py arg1\n  possible arg1:\n    create")
    exit()

#returns 0 if file doesn't exist, 1 if file doesn't exist
def check_file_status(file_name):
    print("checking file status of [%s]" % file_name)
    if os.path.isfile(file_name):
        print("file [%s] exists\n exiting program" % file_name)
        exit()
    elif not os.path.isfile(file_name):
        print("file [%s] does not exist" % file_name)
        return 0 

def check_exist():
    if os.path.exists(sys.argv[2]):
        print("file exists")
        exit()

#returns 0 if directory doesn't exist, 1 if directory doesn't exist
def check_dir_status(dir_name):
    print("checking directory status of [%s]" % dir_name)
    if os.path.isdir(dir_name):
        print("directory [%s] exists\nexiting program" % dir_name)
        exit()
    elif not os.path.isdir(dir_name):
        print("directory [%s] does not exist" % dir_name)
        return 0

#creates stuff
def create_makefile(exec_name):
    check_file_status("Makefile")
    create_file_custom("Makefile", """# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wfung <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/11 14:50:44 by wfung             #+#    #+#              #
#    Updated: 2018/01/05 16:59:27 by wfung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   """ + exec_name + """

CC		=	gcc

FLAG	=	-Wall -Wextra -Werror

SRCS	=	

OBJ     =	${SRCS:.c=.o}

INCLUDE	=	-I

all: $(NAME)

$(OBJ):
		@$(CC) $(FLAG) -c $(SRCS)

$(NAME): $(OBJ)
		@make all -C libft
		@$(CC) $(FLAG) $(INCLUDE) $(OBJ) -o $(NAME)

clean:
		@make clean -C libft
		@/bin/rm -f $(OBJ)

fclean: clean
		@make fclean -C libft
		@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean""")

def create_c_projects():
    root_dir = input("Name of rootdir:\n")
    executable_name = input("Name of Executable:\n")
    srcs_all = []
    includes_all = []
    create_makefile(executable_name)
    while (1):
        srcs = input("Name of Sources:\n[type !finish when finished]\n")
        if srcs == "!finish":
            break
        srcs = srcs + ".c"
        create_file(srcs)
        srcs_all.append(srcs)
    while (1):
        includes = input("Name of includes:\n[type !finish when finished]\n")
        if includes == "!finish":
            break
        includes = includes + ".h"
        create_file(includes)
        includes_all.append(includes)
    create_dir("includes")
    create_dir("srcs")
    for i in srcs_all:
        shutil.move(os.path.abspath(i), os.path.abspath("srcs"))
    for j in includes_all:
        shutil.move(os.path.abspath(j), os.path.abspath("includes"))
    shutil.move(os.path.abspath("srcs"), os.path.abspath(root_dir))
    shutil.move(os.path.abspath("includes"), os.path.abspath(root_dir))
    shutil.move(os.path.abspath("Makefile"), os.path.abspath(root_dir))
    print("Makefile, srcs dir, includes dir, srcs, includes, all inside of %s" % root_dir)

def create_git_ignore():
    print("creating .gitignore in current directory")
    if check_file_status(".gitignore") == 0:
        create_file_custom(".gitignore", '# Compiled source #\n###################\n*.com\n*.class\n*.dll\n*.exe\n*.o\n*.so\n\n# Packages #\n############\n# it\'s better to unpack these files and commit the raw source\n# git has its own built in compression methods\n*.7z\n*.dmg\n*.gz\n*.iso\n*.jar\n*.rar\n*.tar\n*.zip\n\n# Logs and databases #\n######################\n*.log\n*.sql\n*.sqlite\n\n# OS generated files #\n######################\n.DS_Store\n.DS_Store?\n._*\n.Spotlight-V100\n.Trashes\nehthumbs.db\nThumbs.db')

def create_dir(file_name):
    #if len(sys.argv) > 2:
    if (check_dir_status(file_name) == 0):
        print("creating dir [%s] in current directory..." % file_name)
        os.mkdir(file_name)

def create_file(file_name):
    #if len(sys.argv) > 2:
    if (check_file_status(file_name) == 0):
        print("creating file in current directory...")
        test = open(file_name, 'a')
        test.close()

def create_file_custom(file_name, content):
    with open(file_name, 'a') as test:
        test.write(content)
    test.close()

def main():
    args = len(sys.argv)
    if args < 2:
        show_usage()
    if args >= 2:
        #old commands
        #choices = {'create': create_file(), '2': 'hi'}
        valid_cmds = ["create", "hi"]
        arg1 = sys.argv[1]
        if arg1 not in valid_cmds:
            print("Invalid command [%s]\n-----" % arg1)
            show_usage()
        if args == 2:
            show_usage_specific(arg1)
        if args == 3:
            validate(sys.argv[1]) 
        elif args == 4:
            create_files_flag(sys.argv[2])
        elif args > 4:
            print("4+ args")

if __name__ == "__main__":
    #debugging til line 75 or line before main
    print("total args %s\n-----\ndebug" % len(sys.argv))
    i = 0
    for i in range(len(sys.argv)):
        print("arg" + str(i) + ' = ' +  sys.argv[i])
    print("-----")
    main()
