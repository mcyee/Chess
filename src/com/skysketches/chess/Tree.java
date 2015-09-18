/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-12
 * Description: Stores opening moves
 */

package com.skysketches.chess;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.List;

public class Tree {

	private static int counter = 0;
	
	private int id;
	private char type; // 'm" for "main, 'o' for "opening"
	private String move;
	private String description;
	private List<Tree> children;
	
	public Tree(char t, String m, String d)
	{
		this.id = Tree.counter;
		this.type = t;
		this.move = m;
		this.description = d;
		
		Tree.counter++;
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
	 * printChildrenMoves() prints the children moves
	 */
	public void printChildrenMoves() {
		for (Tree t : children) {
			System.out.print(t.getMove() + " ");
		}
		System.out.println();
	}
	/**
	 * printTreeID() prints the ID's of all the nodes in the tree to standard output
	 */
	public void printTreeID() {
		System.out.println(id);
		for (Tree t : children) {
			t.printTreeID();
		}
	}

	/**
	 * save() saves the Tree to file
	 * @throws IOException 
	 */
	public void save(Writer writer) throws IOException {
		BufferedWriter bw = new BufferedWriter(writer);
		// save number of nodes and its fields
		int numNodes = Tree.counter + 1;
		bw.write(numNodes);
		bw.newLine();
		bw.write(this.getType() + " " + this.getMove() + " \""
		    + this.getDescription() + "\"");
		bw.newLine();
		// recursively save children
		for (Tree t : children) {
			t.save(bw);
		}
		// TODO what is going on, also children are private so you can't
		// access them outside of the class
//		Stack<Tree> treeStack = new Stack<Tree>();
//		treeStack.push(root);
//		Tree current;
//		while (!treeStack.isEmpty()) {
//			current = treeStack.pop();
//			if (current.getChildrenSize() > 0) {
//				writer.write(current.getID());
//				writer.write(" ");
//				for () {
//					
//				}
//			}
//		}
	}
}
