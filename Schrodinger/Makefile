CC      = gcc                   # What compiler to use
CFLAGS  = -I. -lm               # Flags to pass to C compiler. -I means to look in the same directory as the source for the .h header. -lm means $
RM      = rm -f                 # Define a standard remove command


default: all                    # Define default command. Just running 'make' does this.

all: schroedinger_test                              # Default command is to do Hello

schroedinger_test: main_schroedinger.c schroedinger.c init.c radial_eq_functions.c extremum.c solve.c derivatives.c numerov.c vector_mtx.c  # Compiles the program. Can also be run with 'make Hello'
	$(CC)  -o schroedinger_test main_schroedinger.c schroedinger.c  init.c radial_eq_functions.c extremum.c solve.c derivatives.c numerov.c vector_mtx.c $(CFLAGS)


clean veryclean:                # Removes the Hello executable with the defined RM command. Run with 'make clean'
	$(RM) schroedinger_test yb.dat yf.dat schroed_params.dat schroedinger.dat plot_data.dat


