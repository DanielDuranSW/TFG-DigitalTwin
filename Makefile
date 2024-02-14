CC := g++
LDLIBS := -pthread
CPPFLAGS := -g -I. -Ithreads -Wall

OBJS := main.o dma.o threads/FSR_Acquisition.o threads/IMU_Acquisition.o threads/RAM_Operation.o threads/BLE_Stack_Operation.o threads/Energy_Saving.o threads/Custom_Event_Handler.o

# Nombre del ejecutable
EXEC := exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDLIBS) -o $(EXEC) $(OBJS)

main.o: dma.h threads/FSR_Acquisition.h threads/IMU_Acquisition.h threads/RAM_Operation.h threads/BLE_Stack_Operation.h threads/Energy_Saving.h threads/Custom_Event_Handler.h
	$(CC) $(CPPFLAGS) -c main.cpp

dma.o: dma.h
	$(CC) $(CPPFLAGS) -c dma.cpp

threads/FSR_Acquisition.o: threads/FSR_Acquisition.h
	$(CC) $(CPPFLAGS) -c threads/FSR_Acquisition.cpp -o threads/FSR_Acquisition.o

threads/IMU_Acquisition.o: threads/IMU_Acquisition.h
	$(CC) $(CPPFLAGS) -c threads/IMU_Acquisition.cpp -o threads/IMU_Acquisition.o

threads/RAM_Operation.o: threads/RAM_Operation.h
	$(CC) $(CPPFLAGS) -c threads/RAM_Operation.cpp -o threads/RAM_Operation.o

threads/BLE_Stack_Operation.o: threads/BLE_Stack_Operation.h
	$(CC) $(CPPFLAGS) -c threads/BLE_Stack_Operation.cpp -o threads/BLE_Stack_Operation.o

threads/Energy_Saving.o: threads/Energy_Saving.h
	$(CC) $(CPPFLAGS) -c threads/Energy_Saving.cpp -o threads/Energy_Saving.o

threads/Custom_Event_Handler.o: threads/Custom_Event_Handler.h
	$(CC) $(CPPFLAGS) -c threads/Custom_Event_Handler.cpp -o threads/Custom_Event_Handler.o

clean:
	rm -rf *~ core $(EXEC) $(OBJS)
