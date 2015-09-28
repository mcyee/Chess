/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-11
 * Description: Launches the Chess game
 */

package com.skysketches.chess;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.Scanner;
import java.util.StringTokenizer;

class Interpreter {
	
	private String openingBook; // TODO what are these		two variables that hold the names of the files that hold the openingbook and list of games. /what is an opening book
	private String gameBook; // name of the list of saved games TODO is there a way to make this into a reference instead of a string?

	public Interpreter() {
		this.openingBook = "prepfile.txt";
		this.gameBook = "games.txt";
	}

	/**
	 * init() initialises (launches) the game and provides main menu options
	 */
	public void init() {
		System.out.println("Welcome to this chess program!");
		try (Scanner scan = new Scanner(System.in)) {
		
			// accept a text command
			while (scan.hasNextLine()) {
				StringTokenizer line = new StringTokenizer(scan.nextLine());
				String command = line.nextToken();
				
				System.out.println("Type \"help\" for general instructions or " +
						"\"help <cmd>\" for help with a specific command.");
				System.out.println("~> ");
				
				// TODO catch invalid number of arguments
				if (command.equals("q") || command.equals("quit")) {
					System.out.println("Exiting game.");
					break;
				}
				else if (command.equals("help")) {
					if (line.hasMoreTokens()) {
						this.help(line.nextToken());
					}
					else {
						this.help();
					}
				}
				else if (command.equals("openings")) {
					System.out.println("Running the openings tool.");
					
					FileInputStream scanBookIn = new FileInputStream(openingBook);
					FileOutputStream scanBookOut = new FileOutputStream(openingBook);
					Controller controller = new Controller(scanBookIn, scanBookOut, "opening");
					
					controller.buildList();
					controller.traverse();
					System.out.println("Done running the openings tool.");
				}
				else if (command.equals("gamebook")) {
					System.out.println("Running the gamebook tool.");
					GameBook gb = new GameBook(gameBook);
					gb.run();
					System.out.println("Done running the gamebook tool.");
				}
				else if (command.equals("play")) {
					System.out.println("Initiating a game.");
					// TODO implement							// Yeah, this is something that has yet to be implemented, and is huge. 
					System.out.println("Done playing.");
				}
				else {
					System.out.println("Command not recognized. Please type " +
							"\"help\" to see possible commands.");
				}
			}
			
			System.out.println("Exited game.");
		}
		catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * help() lists all available commands
	 */
	public void help() {
		System.out.println("These are the current possible commands:");
		System.out.println("\"openings\": Use the opening book tool.");
		System.out.println("\"gamebook\": Use the gamebook tool.");
		System.out.println("\"play\": Play a game of chess.");
	}
	
	/**
	 * help(s) displays the description for the command s
	 */
	public void help(String s) {
		// TODO command descriptions
	}
}
