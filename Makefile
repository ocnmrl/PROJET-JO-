# Define the compiler
CC = gcc

# Define the flags
CFLAGS = -Wall -Wextra -Werror

# Define the target executable
TARGET = jo

# Define the source files
SRCS = main.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
