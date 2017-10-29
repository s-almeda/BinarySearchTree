CC = gcc
CFLAGS = 

TARGET = pa2


all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)