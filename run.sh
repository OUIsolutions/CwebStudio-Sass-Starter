
chmod +x zip
gcc src/main.c -fsanitize=address
./a.out