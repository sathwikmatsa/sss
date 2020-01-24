sss: src/main.cpp src/shamir.cpp
	g++ -pedantic -Wall -Wextra -Wcast-align -Wcast-qual\
		-Wmissing-declarations -Wnoexcept -Wredundant-decls\
		-Wshadow -Wsign-conversion -Wundef -Werror -Wno-unused\
		src/main.cpp src/shamir.cpp -o sss -std=c++2a

clean:
	rm -f *.o sss
