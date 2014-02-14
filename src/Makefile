CFLAG=`pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`


##OBJ= Lab_Color.o



Project2: 
	g++ $(CFLAG) $(LIBS) -o Project2 Main.cpp  


##Lab_Color.o: Lab_Color.cpp 
##	g++ $(CFLAG) $(LIBS) -o $@ -c $^
   	

clean:
	@for obj in $(OBJ); do\
		if test -f $$obj; then rm $$obj; fi; done
	@if (test -f Project1); then rm Project2; fi;

