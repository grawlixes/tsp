TARGET1=naiveTSP

# Specifiy the target
all:	$(TARGET1)

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
$(TARGET1):	$(TARGET1).o
	g++ $(TARGET1).o -o $(TARGET1) 

# Specify how the object files should be created from source files
$(TARGET1).o:	$(TARGET1).cpp
	g++ -c -Wall $(TARGET1).cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -rf *.o $(TARGET1) ribeiro_leandro.zip ribeiro_leandro

run:	$(TARGET1)
	./$(TARGET1) input.txt 0

zip: $(TARGET1)
	mkdir ribeiro_leandro
	cp declaration.txt readme.txt makefile $(TARGET1).cpp ribeiro_leandro/
	zip -r ribeiro_leandro.zip ribeiro_leandro/
