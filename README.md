# PlotDEV

This is a package is intended for making plots for the online DAQ system. It contains a template and example and a script to test your plots with a simplified output. Any plot clases you make and wish to include in the DAQ please send to b.richards@qmul.ac.uk. I will then check the code and test it before deploying it on the DAQ.

Please note: That all plotting scripts will be run periodically on the DAQ (e.g. every X number of Card reads/events). This frequency will be dynamically changeable but will also be based on how long each takes to run. Remember data can come in at 0.5Hz so if your plotting class takes a long time to execute it will have to be run less frequently. 


#Building

To build the PlotTest executable just do the following:

1) Change the Root libs and include path in the makefile

2) make clean

3) make


# Creating your own plots

Creating your own plot or collection of plots is simple you just need to follow the steps below:

1) Make a copy of the Template.cpp and Template.h in UserPlots, naming it something relevent.
   e.g. cp UserPlots/Template.cpp UserPlots/MyEventDisplay.cpp
   	cp UserPlots/Template.h UserPlots/MyEventDisplay.h


2) Edit the Initialise Execute and Finalise Funcitons in the new files


Descriptions of these functions are below:

#Initialise
 
bool Initialise(Store* variables, std::map<int, std::map<int,PMT> >* PMInfo, std::vector<std::string>* SlackErrors);

Use this to load any dynamic variables from the variables store (variables), initialise an member variables, create a canvas and define and plots that span multiple events.

Arguments:

1) variables is a dnamic variable store thats templated. you can retreive any dynamic variables using.

	  variables->Get("variablename",var1);

variable names cannot contain spaces.

2) PMTInfo is a nested map containing all PMT locations and pedistal values. The maps are indexed by card number and channel in that order. the variables contained inside can be found in the PMT struct in inlcude/Plot.h. 

e.g.	  (*PMTInfo)[CardID][Channel].gx
	  (*PMTInfo)[CardID][Channel].gy
	  (*PMTInfo)[CardID][Channel].PEDmean 

3) SlackErrors is a vector of strings which allows users to pass error messages and warnings to shiters via slack. Usage is simple:

   SlackErrors.push_back("MYPlot: error message text");

#Execute

  bool Execute(std::vector<CardData*> *data);
  
The Execute function is run on every X card reads and is where data for that event is read in for you to fill and make a plot of.

Aguments:

1) data is a vector of CardData pointers. This is an object which contains the raw information form the cards when read out. note it is in ADC units not pedistal subtracted and the ADC data is stacked back to back by channel and then interleaved in each channel in the following patter 13245768...
A full list of vaiables can be found in include/CardData.h

#Finalise 

  bool Finalise();

the Finalise function should be used to clean up all data delete histograms canvases and internal variables. This is only run at the end of a subrun or run and the idea is to completly remove all memory usage of the class so Initialise could be called again and everything restarted.



#Testing

the PlotTest executable provides a test stand for your plotting class. It can provide a set of simulated card outputs and test input arguments. If you need specific functionality or data to test your plots feel free to expand what is currently there. currently the entire program is in src/main.cpp

in order to add your newply created plot to this executable please follow the following steps:

1) Add your plot to the plots vector

e.g 

 //////////////////////////////////////////////////// Plots vector ////////////////////////////////////////////////////////
  std::vector<Plot*> plots;


  Plot *mytest = new ExampleEventDisplay();
  plots.push_back(mytest);

  Plot *yourplot = new YourNewPlotClass();
  plots.push_back(yourplot);

  // add your own plots by pushing them back here
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


2) Add any dynamic variables you need to read form a config file using the Store (vars.Set(....))

e.g.

/////////////////// Dynamic Input Variables //////////////////////////////////////////////////////////////////////////////////////////
  //// Use the Store to pass any variables to your monitoring plot that you want dynamically set from the configuration file ///////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Store vars;
  vars.Set("OutputPath","./");
  vars.Set("MyNewVar1",1.45);
  vars.Set("MyNewVar2","Hello World");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


# Further info

Further information or clarification/help can be found on the ANNIE DAQ slack channel or by emailing b.richards@qmul.ac.uk 