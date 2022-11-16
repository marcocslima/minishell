# 42 minishell

This is a simple Shell program that will run the most part of shell commands.

Just compile and run it with ./minishell

You can run it with valgrind but the readline library need to be supressed:

valgrind --suppressions=./local.supp --leak-resolution=med --leak-check=full --show-leak-kinds=all ./minishell

We have built for this project our own cd , env, echo, pwd export and unset functions.
The other functions are looked for the program in the /bin folder.

You can use commands like :

Redirects and pipes.


ls > file

ls >> file1 >> file2 >file23

cat << eof >> file3

ls | cat

ls | cat | grep 42

ls | cat > cat.txt

cat < file | wc > file2.txt

You can use Ctrl + D, Ctrl + C commands.


You can try any commands.

ls -l 

wc -l 

/bin/ls

Builtin commands


    echo
    
echo hello

echo -n hello

echo "Hello '$USER'"

echo 'Hello "$USER"'

    cd
    
    
cd ./dir

cd /bin

cd ..

cd ~

  pwd
  
pwd

   export
   
export PATH="/"

export x=1

export


    unset
    
unset x

unset

    env
    
env

env | grep 10

    exit
    
exit

exit 42

exit --1
