CC = gcc
CFLAGS = -W
TARGET = testlib
OBJECTS = list.o hash.o bitmap.o list_command.o hash_table_command.o bitmap_command.o 20151607.o

all = $(TARGET)

$(TARGET) : $(OBJECTS)
			  $(CC) $(CFLAGS) -o $@ $^
clean : 
	rm -f $(TARGET) $(OBJECTS)
