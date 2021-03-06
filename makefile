#
# Specifiy the target
all:	program1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program1: Story.o Paragraph.o Sentence.o Word.o driver.o
	g++ Story.o Paragraph.o Sentence.o Word.o driver.o -o program1

# Specify how the object files should be created from source files
Story.o: Story.cpp
	g++ -g -c Story.cpp
Paragraph.o: Paragraph.cpp
	g++ -g -c Paragraph.cpp
Sentence.o: Sentence.cpp
	g++ -g -c Sentence.cpp
Word.o: Word.cpp
	g++ -g -c Word.cpp
driver.o: driver.cpp
	g++ -g -c driver.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program1

