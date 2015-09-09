## Chess

This is a standalone application in which you can play a game of chess as well as do the following:
	-Develop openings with annotations. 
	-Record chess games for analysis. 
	-Use the computer to analyze recorded chess games.

The current feature in development is:
	-Record chess games for analysis.
	
What has been currently implemented is:
	-The main framework that will help us navigate through the played game. (It's basically the same opening tree structure). 

What needs to be implemented for this feature is:
	-The feature that lets us save the game information in terms of who was white, black, when the game was played, etc. 
	-(Basically the part that differentiates between a game file and opening file, etc)

Note: This project was intended to be done in Java, but will likely be later ported from the source language C++ to Java. 
Note2: The current system used to implement the opening database is to load the entire tree into RAM from a file, make necessary changes in RAM through the course of the program and then save everything whenever the user desires so. This should be fine for small opening books but is likely a bad idea for long term usage. We may want to use sqlite3 in the future to hold the information, especially when concerned with creating an analyzed games archive. In the case that we are loading games that have been played it will obviously be no problem in loading it into RAM since games (even heavily analyzed ones) will not be as large as an opening book.


