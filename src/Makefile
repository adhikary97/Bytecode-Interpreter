TARGET = main
GCC = g++
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic
CC = $(GCC) $(CFLAGS)
SRCS = stack.cpp
OBJS = $(SRCS:%.cpp=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

all: $(TARGET) testall

testall: test1 test2 test3 test4 test5 test6 test7 test8

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test1: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Basics.bin > Basics_out.txt

test2: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Math.bin > Math_out.txt

test3: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Comparisons.bin > Comp_out.txt

test4: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Jumps.bin > Jumps_out.txt

test5: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Push_Pop.bin > Push_Pop.txt

test6: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Peek_Poke.bin > Peek_Poke.txt

test7: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Interpreter_Input.bin > Inpterpreter.txt
test8: $(TARGET)
	./main /Users/parasadhikary/Downloads/school/ece30862/project1/Structured_Tests_Final/Test_Binaries/Subroutines.bin > Sub_out.txt

.c.o:
	$(GCC) $(CFLAGS) -c $*.cpp
clean:
	rm -f $(OBJS) $(TARGET)
