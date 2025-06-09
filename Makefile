OUT = log
SRC = logger.c

all:
	gcc $(SRC) -o $(OUT) -lSDL2 -lSDL2_ttf

install: all
	sudo cp $(OUT) /usr/local/bin/
	sudo setcap cap_dac_read_search+ep /usr/local/bin/$(OUT)

run: all
	sudo -E ./$(OUT)

clean:
	rm -f $(OUT)
