# Mandelprison - Free Benoit!
### A text adventure in style of the 80's game Thor - The trilogy for the  Schneider CPC464.


### The Story:

Sadly, Benoit Mandelbrot has been captured by the villain Fraktalo  and is now held prisoner in a cell in the hyperbolic center of the  main cardioid. Your task as the hero Taylor is to free Benoit and prevent fractal mathematics from falling into a dark age - a century without progress. 


### The Game:

You start in a hyperbolic component of the Mandelbrot set and have  to find a way to the main cardioid. 

Three types of movement are possible for you.

A component consists of joined rooms with open doors which you can  simply traverse.

At the boundary of the component there are occasionally locked  parabolic doors. They open after the correct PIN has been entered and you traverse to the adjacent component. The PIN is the periodicity of the current component which you have to figure out beforehand, simply guess by trial-and-error or use an educated guess if you have discovered where in the Mandelbrot set you currently are located. Hidden in some of the rooms of a component are clues to 
that periodicity, sometimes a simple note on the floor, sometimes hidden near an object, sometimes locked in a case where you have to 
answer a question about fractals to open it, sometimes multiple choice. In the hyperbolic center of some components there is a transmitter 
that could - if active - teleport you to another component of the same periodicity, whether you already know it or not, but you do not 
necessarily land in its hyperbolic center. 

Hidden in the starting component there are pieces of a device, the multiplier detector. After assembly (takes place automatically by 
just grabbing the parts once you have found them) it gives a precalculated multiplier of the current room even if you do not know the periodicity of the 
component yet, and might help find the center or the boundary more quickly.


### The Goal:

Once you have found Benoit's cell, you have to answer a multiple choice question to open the door. But beware! You only have a limited number 
of trials till an alarm goes off and you are teleported back to your game start but retain all your knowledge or device parts. If you 
answer correctly, your task has been completed and mathematics is save!


### Example Commands:

"go north" (or shortly just "n")<br>
"look behind mirror"<br>
"take part"<br>
"open case"<br>
"use transmitter"<br>
"save", "load" - store/read game state

The command parser is very primitive. Commands are simply understood by keywords, usually - but not always - prepositions are not 
important ("read note", "read around note", "read note backwards" all does the same  - telling you what's  written on it)

There is an "undocumented" magic command, a hex,  that starts an oracle which reveals the right answer to all following questions
once invoked.


### The Command Window:

The game is a pure text adventure in an endless paper output screen rolling downwards. Responses to commands are written directly under 
the command you entered as well as their consequences in the new command window. 

At the beginning you choose between three starting levels , roughly correlated to difficulty of the path to the main cardioid: easy, 
intermediate, difficult, and the language used: English or (mostly) German.


### Underlying design

Everything has to be imagined by your mind. But one might draw a map on a sheet of paper (that's how I checked the rescue routes). Knowledge 
about the distribution of multiplier values in a component, what might lie behind a parabolic door could help you figure out, where 
in the Mandelbrot set you are and what comes in the adjacent regions. 

The questions to be answered are related to Benoit Mandelbrot or might refer to fractal mathematics in general. Solutions are usually 
from articles, maxima scripts incorporated into the source code, or external programs to calculate respective values.

The Game is deterministic. Questions in specific rooms are always the same, the clues are hidden in the same rooms, as well as the 
device parts in the starting component. The teleport-order is predetermined and fixed. Not all center transmitters are useable. 
Multipliers are in every program run the same. The number of rooms in a component is not indicative of its size nor do the rooms
cover the entire component. The starting component usually has a larger number of rooms to store all the device parts. 

