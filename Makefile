sss: main.cpp
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual\
		-Wmissing-declarations -Wnoexcept -Wredundant-decls\
		-Wshadow -Wsign-conversion -Wundef -Werror -Wno-unused\
		main.cpp -o sss
clean:
	rm -f *.o sss
