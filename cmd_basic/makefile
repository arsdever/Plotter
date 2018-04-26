C		=	g++
FLAGS	=	-std=c++11
TARGET	=	../../linux64/cmd_graph/

FILES 	=	cmd_delete \
			cmd_exit \
			cmd_find \
			cmd_help\
			cmd_load \
			cmd_new \
			cmd_print\
			cmd_save


OBJECT = $(patsubst %, %.obj, $(FILES))

all: set build

set:
	if [ ! -d "$(TARGET)" ]; then mkdir $(TARGET); fi

build: $(addprefix $(TARGET), $(OBJECT))

$(TARGET)%.obj : %.cpp
	$(C) -c -o $(TARGET)$@ $^ $(FLAGS)

clean:
	rm -f $(addprefix $(TARGET), $(OBJECT))