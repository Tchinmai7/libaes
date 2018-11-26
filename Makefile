CC=gcc
#TODO: Add compiler flags to secure against buffer overflow
CFLAGS=-Wall -Werror -Wextra -O3  -fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 -pedantic -pedantic-errors -pie -Wformat -Wformat-security 
#-Wconversion -Wstack-protector -Wsign-conversion
DEPS = aes.h inv_aes.h decrypt.h encrypt.h utils.h padding.h
OBJ = aes.o inv_aes.o encrypt.o decrypt.o driver.o utils.o padding.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

aes_sample: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)

.PHONY: clean valgrind 

clean:
	rm -f aes_sample
	rm -f *.o   

valgrind:
	valgrind -v --leak-check=yes --track-origins=yes ./aes_sample IsthisthereallifeIsthisjustfantasyCaughtinalandslideNoescapefromrealityOpenyoureyesLookuptotheskiesandseeI\'mjustapoorboyIneednosympathyeasycomeeasygowillyoulet
