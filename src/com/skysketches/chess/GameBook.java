/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: Sep 14, 2015
 * Description: Maintains list of saved games
 */

package com.skysketches.chess;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

public class GameBook {

	private int numGames;
	private String gamesFile;
	private List<GameRecord> games;
	
	public GameBook(String gf) {
		this.gamesFile = gf;
		
		// read game data from file
		BufferedReader br = new BufferedReader(new InputStreamReader
		    (new FileInputStream(this.gamesFile)));
		
		this.numGames = br.read();
		
		String input = br.readLine(); // TODO isn't being used?
		int id;
		String black;
		String white;
		String date;
		for (int i = 0; i < numGames; i++) {
			input = br.readLine();
			StringTokenizer st = new StringTokenizer(input);
			id = Integer.parseInt(st.nextToken());
			white = st.nextToken();
			black = st.nextToken();
			date = st.nextToken();
			GameRecord record = new GameRecord(id, white, black, date);
			games.add(record);
		}
	}
	
	/**
	 * displayGames() displays the information for all saved games
	 */
	public void displayGames() {
		for (GameRecord g : games) {
			g.printInfo();
		}
	}
	
	/**
	 * 
	 */
	public void save() {
		BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
		    new FileOutputStream(gamesFile)));
		int j = 1;
		writer.write(numGames);
		writer.newLine();
		for (GameRecord gr : games) {
			writer.write(j);
			writer.write(" ");
			writer.write(gr.getWhite());
			writer.write(" ");
			writer.write(gr.getBlack());
			writer.write(" ");
			writer.write(gr.getDate());
			j++;
		}
	}
	
	/**
	 * 
	 */
	public void run() {
		System.out.println("Displaying all current games. " +
		    "Type in \"help\" for more options.");
		System.out.println("~> ");
		String input;
		
		Scanner scan = new Scanner(System.in);
		// reads in user command
		while(scan.hasNextLine()) {
			input = scan.nextLine();
			StringTokenizer st = new StringTokenizer(input);
			String command = st.nextToken();
			
			if (command.equals("q") || command.equals("quit")) {
				break;
			}
			else if (command.equals("open")) {
				String file = st.nextToken();
				FileInputStream fistream = new FileInputStream(file);
				FileOutputStream fostream = new FileOutputStream(file);
				Controller controller = new Controller(fistream, fostream, "gamebook");
				controller.buildList();
				controller.traverse();
			}
			// initialises players and played moves
			else if (command.equals("new")) {
				String white = st.nextToken();
				String black = st.nextToken();
				String date = st.nextToken();
				this.numGames++;
				games.add(new GameRecord(numGames, white, black, date));
				
				String saveFile = numGames + ".txt";
				// TODO stuff flush?
				FileInputStream fistream = new FileInputStream(saveFile);
				FileOutputStream fostream = new FileOutputStream(saveFile);
				Controller controller = new Controller(fistream, fostream, "gamebook");
				controller.buildGame();
				controller.traverse();
				// TODO close file?
				save();
			}
			else if (command.equals("help")) {
				System.out.println("quit, open, new, help, display");
			}
			else if (command.equals("display")) {
				displayGames();
			}
			else {
				System.out.println("Unrecognized command.");
			}
			System.out.println("~> ");
		}
	}
	
	/**
	 * TODO missing?
	 */
	public createGame(String, String, String) {
		
	}

}
