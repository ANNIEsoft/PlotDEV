RootInclude = -I $(shell root-config --incdir)
RootLib = $(shell root-config --libs)
CXX = $(shell root-config --cxx)

all: 

	$(CXX) -g src/*.cpp UserPlots/*.cpp -o PlotTest -I include -I UserPlots $(RootInclude) $(RootLib)

clean:

	rm PlotTest
