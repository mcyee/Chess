/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: Sep 14, 2015
 * Description: Maintains list of saved games
 */

package com.skysketches.chess;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.List;
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
	 * 
	 */
	public void displayGames() {
		
	}
	
	/**
	 * 
	 */
	public void run() {
		
	}
	
	/**
	 * 
	 */
	public void save() {
		
	}
	
	/**
	 * 
	 */
	public createGame(String, String, String) {
		
	}

}
