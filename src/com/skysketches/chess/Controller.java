/**
 * Project: Chess
 * Author: Ming-Cee Yee
 * Created: 2015-09-11
 * Description: 
 */

package com.skysketches.chess;

import java.io.BufferedReader;
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
	private int numNodes; // TODO shouldn't this be a field of Tree?  ANS: This is used when assigning id's to new nodes that are created. 
	private Tree root; // TODO what tree is this?	ANS: The Controller is a large interface for dealing with the tree. It holds the tree by the root. 
	private List<Tree> nodeList; // TODO what's the point of this 	ANS: A hacky "map" because the index maps to the pointer of the node. We use these 
								// indices in order to properly create the tree. If you look at the tree configuration files the indices are used to show 
								// which nodes are children to which other nodes in the productions similar to: 
								// https://www.student.cs.uwaterloo.ca/~cs241/wlp4/WLP4.html   (the context free syntax productions) 
	// list of all nodes added prior to current
	
	public Controller(FileInputStream r, FileOutputStream w, String t)
	{
		this.read = r;
		this.write = w;
		this.type = t;
	}
	
	/**
	 * TODO i dunno what this does	// This is a function used when taking input from either the user or a file. In the file, each node has a description, 
	 * 								// and so we need to change the input stream. On the other hand if the user is providing a description for the node while
	 * 								// working with the program, the description is read in exactly the same way and so that is what this fucntion is for. 
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
			try (Scanner scan = new Scanner(System.in)) {
				input = scan.nextLine();
			}
		}
		
		// TODO what is going on			// So the way the description is read in is kind of like how you enter git commit messages, within quotes. 
											// so this reads in a quote, keeps going until it sees the second quote and then takes the appropriate substring. 
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
		try (Scanner scan = new Scanner(System.in)) {
			System.out.println("Enter the moves and \"q\" when done");
			
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
	}
	
	/**
	 * TODO dunno			// This is a large function that reads builds the tree from reading in the file. Initially it was two functions, 
	 * 						// buildtree and buildlist, but then I decided to merge it into one function because buildtree always went after buildlist. 
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
				
				// TODO reading in the file is a pita. Please comment this!			Um... don't understand what the question is. :/
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
	 * printTree() prints the ...opening tree? TODO write more accurate comment, *****UNUSED METHOD*****		// Yes, this prints the opening tree but was 
	 * only used early on in the development to make sure that the tree was constructed properly. After that I never really used this function again. 
	 */
//	public void printTree() {
//		this.root.printTreeID(); // TODO why can't you call this directly?		// Call it directly from... where? 
//	}
	
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
	 * TODO		// Traverse is really just a "work with the program" part. Here the user can traverse the tree, add nodes and descriptions to nodes and such. 
	 */
	public void traverse() {
		this.player = "black";
		
		Stack<Tree> position = new Stack<Tree>();
		position.push(this.root);
		Tree current = position.peek();

		Boolean saved = true;
		char action = '0';
		char ans = 'n';
		String next;
		String newDescription;
		Tree nextStep;
		Tree newTree;

		this.showMessage();
		
		do {
			try (Scanner scan = new Scanner(System.in)) {
				
				current = position.peek();
				System.out.println("~> ");
				action = scan.next(".").charAt(0); // read in the first char
				
				// select game play options
				switch(action) {
					case 'j': // TODO desc of each case			// This "jumps" to the child node that the user specifies. If one that matches the name 
																// doesn't exist, a new child is created. (New move variation from that point) 
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
					case 'b': // TODO add comment		// go to the parent of the child. We're taking back a move. 
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
					case 'd': // TODO add comment		// Print out the description that is entered at that move. Ie, the player's thoughts on the move 
														// that should be recorded there from previous use. 
						System.out.println(current.getDescription());
						break;
					case 'a': // TODO add comment		// This is where we append a new description onto the old one. 
						// TODO why can't these be done on one line?		// Uhh, no reason. 
						newDescription = inputDescription(false);
						newDescription = current.getDescription() + newDescription;
						
						current.setDescription(newDescription);
						break;
					case 'r': // TODO add comment		// This is replacing the description with the one that the user enters. 
						newDescription = inputDescription(false);
						newDescription = scan.next(); // TODO overwriting the line above??
						current.setDescription(newDescription);
						break;
					case 'c': // TODO add comment		// Print the children of the current move. (currently analyzed next moves). 
						current.printChildrenMoves();
						break;
					case 's': // TODO add comment		// save the changes into the opening book file. 
						System.out.println("This option cannot be undone. "
						    + "Are you sure you want to save? (y/n): ");
						ans = scan.next(".").charAt(0);
						if (ans == 'y') {
							save();
							System.out.println("Saved changes.");
						}
						saved = true; // TODO should be in the if block?? ^		Um, yeah, it should, I'm not sure why this is outside the if block. 
						break;
					case 'q': // TODO add comment		This should cause a return statement that quits the program. 
						// TODO this doesn't actually do anything except display a message		// so long as the return statement works... this shoudl work. 
						if (!saved) {
							System.out.println("There are unsaved changes. "
							    + "Are you sure you want to quit without saving? (y/n): ");
							ans = scan.next(".").charAt(0);
							if (ans == 'y') {
								return; // TODO not sure this works in java?			// oh, um, is there a different construct that works in Java?
																						// there has to be some way to break out of a function! 
							}
						}
						else {
							return;
						}
						break;
					// Displays list of descriptions of all tree traversing commands
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
			}
		} while (true); // TODO is there a better way to control this loop?		// Probably, I'm not sure why I chose a do while loop. 
																				// Either way I want to use a if/else chained thing instead 
																				// to allow for more flexible commands. 
	}
	
	/**
	 * showMessage() prints the initial messages of the given type of book
	 */
	public void showMessage() {
		if (type.equals("gamebook")) {
			System.out.println("You should have recorded the game by now.");
			System.out.println("You are at the start of the game you just recorded.");
			// TODO these messages seem conflicting...		// No because this one prints when we are exploring a game and have just recorded it. 
		}
		else { // type.equals("opening")
			System.out.println("This is the chess opening book tool.");
			System.out.println("Type in \"h\" to see command options.");
			// While this one was printed for the case when we are working with opening book. 
		}
	}
	
	/**
	 * save() saves the current game to file
	 */
	public void save() {
		// calls save on Tree object
		try {
			this.root.save(new OutputStreamWriter(this.write));
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
