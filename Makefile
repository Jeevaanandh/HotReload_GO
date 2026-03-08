CC = gcc
CFLAGS = -Wall

TARGET = hotreload
SRC = cli.c directoryWatcher.c startServer.c
OBJ = $(SRC:.c=.o)

PREFIX = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	sudo cp $(TARGET) $(PREFIX)/$(TARGET)
	sudo chmod +x $(PREFIX)/$(TARGET)
	@echo "Installed $(TARGET) to $(PREFIX)"

uninstall:
	sudo rm -f $(PREFIX)/$(TARGET)
	@echo "$(TARGET) removed from $(PREFIX)"

clean:
	rm -f $(OBJ) $(TARGET)