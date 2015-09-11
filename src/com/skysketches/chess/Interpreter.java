/**
 * Project: Chess
 * File: Interpreter.java
 *
 * Author: Ming-Cee Yee
 *
 * Date Created: 2015-09-11
 * Description: Launches the Chess game
 */
package com.skysketches.chess;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.StringTokenizer;

class Interpreter {
	
	private String openingBook;
	private String gameBook;

	public Interpreter() {
		this.openingBook = "prepfile.txt";
		this.gameBook = "games.txt";
	}

	/**
	 * init() initialises (launches) the game
	 */
	public void init() {
		System.out.println("Welcome to this chess program!");
		
		Scanner scan = new Scanner(System.in);
		
		 // accept a text command
		try {
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
					
					Scanner scanBook = new Scanner(new BufferedReader(new FileReader(openingBook)));
					Scanner scanBook2 = new Scanner(new BufferedReader(new FileReader(openingBook))); // TODO why are there 2?
					Controller controller = new Controller(scanBook, scanBook2, "opening");
					
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
					// TODO implement
					System.out.println("Done playing.");
				}
				else {
					System.out.println("Command not recognized. Please type " +
							"\"help\" to see possible commands.");
				}
			}
			
			System.out.println("Exited game.");
		} catch (FileNotFoundException e) {
	        // TODO Auto-generated catch block
	        e.printStackTrace();
        }
		finally {
			scan.close();
		}
	}
	
	public void help() {
		System.out.println("These are the current possible commands:");
		System.out.println("\"openings\": Use the opening book tool.");
		System.out.println("\"gamebook\": Use the gamebook tool.");
		System.out.println("\"play\": Play a game of chess.");
	}
	
	public void help(String s) {
		// TODO command descriptions
	}
}
