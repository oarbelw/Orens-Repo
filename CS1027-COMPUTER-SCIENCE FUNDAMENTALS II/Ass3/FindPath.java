import java.io.IOException;

public class FindPath {
	
	//private instance variables
	private Map pyramidMap;
	
	//public methods
	// constructor
	public FindPath(String filename) {
		try {
			pyramidMap = new Map(filename); //creates an object of class Map with the input file as the argument and sets it to instance variable pyramidMap
		}
		catch (InvalidMapCharacterException | IOException e) {System.out.println("Exception raised");}
	}
	
	public DLStack<Chamber> path() {
		DLStack <Chamber> stack = new DLStack<Chamber>(); //this creates a stack
		Chamber entrance = pyramidMap.getEntrance(); //this gets the starting chamber
		int N = pyramidMap.getNumTreasures(); //this gets the number of treasures
		stack.push(entrance);
		entrance.markPushed();
		int TFound = 0; //this keeps track of how many treasures were found

		
		while(stack.isEmpty() == false) {//while the stack is not empty
			Chamber curr = stack.peek(); //peeks at the stack to get current chamber
			if ((curr.isTreasure() == true)) TFound += 1; //if it found treasure, add 1
			if ((curr.isTreasure() == true) && (TFound == N)) { // if the current chamber has treasure and total found treasure is as much as there is on the map:
				break; //this immediately exists the while loop
			}
			Chamber c = bestChamber(curr); //this sets chamber c (best neighbouring chamber) to be the best possible chamber for current chamber to go into
			if (c != null) {
				stack.push(c); //if c is not null, push c into stack 
				c.markPushed();//then mark it as pushed
			} else {
				stack.pop().markPopped(); //pops the top chamber and marks as popped
			}
			
		
		}
		return stack;
	

	}
	
	public Map getMap() { //getter that returns the map
		return pyramidMap;
	}
	
	public boolean isDim(Chamber currentChamber) {
		for (int i = 0; i < 6; i++) {//this will look at all 6 sides of a current room and plug it into getNeighbor to see if they are light or not.
			if (currentChamber.getNeighbour(i) == null) continue;
			if ((currentChamber != null) && (currentChamber.isSealed() == false) && (currentChamber.isLighted() == false) && (currentChamber.getNeighbour(i).isLighted())) return true; //if all of these are true, return true as it is dim. It will return true only if one of the 6 neighbors are light. 
		}
		return false; //otherwise returns false and it is not dim
	}
	
	public Chamber bestChamber(Chamber currentChamber) {
			for (int i = 0; i < 6; i++) {//first checking to see if neighboring chamber is unmarked treasure
				if (currentChamber.getNeighbour(i) == null) continue; //if there is a null neighbour, add iteration to i and continue
				if (currentChamber.getNeighbour(i).isTreasure() && currentChamber.getNeighbour(i).isMarked() == false) { //if the neighbor chamber has treasure and is not marked:
					return currentChamber.getNeighbour(i); //returns current neighbhor chamber at that index which would immediately return the neighbor chamber and break
					}
				}
			for (int i = 0; i < 6; i++) {// checking to see if neighboring chamber is unmarked lighted
				if (currentChamber.getNeighbour(i) == null) continue; //if there is a null neighbour, add iteration to i and continue
				if (currentChamber.getNeighbour(i).isLighted() && currentChamber.getNeighbour(i).isMarked() == false) {//if the neighbor chamber is light and is not marked:
					return currentChamber.getNeighbour(i); //returns the smallest index which would be the first found, if any, and it returns that and breaks
					}
				}
			for (int i = 0; i < 6; i++) {// checking to see if neighboring chamber is unmarked dim
				if (currentChamber.getNeighbour(i) == null) continue; //if there is a null neighbour, add iteration to i and continue
				if (isDim(currentChamber.getNeighbour(i)) && currentChamber.getNeighbour(i).isMarked() == false) {//if the neighbor chamber is dim and is not marked:
					return currentChamber.getNeighbour(i);//returns the smallest index in which the neighbour chamber is dim and is not marked
					}
				}
		
			return null;
		}
		
	


			
}