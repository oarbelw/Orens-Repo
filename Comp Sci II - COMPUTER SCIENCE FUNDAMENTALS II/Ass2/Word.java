
public class Word {
	//private variables
	private LinearNode <Letter> firstLetter;
	
	//constructor
    public Word(Letter[] letters){
        LinearNode <Letter> prev = null;
        LinearNode <Letter> curr = null;
        for(int i = 0; i < letters.length; i++){
            curr = new LinearNode(letters[i]);
            if(i == 0){
                firstLetter = curr;
                prev = curr;
            } else {	
            prev.setNext(curr);
            prev = curr;
            }
        }
    }
	
	@Override
	public String toString() {
		LinearNode <Letter> curr = firstLetter;
		String string = "Word: ";
		while (curr != null) {
			if (curr.getNext() == null) {
				string = string + curr.getElement().toString();
			} else {
				string = string + curr.getElement().toString() + " ";
				curr = curr.getNext();
			}
		}
		return string; 
	}
	
	//updates mystery word letters with label attribute
	public boolean labelWord(Word mystery) {
		LinearNode <Letter> mycurr = this.firstLetter;
		LinearNode <Letter> othercurr = mystery.firstLetter;
		boolean identical = true;
		boolean nnull = true;
		while (nnull) {
			while (nnull) {
				if(mycurr == null || othercurr == null){
					nnull = false;
				}
				if (mycurr.getElement().equals(othercurr.getElement())) {
					mycurr.getElement().setCorrect(); //this sets the letter to be correct
					mycurr = mycurr.getNext();
					othercurr = othercurr.getNext();
				} 
				else {
					while (nnull) {
						while (nnull) { 
							if(mycurr == null || othercurr == null){
								nnull = false;
							}
							mycurr = mycurr.getNext();
							if (mycurr.getElement().equals(othercurr.getElement())) {
								mycurr.getElement().setUsed(); //this sets the letter to be used
								identical = false;
							} else {
								mycurr.getElement().setUnused(); //this sets the letter to be unused
								identical = false;
							}
						}
				}
					othercurr = othercurr.getNext();
				}
				
			}

		}
		return identical; //this returns true as long as there are no unused or used letters, which would trigger false
	}
	

	

	
	
}
