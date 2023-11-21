public class Dice {

	private int value;
	
	
	public Dice(int value) {
		this.value = value;
	}
	
	public Dice () {
		this.value = -1;
	}
	
	public void roll () {
		this.value = RandomNumber.getRandomNumber(1, 6); //generates a random number between 1 and 6
	}
	
	public int getValue() {
		return value;
	}
	
	
	
	
	
}
