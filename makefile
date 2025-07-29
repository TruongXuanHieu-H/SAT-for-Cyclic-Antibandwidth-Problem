OBJDIR=build/obj
SRCDIR=src

OBJECTS= global_data.o cabw_encoder.o version.o usage.o signal_handler.o pid_manager.o graph.o var_handler.o sat_solver_cadical.o instance_encoder.o ladder_encoder.o instance_data.o clause_container.o cabw_instance.o 
OBJS = $(patsubst %.o,$(OBJDIR)/%.o,$(OBJECTS))

FLAGS= -Wall -Werror -Wextra -O3 -DNDEBUG
IGNORE_ASSERTVARS= -Wno-unused-but-set-variable
STANDARD= -std=c++23

CADICAL_INC=./solver/cadical/
CADICAL_LIB_DIR=./solver/cadical/
CADICAL_LIB=-lcadical

all : $(OBJDIR)/interface.o
	g++ $(FLAGS) $(OBJDIR)/interface.o $(OBJS) -L$(CADICAL_LIB_DIR) $(CADICAL_LIB) -o build/cabw_enc

$(OBJDIR)/interface.o : $(SRCDIR)/interface.cpp $(OBJS) $(SRCDIR)/global_data.h $(SRCDIR)/cabw_encoder.h $(SRCDIR)/utils/signal_handler.h $(SRCDIR)/utils/usage.h $(SRCDIR)/utils/version.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/enum/symmetry_breaking_type.h $(SRCDIR)/enum/search_strategy.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/global_data.o : $(SRCDIR)/global_data.cpp $(SRCDIR)/global_data.h $(SRCDIR)/graph/graph.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/enum/symmetry_breaking_type.h $(SRCDIR)/enum/search_strategy.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/cabw_encoder.o : $(SRCDIR)/cabw_encoder.cpp $(SRCDIR)/cabw_encoder.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/enum/search_strategy.h $(SRCDIR)/graph/graph.h $(SRCDIR)/global_data.h $(SRCDIR)/encoders/cabw_instance.h $(SRCDIR)/utils/pid_manager.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/version.o : $(SRCDIR)/utils/version.cpp $(SRCDIR)/utils/version.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/usage.o : $(SRCDIR)/utils/usage.cpp $(SRCDIR)/utils/usage.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/signal_handler.o : $(SRCDIR)/utils/signal_handler.cpp $(SRCDIR)/utils/signal_handler.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/pid_manager.o: $(SRCDIR)/utils/pid_manager.cpp $(SRCDIR)/utils/pid_manager.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/graph.o : $(SRCDIR)/graph/graph.cpp $(SRCDIR)/graph/graph.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/var_handler.o : $(SRCDIR)/encoders/var_handler.cpp $(SRCDIR)/encoders/var_handler.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/sat_solver_cadical.o : $(SRCDIR)/encoders/sat_solver_cadical.cpp $(SRCDIR)/encoders/sat_solver_cadical.h $(SRCDIR)/encoders/instance_data.h $(SRCDIR)/global_data.h
	g++ $(FLAGS) $(STANDARD) -I$(CADICAL_INC) -c $< -o $@

$(OBJDIR)/instance_encoder.o : $(SRCDIR)/encoders/instance_encoder.cpp $(SRCDIR)/encoders/instance_encoder.h $(SRCDIR)/global_data.h $(SRCDIR)/encoders/instance_data.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/ladder_encoder.o : $(SRCDIR)/encoders/ladder_encoder.cpp $(SRCDIR)/encoders/ladder_encoder.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/instance_data.o : $(SRCDIR)/encoders/instance_data.cpp $(SRCDIR)/encoders/instance_data.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/clause_container.o : $(SRCDIR)/encoders/clause_container.cpp $(SRCDIR)/encoders/clause_container.h $(SRCDIR)/encoders/var_handler.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

$(OBJDIR)/cabw_instance.o : $(SRCDIR)/encoders/cabw_instance.cpp $(SRCDIR)/encoders/cabw_instance.h $(SRCDIR)/graph/graph.h $(SRCDIR)/enum/encode_type.h $(SRCDIR)/encoders/instance_encoder.h $(SRCDIR)/encoders/clause_container.h $(SRCDIR)/encoders/sat_solver.h
	g++ $(FLAGS) $(STANDARD) -c $< -o $@

#.PHONY : clean
clean:
	rm -f *.a $(OBJDIR)/*.o *~ *.out  $(OBJDIR)/cabw_enc

tar:
	tar cfv cabw_enc.tar src/interface.cpp makefile $(SRCDIR)/*.cpp $(SRCDIR)/*.h cadical/*.a cadical/*.hpp