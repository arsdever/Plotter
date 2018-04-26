C		=	g++
FLAGS	=	-std=c++11
TARGET	=	../linux64/
SUBDIRS	=	$(wildcard */)
EXE		=	graph

FILES	= 	ccommand \
			cgraph \
			cresult \
			itype \
			main

OUTPUT	=	graph

OBJECT = $(patsubst %, %.obj, $(FILES))

all: set $(EXE)

set:
	if [ ! -d "$(TARGET)" ]; then mkdir $(TARGET); fi
	for DIR in $(SUBDIRS); do $(MAKE) -C $$DIR; done

$(EXE): $(addprefix $(TARGET), $(OBJECT))
	$(C) -o $(TARGET)$@ $^ $(FLAGS) $(TARGET)/cmd_basic/*.obj $(TARGET)/cmd_graph/*.obj

$(TARGET)%.obj : %.cpp
	$(C) -c -o $(TARGET)$@ $^ $(FLAGS)

clean:
	rm -f $(addprefix $(TARGET), $(OBJECT)) $(addprefix $(TARGET), $(OUTPUT))
	$(MAKE) clean -C cmd_basic
	$(MAKE) clean -C cmd_graph