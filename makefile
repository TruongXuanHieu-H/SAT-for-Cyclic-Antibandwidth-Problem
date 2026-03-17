# ================================
# Project directories
# ================================
SRCDIR  := src
OBJDIR  := build/obj
BINDIR  := build

TARGET  := $(BINDIR)/cabw_enc

# ================================
# Compiler
# ================================
CXX       := g++
STANDARD  := -std=c++23

# ================================
# Compiler flags
# ================================
IGNORE_ASSERTVARS := -Wno-unused-but-set-variable
CXXFLAGS := -Wall -Wextra -Werror -O3 -DNDEBUG $(STANDARD) -Wno-literal-suffix

# ================================
# CaDiCaL
# ================================
CADICAL_FOLDER  ?= solver/cadical
CADICAL_INC     := ./$(CADICAL_FOLDER)
CADICAL_LIB_DIR := ./$(CADICAL_FOLDER)
CADICAL_LIB     := -lcadical

# ================================
# Minisat
# ================================
MINISAT_FOLDER  ?= src_solver/minisat
MINISAT_INC     := ./$(MINISAT_FOLDER)
MINISAT_SRC     := $(shell find $(MINISAT_FOLDER) -name "*.cc" ! -name "Main.cc")

INCLUDES := -I$(CADICAL_INC) -I$(MINISAT_INC)

# ================================
# Source files
# ================================
SOURCES := \
	cabw_encoder.cpp \
	global_data.cpp \
	interface.cpp \
	encoders/cabw_instance.cpp \
	encoders/clause_container.cpp \
	encoders/instance_data.cpp \
	encoders/instance_encoder.cpp \
	encoders/ladder_encoder.cpp \
	encoders/sat_solver_cadical.cpp \
	encoders/sat_solver_minisat.cpp \
	encoders/var_handler.cpp \
	graph/graph.cpp \
	searchers/cabw_searcher.cpp \
	searchers/cabw_searcher_binary_bfs.cpp \
	searchers/cabw_searcher_binary_from_lb.cpp \
	searchers/cabw_searcher_binary_from_ub.cpp \
	searchers/cabw_searcher_iterate_from_lb.cpp \
	searchers/cabw_searcher_step_from_lb.cpp \
	utils/pid_manager.cpp \
	utils/signal_handler.cpp \
	utils/usage.cpp \
	utils/version.cpp

# ================================
# Object files
# ================================
OBJECTS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# ================================
# Default target
# ================================
.PHONY: all
all: $(TARGET)

# ================================
# Link
# ================================
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -w $(MINISAT_SRC) -L$(CADICAL_LIB_DIR) $(CADICAL_LIB) -o $@

# ================================
# Compile rules
# ================================
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ================================
# Special flags (optional)
# ================================
# $(OBJDIR)/encoders/xxx.o: CXXFLAGS += $(IGNORE_ASSERTVARS)

# ================================
# Clean
# ================================
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET) *.a *~ *.out

# ================================
# Archive
# ================================
.PHONY: tar
tar:
	tar cfv cabw_enc.tar \
		$(SRCDIR) \
		makefile \
		$(CADICAL_LIB_DIR)/*.a \
		$(CADICAL_LIB_DIR)/*.hpp