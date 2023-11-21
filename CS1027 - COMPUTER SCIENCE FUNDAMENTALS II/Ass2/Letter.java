
public class Letter {

	// initializing variables and constants
	private char letter;
	private int label;
	private final int UNSET = 1;
	private final int UNUSED = 2;
	private final int USED = 3;
	private final int CORRECT = 4;
	
	//methods
	
	public Letter(char c) {
		label = UNSET;
		letter = c;
	}
	
	public boolean equals(Object otherObject) {
		if (otherObject instanceof Letter) {
			Letter object = (Letter)otherObject;
			if (this.letter == object.letter) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	
	public String decorator() {
		if (label == USED) {
			return "+";
		}
		if (label == UNUSED) {
			return "-";
		}
		if (label == CORRECT) {
			return "!";
		}
		else { // this is UNSET
			return " ";
		}
	}
	@Override
	public String toString() {
		return decorator() + letter + decorator();
	}
	
	public void setUnused() {
		label = UNUSED;
	}
	
	public void setUsed() {
		label = USED;
	}
	
	public void setCorrect() {
		label = CORRECT;
	}
	
	public boolean isUnused() {
		if (label == UNUSED) {
			return true;
		} else {
			return false;
		}
	}
	
	public static Letter[] fromString(String s) {
		Letter[] arr = new Letter[s.length()];
		for (int i = 0; i < s.length(); i++) {
			arr[i] = new Letter(s.charAt(i));
		}
		return arr;
	}
	
	

	
}
