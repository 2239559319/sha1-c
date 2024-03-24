format:
	clang-format -i test.c sha1.hpp

test-build:
	gcc test.c -o test
test: test-build
	./test