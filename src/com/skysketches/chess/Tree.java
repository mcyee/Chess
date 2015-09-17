/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-12
 * Description: Stores opening moves
 */

package com.skysketches.chess;

import java.util.List;

public class Tree {

	private static int counter = 0;
	
	private int id; // TODO implement a static counter and fix controller instances
	private char type; // 'm" for "main, 'o' for "opening"
	private String move;
	private String description;
	private List<Tree> children;
	
	public Tree(char t, String m, String d)
	{
		this.id = counter;
		this.type = t;
		this.move = m;
		this.description = d;
		
		this.counter++;
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
	 * getChildrenSize() returns the number of children
	 */
	public int getChildrenSize() {
		return this.children.size();
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
