RootInclude=  -I ../../ToolDAQ/root/include
RootLib=   -L ../../ToolDAQ/root/lib  -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lMathCore -lThread -pthread -lm -ldl -rdynamic -pthread -m64


all: 

	g++ -g src/*.cpp UserPlots/*.cpp -o PlotTest -I include -I UserPlots $(RootInclude) $(RootLib)

clean:

	rm PlotTest