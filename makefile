SRC1 := gatorTaxi.cpp
SRC2 := RBT.cpp
SRC3 := Min_Heap.cpp
EXE := gatorTaxi
all:
	@g++ -o $(EXE) $(SRC1) $(SRC2) $(SRC3)

clean:
	rm -rf $(EXE)