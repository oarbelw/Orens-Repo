
public class Ski {
	//instance variables
	private BinaryTreeNode <SkiSegment> root;
	
	//public methods
	//constructor
	public Ski(String[] data) {
		SkiSegment[] segments = new SkiSegment[data.length]; //creates an array of objects of class SkiSegment of length data (since it will contain the same info)
		for (int i = 0; i < data.length; i++) {//considers every element of data[i]
			if (data[i] == null) segments[i] = null;  //otherwise if it is null, it will store null in segments (does not need parameter to identify object)
			else if (data[i].contains("jump")) segments[i] = new JumpSegment(String.valueOf(i),data[i]); //if data[i] contains jump it stores an object in segments[i] 
			else if (data[i].contains("slalom")) segments[i] = new SlalomSegment(String.valueOf(i),data[i]); //otherwise, if data[i] contains slalom it stores an object in segments[i]
			else segments[i] = new SkiSegment(String.valueOf(i),data[i]); //otherwise, it will store all other data in segments[i] of object SkiSegment
		}
		
		TreeBuilder<SkiSegment> builder = new TreeBuilder<SkiSegment>(); //creates a TreeBuilder object 
		LinkedBinaryTree<SkiSegment> tree = builder.buildTree(segments); //contructs tree with data in array segments created above
		
		root = tree.getRoot(); //stores the root of that tree to instance variable root
	}
	
	public BinaryTreeNode<SkiSegment> getRoot() {
		return root; //returns the tree's root node that instance variable uses
	}
	
	
	public void skiNextSegment (BinaryTreeNode<SkiSegment> node, ArrayUnorderedList<SkiSegment> sequence) { //finds the next segment to ski on
		if (node != null) { //as long as the node is not a leaf node
			sequence.addToRear(node.getData()); //this adds the data stores in parameter node to end of sequence
			
			//determining the next node to access from the node passed as parameter
			BinaryTreeNode<SkiSegment> leftnode = node.getLeft(); //gets the left node
			BinaryTreeNode<SkiSegment> rightnode = node.getRight(); //gets the right node
			BinaryTreeNode<SkiSegment> next = nextNode(leftnode, rightnode); //this just initializes the next node to null temporarily that we determine based on requirements
			skiNextSegment(next, sequence); //recursive part
		}
	}
	
	private BinaryTreeNode<SkiSegment> nextNode(BinaryTreeNode<SkiSegment> left, BinaryTreeNode<SkiSegment> right) {//left node and right node will be assessed from skiNextSegment above
		if (left == null && right == null) return null; //finished if no subsequent paths
		
		else if (left == null || right == null) {//if either one is equal to null (cant be both because of else if)
			if (left != null) return left; //if left is not null we use left
			else return right; //otherwise we use right
		}

		//otherwise if there are 2 possible paths:
		SkiSegment leftn = left.getData(); //creates a left node that can be used to compare to SkiSegment objects
		SkiSegment rightn = right.getData(); //creates a right node that can be used to compare to SkiSegment objects
		
		if (leftn instanceof JumpSegment && rightn instanceof JumpSegment) {//if both contains jumps, will choose best one (based on height)
			JumpSegment leftj = (JumpSegment) leftn; //must cast in order to use getheight which is a JumpSegment method
			JumpSegment rightj = (JumpSegment) rightn; //must cast in order to use getheight which is a JumpSegment method
			if (leftj.getHeight() > rightj.getHeight()) return left; //if left node has the greater height, choose left node
			else return right; //otherwise if it is equal or right is bigger return right
		}
		
		else if (leftn instanceof JumpSegment || rightn instanceof JumpSegment) {//if one of them contains a jump, we will choose that path
			if (leftn instanceof JumpSegment) return left; //if the left has a jump and right doesnt, returns left
			else return right; //otherwise we will return right since right has a jump and left doesnt
		}
		
		else if (leftn instanceof SlalomSegment && rightn instanceof SlalomSegment) {//if both contain slaloms, go to leeward direction
			SlalomSegment lefts = (SlalomSegment) leftn; //must cast a left node that can be used to compare to SkiSegment objects
			if (lefts.getDirection().equals("L")) return left; //if left is the leeward direction return left
			else return right; //otherwise the right is the leeward direction and must return right
		}
		
		else if (leftn instanceof SlalomSegment || rightn instanceof SlalomSegment) {//if one of them contains slaloms, go to slaloms only if it is leeward
			if (leftn instanceof SlalomSegment) { //if left is the slalom node
				SlalomSegment lefts = (SlalomSegment) leftn; //must cast a left node that can be used to compare to SkiSegment objects
				if (lefts.getDirection().equals("L")) return left; //if left is the slalom and it is leeward return left
				else return right; //otherwise if left is windward return right
			}
			else { //otherwise right is the slalom node
				SlalomSegment rights = (SlalomSegment) rightn; //must cast a right node that can be used to compare to SkiSegment objects
				if (rights.getDirection().equals("L")) return right; //if right is the slalom and it is leeward return right
				else return left; //otherwise if right is windward return left; 
			}
		}
		else return right; //if both are regular segments choose right as default

	}

}
