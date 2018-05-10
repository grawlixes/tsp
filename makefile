# TO RUN THE PROGRAM:
# -type "make" in the directory to create the two executables
# -./naiveTSP <input file name>
# -./bnbTSP <input file name>
# where the input file name is a matrix of values representing
# an adjacency matrix for the group of cities

TARGET1=naiveTSP
TARGET2=bnbTSP

# Specifiy the target
all:	$(TARGET1) $(TARGET2)

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
$(TARGET1):	$(TARGET1).o $(TARGET2).o
	g++ $(TARGET1).o -o $(TARGET1) 
	g++ $(TARGET2).o -o $(TARGET2) 

# Specify how the object files should be created from source files
$(TARGET1).o:	$(TARGET1).cpp $(TARGET2).cpp
	g++ -c -Wall $(TARGET1).cpp
	g++ -c -Wall $(TARGET2).cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -rf *.o $(TARGET1) $(TARGET2) ribeiro_leandro.zip ribeiro_leandro

run:	$(TARGET1) $(TARGET2)
	./$(TARGET1) input.txt
	./$(TARGET2) input.txt

zip: $(TARGET1)
	mkdir ribeiro_leandro
	cp *.txt makefile $(TARGET1).cpp $(TARGET2).cpp ribeiro_leandro/
	zip -r ribeiro_leandro.zip ribeiro_leandro/
