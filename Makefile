format:
	clang-format -i test.c sha1.h sha1.c

test-build:
	gcc sha1.c test.c -o test
test: test-build
	./test