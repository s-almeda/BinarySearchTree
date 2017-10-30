CC = gcc
CFLAGS = 

TARGET = pa2


all: $(TARGET)
	$(CC) $(CFLAGS) -o bst $(TARGET).c

clean:
	$(RM) $(TARGET)
