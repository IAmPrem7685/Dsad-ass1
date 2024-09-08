# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Target executable
TARGET = Executable

# Source files, Object files, and Object directory
SRCS = $(wildcard src/*.cpp) main.cpp
OBJDIR = obj
OBJS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(filter src/%.cpp,$(SRCS))) $(OBJDIR)/main.o

# Default target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file into a .o file for src folder files
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile main.cpp in the root folder
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up the build (remove object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJDIR)

# Run the executable
run:
	./$(TARGET)
