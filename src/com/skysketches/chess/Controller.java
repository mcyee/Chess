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
	private int numNodes;
	private Tree root;
	private List<Tree> nodeList; // list of all nodes added prior to current
	
	public Controller(FileInputStream r, FileOutputStream w, String t)
	{
		this.read = r;
		this.write = w;
		this.type = t;
	}
	
	/**
	 * 
	 */
	private String inputDescription(Boolean b) {
		
	}
	
	/**
	 * 
	 */
	private void switchPlayer() {
		
	}
	
	/**
	 * buildGame() builds the tree of moves from user input
	 */
	public void buildGame() {
		numNodes = 1;
		Tree node = new Tree(0, 'm', "start", "the start node");
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
				node = new Tree(numNodes, 'm', move, "");
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
	 * 
	 */
	public void buildList() {
		String nodeName;
		char nodeType;
		String nodeDescription;
		// read in numNodes
		BufferedReader br = new BufferedReader(new InputStreamReader(read));
		try
		{
			// get node information and add to tree
			String temp = br.readLine();
			numNodes = Integer.parseInt(temp);
			for (int i = 0; i < numNodes; i++) {
				nodeType = (char) br.read();
				nodeName = br.readLine();
				nodeDescription = inputDescription(true);
				Tree newNode = new Tree(i, nodeType, nodeName, nodeDescription);
				this.nodeList.add(newNode);
			}
			
			this.root = nodeList.get(0); // Assume first node is root
			
			Stack<Tree> treeStack = new Stack<Tree>();
			String production;
			int token;
			int rootID;
			treeStack.push(root);
			while((production = br.readLine()) != null) {
				List<Tree> treeList = new ArrayList<Tree>();
				StringTokenizer st = new StringTokenizer(production);
				temp = st.nextToken();
				rootID = Integer.parseInt(temp);
			}
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * 
	 */
	public void printTree() {
		
	}
	
	/**
	 * 
	 */
	public void printNodes() {
		
	}
	
	/**
	 * 
	 */
	public void traverse() {
		
	}
	
	/**
	 * 
	 */
	public void showMessage() {
		
	}
	
	/**
	 * 
	 */
	public void save() {
		
	}

}
