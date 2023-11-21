
public class TreeBuilder<T>{
	
	public LinkedBinaryTree<T> buildTree (T[] data) {
		LinkedQueue<T> dataQueue = new LinkedQueue<T>(); //this just initializes empty dataQueue
		for (T i:data) {//now enqueues data in dataQueue (for i in data)
			dataQueue.enqueue(i);
		}
		
		LinkedQueue<BinaryTreeNode <T>> parentQueue = new LinkedQueue<BinaryTreeNode <T>>(); //this initializes parentQueue as an empty queue
		
		LinkedBinaryTree<T> tree = new LinkedBinaryTree<T>(dataQueue.dequeue());//creates a LinkedBinaryTree object. Sets root node storing first element of dataQueue
		
		parentQueue.enqueue(tree.getRoot()); //this gets the root node and enqueues it on parentQueue
		
		while (!dataQueue.isEmpty()) { //while dataQueue is not empty (has elements)
			T a = dataQueue.dequeue(); //top of dataQueue
			T b = dataQueue.dequeue(); //top of dataQueue
			BinaryTreeNode<T> parent = parentQueue.dequeue(); //parent is of type BinaryTreeNode, sets top of parentQueue
			
			if (a != null) {//if a is not null
				BinaryTreeNode<T> na = new BinaryTreeNode<T>(a); //na is node a. na stores a
				parent.setLeft(na); //sets a as left child of parent
				parentQueue.enqueue(na); //enqueues node a on parentQueue
			}
			
			if (b != null) {//if b is not null (do similar of above)
				BinaryTreeNode<T> nb = new BinaryTreeNode<T>(b); //nb is node b. nb stores b
				parent.setRight(nb); //sets b as right chilf od parent
				parentQueue.enqueue(nb); //enqueues node b on parentQueue

			}
		}
		return tree; //returns the LinkedBinaryTree object with the root node from above
	}

}

