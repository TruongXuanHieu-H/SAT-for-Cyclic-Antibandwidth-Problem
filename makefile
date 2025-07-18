OBJDIR=build
SRCDIR=src

OBJECTS= graph.o signal_handler.o usage.o version.o cabw_encoder.o
OBJS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJECTS))

FLAGS= -Wall -Werror -Wextra -O3 -DNDEBUG
IGNORE_ASSERTVARS= -Wno-unused-but-set-variable
STANDARD= -std=c++11

CADICAL_INC=./solver/cadical/
CADICAL_LIB_DIR=./solver/cadical/
CADICAL_LIB=-lcadical

all : $(OBJDIR)/interface.o
	g++ $(FLAGS) $(OBJDIR)/interface.o $(OBJS) -L$(CADICAL_LIB_DIR) $(CADICAL_LIB) -o build/cabw_enc

$(OBJDIR)/interface.o : $(SRCDIR)/interface.cpp $(OBJS) $(SRCDIR)/cabw_encoder.h $(SRCDIR)/utils/signal_handler.h $(SRCDIR)/utils/usage.h $(SRCDIR)/utils/version.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/enum/search_strategy.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/cabw_encoder.o : $(SRCDIR)/cabw_encoder.cpp $(SRCDIR)/cabw_encoder.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/enum/search_strategy.h $(SRCDIR)/graph/graph.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/signal_handler.o : $(SRCDIR)/utils/signal_handler.cpp $(SRCDIR)/utils/signal_handler.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/usage.o : $(SRCDIR)/utils/usage.cpp $(SRCDIR)/utils/usage.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/version.o : $(SRCDIR)/utils/version.cpp $(SRCDIR)/utils/version.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/graph.o : $(SRCDIR)/graph/graph.cpp $(SRCDIR)/graph/graph.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

#.PHONY : clean
clean:
	rm -f *.a $(OBJDIR)/*.o *~ *.out  $(OBJDIR)/cabw_enc

tar:
	tar cfv cabw_enc.tar src/interface.cpp makefile $(SRCDIR)/*.cpp $(SRCDIR)/*.h cadical/*.a cadical/*.hpp