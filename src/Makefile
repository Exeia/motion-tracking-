CFLAG=`pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`


OBJ= Motion.o



Project2: $(OBJ)
	g++ $(CFLAG) $(LIBS) -o Project2 Main.cpp $(OBJ)


Motion.o: Motion.cpp 
	g++ $(CFLAG) $(LIBS) -o $@ -c $^
   	

clean:
	@for obj in $(OBJ); do\
		if test -f $$obj; then rm $$obj; fi; done
	@if (test -f Project1); then rm Project2; fi;

