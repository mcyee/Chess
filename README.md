## Chess

This is a standalone application in which you can play a game of chess as well as do the following:
	-Develop openings with annotations. 
	-Record chess games for analysis. 
	-Use the computer to analyze recorded chess games.

The current feature in development is:
	-Develop openings with annotations. 
	
What has been currently implemented is: 
	-A base working tree style structure meant to hold the different opening moves. 

What needs to be implemented for this feature is:
	-A system that takes in the next move the player wants to do and then create a unique id for the move so that the tree is well structured without duplicate nodes. (Ie, it's possible that for two different openings, the same side plays the same move on the same turn but with different preceding moves. Clearly the two moves are in different contexts and hence need unique id's to differentiate them.)

Note: This project was intended to be done in Java, but will likely be later ported from the source language C++ to Java. 
Note2: The current system used to implement the opening database is to load the entire tree into RAM from a file, make necessary changes in RAM through the course of the program and then save everything whenever the user desires so. This should be fine for small opening books but is likely a bad idea for long term usage. We may want to use sqlite3 in the future to hold the information, especially when concerned with creating an analyzed games archive. 
