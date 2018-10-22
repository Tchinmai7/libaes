CC=gcc
CFLAGS=-Wall -Werror -I.
DEPS = aes.h inv_aes.h decrypt.h encrypt.h
OBJ = aes.o inv_aes.o encrypt.o decrypt.o driver.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

aes_sample: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f aes_sample
	rm -f *.o   
