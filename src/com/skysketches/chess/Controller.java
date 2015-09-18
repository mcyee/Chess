/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-11
 * Description: 
 */

package com.skysketches.chess;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;

public class Controller {

	private FileInputStream read;
	private FileOutputStream write;
	
	private String type;
	private String player;
	private int numNodes; // TODO shouldn't this be a field of Tree?
	private Tree root; // TODO what tree is this?
	private List<Tree> nodeList; // TODO what's the point of this 
	// list of all nodes added prior to current
	
	public Controller(FileInputStream r, FileOutputStream w, String t)
	{
		this.read = r;
		this.write = w;
		this.type = t;
	}
	
	/**
	 * TODO i dunno what this does
	 */
	private String inputDescription(Boolean fromFile) {
		String desc;
		String input = "";
		
		// choose input source (file or stdin)
		if (fromFile) {
			BufferedReader br = new BufferedReader(new InputStreamReader(read));
			try{
				input = br.readLine();
			}
			catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else {
			Scanner scan = new Scanner(System.in);
			input = scan.nextLine();
			scan.close();
		}
		
		// TODO what is going on
		int i = 0;
		while (input.charAt(i) != '"') {
			i++;
		}
		i++;
		int start = i;
		int j = 0;
		while (input.charAt(i) != '"') {
			i++;
			j++;
		}
		
		desc = input.substring(start, j);
		return desc;
	}
	
	/**
	 * switchPlayer() changes the player to the opposite colour
	 */
	private void switchPlayer() {
		if (player.equals("black")) {
			this.player = "white";
		}
		else {
			this.player = "black";
		}
	}
	
	/**
	 * buildGame() builds the tree of moves from user input
	 */
	public void buildGame() {
		numNodes = 1;
		Tree node = new Tree('m', "start", "the start node");
		nodeList.add(node);
		root = nodeList.get(0);
		Tree current = root;

		String move;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("Enter the moves and \"q\" when done");
		
		try {
			while (scan.hasNext()) {
				move = scan.next();
				
				// quit
				if (move.equals("q")) break;
				
				// add node to tree
				node = new Tree('m', move, "");
				current.addChild(node);
				nodeList.add(node);
				numNodes++;
				current = node;
			}
			
			this.save();
			System.out.println("The game was saved.");
		}
		finally {
			scan.close();
		}
	}
	
	/**
	 * TODO dunno
	 */
	public void buildList() {
		String nodeName;
		char nodeType;
		String nodeDescription;
		// read in numNodes
		BufferedReader br = new BufferedReader(new InputStreamReader(read));
		try {
			// get node information and add to tree
			String temp = br.readLine();
			numNodes = Integer.parseInt(temp);
			for (int i = 0; i < numNodes; i++) {
				nodeType = (char) br.read();
				nodeName = br.readLine();
				nodeDescription = inputDescription(true);
				this.nodeList.add(new Tree(nodeType, nodeName, nodeDescription));
			}
			
			this.root = nodeList.get(0); // Assume first node is root
			
			Stack<Tree> treeStack = new Stack<Tree>();
			String production;
			int rootID;
			treeStack.push(root);
			while(null != (production = br.readLine())) {
				List<Tree> treeList = new ArrayList<Tree>();
				StringTokenizer st = new StringTokenizer(production);
				rootID = Integer.parseInt(st.nextToken());
				
				// TODO reading in the file is a pita. Please comment this!
				while (st.hasMoreTokens()) {
					treeList.add(nodeList.get(Integer.parseInt(st.nextToken())));
				}
				Tree currentRoot = treeStack.peek();
				while (currentRoot.getID() != rootID) {
					treeStack.pop();
					currentRoot = treeStack.peek();
				}
				treeStack.pop();
				for (int i = treeList.size(); i > 0; i--) {
					treeStack.push(treeList.get(i));
				}
				for (Tree t : treeList) {
					currentRoot.addChild(t);
				}
			}
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * printTree() prints the ...opening tree? TODO
	 */
	public void printTree() {
		this.root.printTreeID(); // TODO why can't you call this directly?
	}
	
	/**
	 * printNodes() prints all the nodes in the tree
	 */
	public void printNodes() {
		System.out.println(this.root.getMove() + " is the root.");
		for (Tree t : nodeList) {
			System.out.println(t.getID() + " " + t.getMove());
		}
	}
	
	/**
	 * TODO
	 */
	public void traverse() {
		this.player = "black";
		
		Boolean saved = true;
		String next;
		char action = '0';
		char ans = 'n';
		String newDescription;
		Tree nextStep;
		Tree newTree;
		Stack<Tree> position = new Stack<Tree>();
		position.push(this.root);
		Tree current = position.peek();

		this.showMessage();
		do {
			Scanner scan = new Scanner(System.in);
			
			current = position.peek();
			System.out.println("~> ");
			action = scan.next(".").charAt(0);
			
			// select game play options
			switch(action) {
				case 'j': // TODO desc of each case
					switchPlayer();
					next = scan.next();
					if (current.isChild(next) == null) {
						newTree = new Tree('o', next, "");
						current.addChild(newTree);
						this.nodeList.add(newTree);
						this.numNodes++;
						saved = false;
						nextStep = newTree;
					}
					else {
						nextStep = current.isChild(next);
					}
					position.push(nextStep);
					System.out.println(player + " plays " + nextStep.getMove());
					break;
				case 'b': // TODO add comment
					if (current.getID() == root.getID()) {
						System.out.println("Already at the root node.");
					}
					else {
						switchPlayer();
						position.pop();
						current = position.peek();
						if (current.getID() != root.getID()) {
							System.out.println(player + " plays " + current.getMove());
						}
						else {
							System.out.println("At the beginning of the game.");
						}
					}
					break;
				case 'd': // TODO add comment
					System.out.println(current.getDescription());
					break;
				case 'a': // TODO add comment
					// TODO why can't these be done on one line?
					newDescription = inputDescription(false);
					newDescription = current.getDescription() + newDescription;
					
					current.setDescription(newDescription);
					break;
				case 'r': // TODO add comment
					newDescription = inputDescription(false);
					newDescription = scan.next(); // TODO overwriting the line above??
					current.setDescription(newDescription);
					break;
				case 'c': // TODO add comment
					current.printChildrenMoves();
					break;
				case 's': // TODO add comment
					System.out.println("This option cannot be undone. "
					    + "Are you sure you want to save? (y/n): ");
					ans = scan.next(".").charAt(0);
					if (ans == 'y') {
						save();
						System.out.println("Saved changes.");
					}
					saved = true; // TODO should be in the if block?? ^
					break;
				case 'q': // TODO add comment
					if (!saved) {
						System.out.println("There are unsaved changes. "
						    + "Are you sure you want to quit without saving? (y/n): ");
						ans = scan.next(".").charAt(0);
						if (ans == 'y') {
							return; // TODO not sure this works in java?
						}
					}
					else {
						return;
					}
					break;
				case 'h':
					System.out.println("a = append a description on the current node.");
					System.out.println("b = go back to the parent node.");
					System.out.println("c = display the \"names\" of all children.");
					System.out.println("d = view the description on the current node.");
					System.out.println("h = display this list of commands");
					System.out.println("j = jump to a node that is a child.");
					System.out.println("r = replace a description on the current node.");
					System.out.println("s = save the currend changes.");
					break;
				default:
					System.out.println("Command not recognized. "
					    + "Type 'h' to see a list of possible commands.");
					break;
			}
		} while (true); // TODO is there a better way to control this loop?
	}
	
	/**
	 * showMessage() prints the initial messages of the given type of book
	 */
	public void showMessage() {
		if (type.equals("gamebook")) {
			System.out.println("You should have recorded the game by now.");
			System.out.println("You are at the start of the game you just recorded.");
			// TODO these messages seem conflicting...
		}
		else { // type.equals("opening")
			System.out.println("This is the chess opening book tool.");
			System.out.println("Type in \"h\" to see command options.");
		}
	}
	
	/**
	 * save() saves the current game to file
	 */
	public void save() {
		try {
			this.root.save(new OutputStreamWriter(this.write));
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
