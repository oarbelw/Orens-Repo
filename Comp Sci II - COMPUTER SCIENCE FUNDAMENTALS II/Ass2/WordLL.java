
public class WordLL {
	
	//private variables
	private Word mysteryWord;
	private LinearNode <Word> history;
	
	
	///public methods:
	//constructor:
	public WordLL (Word mystery) {
		history = null;
		this.mysteryWord = mystery;
	}
	
	public boolean tryWord (Word guess) {
		LinearNode node = new LinearNode <Word> (guess);
		node.setNext(history);
		history = node;
		return guess.labelWord(mysteryWord);
	}

	public String toString() {
		LinearNode <Word> curr = history;
		String line = "";
		while (curr != null) {
			line = line + (curr.getElement().toString() + "\n");
			curr.getNext();
		}
		return line;
	}
	
	
}
