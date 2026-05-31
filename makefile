CC = mpicxx
OBJS = TestJeu.o position.o arbitre.o JoueurMPI.o Plateau3D.o Joueur.o JoueurIA.o IA_MinMax.o IA_Aleatoire.o 

exe : exe1 exe2 exe3

exe1 :	$(OBJS)
	${CC} -o exe1 $(OBJS)
exe2 :  $(OBJS)
	${CC} -o exe2 $(OBJS)
exe3 :  $(OBJS)
	${CC} -o exe3 $(OBJS)

%.o: src/%.cpp
	${CC} -c $< -o $@

clean :
	rm -f *.o exe

run :
	mpirun -n 3 ./exe1 ./exe2 ./exe3