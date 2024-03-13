CC := g++
LDLIBS := -pthread
CPPFLAGS := -g -I. -Ithreads -Wall

# Listado de archivos fuente en el proyecto
SRCS := $(wildcard *.cpp) $(wildcard threads/*.cpp) $(wildcard resources/*.cpp)

# Objetos generados a partir de los archivos fuente
OBJS := $(SRCS:.cpp=.o)

# Nombre del ejecutable
EXEC := exe

all: $(EXEC)

# Regla de compilación principal
$(EXEC): $(OBJS)
	$(CC) $(LDLIBS) -o $(EXEC) $(OBJS)

# Regla de compilación para archivos fuente individuales
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf *~ core $(EXEC) $(OBJS)
