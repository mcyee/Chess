/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-12
 * Description: Stores opening moves
 */

package com.skysketches.chess;

import java.util.List;

public class Tree {

	private int id;
	private char type; // TODO could be boolean? // 'm" for "main, 'o' for "opening"
	private String move;
	private String description;
	private List<Tree> children;
	
	public Tree(int id, char t, String m, String d)
	{
		this.id = id;
		this.type = t;
		this.move = m;
		this.description = d;
	}
	
	/**
	 * getID() returns the ID 
	 */
	public int getID() {
		return this.id;
	}
	
	/**
	 * getMove() returns the name of the move
	 */
	public String getMove() {
		return this.move;
	}	

	/**
	 * getType() returns the type 'm' or 'o'
	 */
	public char getType() {
		return this.type;
	}
	
	/**
	 * getDescription() returns the description of the move
	 */
	public String getDescription() {
		return this.description;
	}
	
	/**
	 * setDescription(s) changes the description to s
	 */
	public void setDescription(String s) {
		this.description = s;
	}

	/**
	 * addChild(tree) adds tree to the list of children
	 */
	public void addChild(Tree tree) {
		this.children.add(tree);
	}
	
	/**
	 * isChild(s) returns the child s if s is a child of the current node
	 */
	public Tree isChild(String s) {
		for (Tree t : children) {
			if (t.getMove().equals(s)) {
				return t;
			}
		}
		return null;
	}
	
	/**
	 * printTree() prints the tree to standard output
	 */
	public void printTree() {
		System.out.println(id);
		for (Tree t : children) {
			t.printTree();
		}
	}

}
