
public class DLStack<T> implements DLStackADT<T>{
	
	//private instance variables
	private DoubleLinkedNode<T> top;
	private int numItems;
	
	//public methods
	// constructor
	public DLStack() {
		top = null; //initializes top to be null as it will start as an empty stack
		numItems = 0; //initializes number of items to be 0 as it will start as an empty stack
	}
	
	@Override
	public void push(T element) {
		DoubleLinkedNode<T> temp = new DoubleLinkedNode<T>(element); //creates a node of element that will be the new top
		if (isEmpty()) { //if there is nothing in the stack
			top = temp; //sets the temporary to be the new top
			top.setPrevious(null);  
			top.setNext(null); //sets both ends to point to null since there is nothing else in the stack besides pushed element
			numItems++; //increases stack count
			
		} else { //if there are already items in the stack
			temp.setNext(top);
			top.setPrevious(temp);
			temp.setPrevious(null);
			top = temp;
			numItems++;
	
	}
	}

	@Override
	public T pop() throws EmptyStackException {
		if (isEmpty()) throw new EmptyStackException("Empty Stack");
		T result = top.getElement();
		DoubleLinkedNode<T> prev = top;
		if (top.getNext() == null) { //this is the case only if top is the only element left in stack
			top = null;
		} else {
			top = top.getNext();
			top.setPrevious(null);
			prev.setNext(null);
		}
		numItems--;
		return result;
		
	}

	@Override
	public T peek() {
		if (isEmpty()) throw new EmptyStackException("Empty Stack");
		T result = top.getElement();
		return result;
	}

	@Override
	public T pop(int k) throws InvalidItemException {
		if (k > size() || k <= 0) throw new InvalidItemException("Invalid K");
		DoubleLinkedNode<T> temp = top;
		for (int i = 1; i < k; i++) temp = temp.getNext(); //this moves temp to the right spot
		T result = temp.getElement();
		DoubleLinkedNode<T> prev = temp.getPrevious(); //this sets the previous to be the one before temp
		if (prev != null) {
			prev.setNext(temp.getNext()); //this sets the previous node to have now point to one after temp
			
		}
		temp = top; //if previous is null temp is top
		
		
		DoubleLinkedNode<T> next = temp.getNext(); //this sets the next to be the one after temp
		if (next != null ) {
			next.setPrevious(temp.getPrevious()); //this sets the previous node to now point to one before temp

		} else {
			temp.setNext(null);
			temp.setPrevious(null); //these both set both pointers of temp to be null and not pointing to anything
		}
		

		numItems--;
		

		return result;
	}

	@Override
	public boolean isEmpty() {
		if (size() <= 0) return true; //returns true if the stack is empty by checking how many items in stack there are
		else return false;
	}

	@Override
	public int size() {
		return numItems; //returns amount of items there are in stack as the size
	}

	@Override
	public DoubleLinkedNode<T> getTop() {
		return top;
	}
	
	//toString
	public String toString() {
		if (isEmpty()) return "The stack is empty.";
		else {
			String str = "";
			DoubleLinkedNode<T> temp = top; //this sets a temporary value temp equal to top so value of top is not changed
			for (int i = 0; i < size(); i++) {//this will repeat for the amount of items there are in stack
			T result = temp.getElement();
			temp = temp.getNext();
			str += result;
			str += " "; //this adds a space
			}
			String sbtr = str.substring(0, str.length()-1); //this removes the last space
			return "[" + sbtr + "]";
		}
	}
		
		
}
