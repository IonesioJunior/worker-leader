INCLUDE_PATH= -I./src -I/usr/local/include/librdkafka
LIBS= -lcurl -lrdkafka
BIN_PATH= ./bin

all: worker-manager

run: worker-manager
	./worker-manager

bin_folder:
	mkdir bin

%.o : %.cpp %.hpp
	g++ -Wall -g -c $< -o $@ $(INCLUDE_PATH)

worker-manager: ./workers/worker.o ./dataset_handling/dataset_handler.o
	g++ $^ main.cpp -o $@ -I $(INCLUDE_PATH) $(LIBS)  -larmadillo -std=c++17

clean:
	rm ./workers/*.o
	rm worker-manager
