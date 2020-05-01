CC = cc
FILES = example_project.c test_suite_one.c test_suite_two.c strend.c /Users/darbinreyes/dev/experiments/C/c-misc/helloworld/not_manic_2_11_2016/seatest/src/seatest.c
OUT_EXE = example

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -Wno-parentheses-equality -I /Users/darbinreyes/dev/experiments/C/c-misc/helloworld/not_manic_2_11_2016/seatest/src

clean:
	rm -f *.o core

rebuild: clean build
