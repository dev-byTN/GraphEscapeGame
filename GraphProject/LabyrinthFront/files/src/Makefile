EXEC = escapeLabyrinth

SRC = main.c graph.c display.c ../../json/json.c ../../json/readJson.c ../../../LabyrinthBackEnd/src/graph.c  

CFLAGS = -Wall

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -I/usr/local/include -L/usr/local/lib

all: $(EXEC)

$(EXEC): $(SRC)
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXEC)
