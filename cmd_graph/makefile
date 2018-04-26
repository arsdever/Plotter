C		=	g++
FLAGS	=	-std=c++11
TARGET	=	../../linux64/cmd_basic/

FILES 	=	cmd_graph_delete \
			cmd_graph_find \
			cmd_graph_new \
			cmd_graph_print\
			cmd_graph_set


OBJECT = $(patsubst %, %.obj, $(FILES))

all: set build

set:
	if [ ! -d "$(TARGET)" ]; then mkdir $(TARGET); fi

build: $(addprefix $(TARGET), $(OBJECT))

$(TARGET)%.obj : %.cpp
	$(C) -c -o $(TARGET)$@ $^ $(FLAGS)

clean:
	rm -f $(addprefix $(TARGET), $(OBJECT))