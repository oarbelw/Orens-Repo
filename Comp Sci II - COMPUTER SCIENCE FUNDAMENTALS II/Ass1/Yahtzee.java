import java.util.Arrays;  
public class Yahtzee {
	
	private Dice dice[];

	public Yahtzee () {
		dice = new Dice[5]; //initializes dice array
		for (int i = 0; i < dice.length; i++) { //loop structure for iterating over the array
			Dice darr = new Dice();
			darr.roll(); //this rolls the dice
			dice[i] = darr; //this puts the variables of the roll in the dice array
		}
	}		
	
	public Yahtzee (Dice dice[]) {
		this.dice=dice; //initializes dice
	}
	
	public int[] getValueCount() { 
		int count[] = new int[6]; //creates a new 6 variable array
		for (int i = 0; i < dice.length; i++) { 
			count[dice[i].getValue()-1]++; //this gets the value of each variable in the array, and adds 1 every time the same number is used
		}
		return count;
	}
			
	public int[] getScoreOptions() {
		int scorarr[] = new int[13];
		int value[] = getValueCount();
		
		//Upper section
		scorarr[0] = value[0];
		scorarr[1] = value[1]*2;
		scorarr[2] = value[2]*3;
		scorarr[3] = value[3]*4;
		scorarr[4] = value[4]*5;
		scorarr[5] = value[5]*6;
		//Lower section
		scorarr[6] = ThreeOfAKind(value, scorarr);
		scorarr[7] = FourOfAKind(value, scorarr);
		scorarr[8] = FullHouse(value);
		scorarr[9] = SmallStraight(value);
		scorarr[10] = LargeStraight(value);
		scorarr[11] = checkYahtzee(value);
		scorarr[12] = Chance(scorarr);
		
		
		return scorarr;
	}
	//codes for lower sections:
	
	//3 of a kind code
	private int ThreeOfAKind(int[] value, int[] scorarr) {
		int sum = 0;
		for(int i=0;i<6;i++) {
            if(value[i]>=3) { //if the value of a number is equal to or exceeds 3
            	sum = scorarr[0] + scorarr[1] + scorarr[2] + scorarr[3] +scorarr[4] + scorarr[5];
                return sum;
            }
        }
        return 0;
	}
	   
	//4 of a kind code
	private int FourOfAKind(int[] value, int[] scorarr) {
		int sum = 0;
		for(int i=0;i<6;i++) {
            if(value[i]>=4) { //if the value of a number is equal to or exceeds 4
            	sum = scorarr[0] + scorarr[1] + scorarr[2] + scorarr[3] +scorarr[4] + scorarr[5];
            return sum;
            }
        }
        return 0;
	}

	//Full house
	private int FullHouse(int[] value) {
		int FIXEDSCORE = 25;
		for(int i=0;i<5;i++) {
            if((value[i] == 3) && (value[i] == 2)) { //if the value of a number is equal to 3 and 2
                return FIXEDSCORE;
            }
        }
        return 0;
	}
	
	//Small Straight
	private int SmallStraight(int[] value) {
		int FIXEDSCORE = 30;
		if ((value[0] > 0 && value[1] > 0 && value[2] > 0 && value[3] > 0) || (value[1] > 0 && value[2] > 0 && value[3] > 0 && value[4] > 0) || (value[2] > 0 && value[3] > 0 && value[4] > 0 && value[5] > 0)) { // this basically states the orders of the possible 4 dice straight, if the dice have one of these 3 arrangements, they have a straight
			return FIXEDSCORE;
		}
	
		return 0;
	}

	//Large Straight
	private int LargeStraight(int[] value) {
		int FIXEDSCORE = 40;
		if ((value[0] > 0 && value[1] > 0 && value[2] > 0 && value[3] > 0 && value[4] > 0) || (value[1] > 0 && value[2] > 0 && value[3] > 0 && value[4] > 0 && value[5] > 0)) { //this is one less step than the small straight, but if the dice are in one of these 2 arrangements, they are in a large straight
			return FIXEDSCORE;
		}
	
		return 0;
	}	
		
	//Yahtzee
	private int checkYahtzee(int[] value) {
		int FIXEDSCORE = 50;
		for(int i=0;i<5;i++) {
            if(value[i]>=5) { //if the value of a number is equal to or exceeds 5 (basically asking if all 5 values are the same number)
                return FIXEDSCORE;
            }
        }
        return 0;
	}
		
	//Chance
	private int Chance(int[] scorarr) {
		int sum = 0;
				for(int i=0; i<6; i++) {
					sum = scorarr[0] + scorarr[1] + scorarr[2] + scorarr[3] +scorarr[4] + scorarr[5]; //this just regularly returns the sum of all variables
				}
				return sum;
	}
	
	
	//determining the maximum value from the array of possible scores
	public int[] score() {
		int scores[] = getScoreOptions();
		int maxandind[] = new int[2]; //this is what this class returns - an array containing the maximum value and then the corresponding index
		int max = scores[0]; //this just temporarily sets the max to the first index
		int indexsetter = 0; //this is the temporary index setter and when the max is found it will change to that value
		for(int i=0;i<=12;i++) {
			if (scores[i] > max) {
				max = scores[i];
				indexsetter = i; //basically, these lines of code go through every variable found in getScoreOptions, and when a new maximum is found, it is set to that and the index is set to that
			}
		}
		maxandind[0] = max;
		maxandind[1] = indexsetter;
		return maxandind;
	}
	
	//comparing to see if dice are the same
	public boolean equals(Yahtzee other) {
		int myValueCount[] = getValueCount();
		int otherValueCount[] = other.getValueCount();
		if (Arrays.equals(myValueCount, otherValueCount)) {
			return true;
		} else {
			return false;
		}
	}
	
	//public toString
	public String toString() {
		return "Dice: {" + dice[0].getValue() + ", " + dice[1].getValue() + ", " + dice[2].getValue() + ", " + dice[3].getValue() + ", " + dice[4].getValue() + "}";
	}
    
}
