CC := g++

CC_FLAGS :=

MINPATH_SOURCES := ./Sources/Minpath
MINPATH_OBJECTS := ./Objects/Minpath

MST_SOURCES := ./Sources/MST
MST_OBJECTS := ./Objects/MST

DIGRAPHGEN_SOURCES := ./Sources/Digraphgen

GRAPHGEN_SOURCES := ./Sources/Graphgen

COMMON_SOURCES := ./Sources/Common
COMMON_OBJECTS := ./Objects/Common


all: mst minpath digraphgen graphgen 

mst: $(COMMON_OBJECTS)/Exception.o \
     $(MST_OBJECTS)/Edge.o \
     $(MST_OBJECTS)/Forest.o \
     $(MST_OBJECTS)/Graph.o \
     $(MST_OBJECTS)/MST_Algorithms.o \
     $(MST_OBJECTS)/MST_Utils.o \
     $(MST_OBJECTS)/MST_Main.o 
	$(CC) $(CC_FLAGS) -o $@ $(MST_OBJECTS)/*.o $(COMMON_OBJECTS)/*.o

minpath: $(COMMON_OBJECTS)/Exception.o \
	      $(MINPATH_OBJECTS)/Digraph.o \
	      $(MINPATH_OBJECTS)/DigraphL.o \
	      $(MINPATH_OBJECTS)/DistanceTable.o \
	      $(MINPATH_OBJECTS)/MinpathMain.o \
	      $(MINPATH_OBJECTS)/MinpathConfig.o \
	      $(MINPATH_OBJECTS)/MinpathUtils.o \
	      $(MINPATH_OBJECTS)/PriorityQueue.o 
	$(CC) $(CC_FLAGS) -o $@ $(MINPATH_OBJECTS)/*.o $(COMMON_OBJECTS)/*.o

digraphgen: $(DIGRAPHGEN_SOURCES)/Digraphgen.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

graphgen: $(GRAPHGEN_SOURCES)/Graphgen.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

$(COMMON_OBJECTS)/%.o: $(COMMON_SOURCES)/%.cpp
	$(CC) $(CC_FLAGS) -I$(COMMON_SOURCES)  -c -o $@ $<

$(MST_OBJECTS)/%.o: $(MST_SOURCES)/%.cpp
	$(CC) $(CC_FLAGS) -I$(MST_SOURCES) -I$(COMMON_SOURCES) -c -o $@ $<

$(MINPATH_OBJECTS)/%.o: $(MINPATH_SOURCES)/%.cpp
	$(CC) $(CC_FLAGS) -I$(MINPATH_SOURCES) -I$(COMMON_SOURCES) -c -o $@ $<

clean:
	-rm -f mst minpath digraphgen graphgen core $(MST_OBJECTS)/*.o $(MINPATH_OBJECTS)/*.o $(COMMON_OBJECTS)/*.o

