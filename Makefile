all: questions

questions: qtree.o main.o file.o
	g++ -o $@ $^

%.o: %.cpp qtree.h
	g++ -c -Wall -o $@ $<

.PHONY: clean
clean:
	rm -f questions *.o 
	
#Here, write commands to invoke the executible and verify its behavior
#The first is given as an example with three commands
#  1: run the program with "user input" coming from the file test_scripts/simple_script.txt, and 
#     saving the program output in log.txt
#  2: compare log.txt with the sample output in test_scripts/simple_script.out
#  3: compare the written tree (requested by the user in the script) to the tree file example_trees/pb.txt
test:
	./questions < test_scripts/simple_script.txt > log.out
	diff log.out test_scripts/simple_script.out
	diff pb.qtree example_trees/pb.qtree
	
	#test that creates some nodes and revists them
	./questions < test_scripts/test_one.txt > log.out
	diff log.out test_scripts/test_one.out
	diff test_one.qtree example_trees/test_one.qtree
	
	./questions < test_scripts/rockandstick.txt > log.out
	diff log.out test_scripts/rockandstick.out
	diff rockandstick.qtree example_trees/rockandstick.qtree
	
	#test that uses a pre-built tree and creates a couple of nodes in that tree
	./questions example_trees/stumptown.qtree < test_scripts/script.txt > log.out
	diff log.out test_scripts/responses.out
	diff stumptown1.qtree example_trees/stumptown1.qtree