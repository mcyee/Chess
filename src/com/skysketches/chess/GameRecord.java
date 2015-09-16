/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-15
 * Description: Stores metadata of save games
 */

package com.skysketches.chess;

public class GameRecord {

	private int id;
	private String white;
	private String black;
	private String date;
	
	public GameRecord(int i, String w, String b, String d) {
		this.id = i;
		this.white = w;
		this.black = b;
		this.date = d;
	}
	
	/**
	 * printInfo() prints the values of the GameRecord fields to standard output
	 */
	public void printInfo() {
		System.out.println(id + " " + white + " " + black + " " + date);
	}
	
	/**
	 * getWhite() returns the name of the white player
	 */
	public String getWhite() {
		return this.white;
	}
	
	/**
	 * getBlack() returns the name of the black player
	 */
	public String getBlack() {
		return this.black;
	}
	
	/**
	 * getDate() returns the date of the game
	 */
	public String getDate() {
		return this.date;
	}

}
