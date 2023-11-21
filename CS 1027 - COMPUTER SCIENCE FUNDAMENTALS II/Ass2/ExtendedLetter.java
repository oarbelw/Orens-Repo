
public class ExtendedLetter extends Letter {

	
	//private variables
	private String content;
	private int family;
	private boolean related;
	private final int SINGLETON = -1;
	 
	
	///public methods
	//constructor
	public ExtendedLetter(String s) {
		super('c');
		this.content = s;
		this.related = false;
		this.family = this.SINGLETON;
	 }
	
	public ExtendedLetter(String s, int fam) {
		super('c');
		this.content = s;
		this.related = false;
		this.family = fam;
	}
	
	public boolean equals(Object other) {
		if (other instanceof ExtendedLetter) {
			ExtendedLetter oth = (ExtendedLetter) other;
			if (this.family == oth.family) {
				this.related = true;
			}
			if (this.content == oth.content) {
				return true;
			}
		}
		return false; //this by default returns fault because true is only triggered in the other circumstances above
	}
	
	@Override
	public String toString() {
		if (decorator() == "-") { //minus represents UNUSED
			if (this.related == true) {//if they are related
				return "." + this.content + ".";
			}
		}
		return decorator() + this.content + decorator();
	}
	
	public static Letter[] fromStrings(String[] content, int[] codes) {
		Letter[] letters = new Letter[content.length]; //creates an array the length of the content
		try { //if code is not null
			for (int i = 0; i < letters.length; i++) {
				letters[i] = new ExtendedLetter(content[i], codes[i]);
			}
		}
		catch (NullPointerException e) { //incase code is null
			for (int i = 0; i < letters.length; i++) {
				letters[i] = new ExtendedLetter(content[i]);
			}
		}
		return letters;
	}
	
	
	
	
}
