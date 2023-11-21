

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Hashtable;
import java.util.Scanner;
import java.util.ArrayList;


public class Spell {
	//create a variable dictionary that will be used as the variable
	public static Hashtable<String, Boolean> dictionary = new Hashtable<String, Boolean> ();
	
	public static long endtime;
    public static void getEndTime(long time) {
    	endtime = time;
    }
	
	public Spell(String dictfile, String filetocheck){
    	//want to use try to make sure we can catch a file not found error from our input
    	try {
            Scanner sc = new Scanner(new File(dictfile)); //this scans the dictionary text file
            while (sc.hasNextLine()) { //looks at every line of dictionary
                String word = sc.nextLine().toLowerCase(); //gets the value of a word and turns it to lowercase
                dictionary.put(word, true); //puts the word into a hash table
            }
            sc.close(); 
        } catch (FileNotFoundException e) {
            System.out.println("Dictionary file not found."); //to inform user of wrong input
        }

        // Load words in fileToCheck.txt
    	try {
            Scanner sc = new Scanner(new File(filetocheck));
            while (sc.hasNextLine()) {
                String word = sc.nextLine().toLowerCase();
                if (checkSpelling(word) == false) {//if we run the spell check function with the given word from file to check and it is false, it is spelt wrong
                	if (suggestCorrections(word) == false) { //if there are no suggestions
                		System.out.println(word + ": No Suggestions");
                	}
                	else { //otherwise, there are suggestions to be made
                        System.out.println(word + ": Incorrect Spelling");
                        
                        ArrayList<String> suggestions = new ArrayList<String>();//initializes a list to store the suggestions 
                        
                        if (!correctSpellingSubstitution(word).isEmpty()) { //if there is a correct spelling substitution possible, add it as a suggestion
                        	suggestions.addAll(correctSpellingSubstitution(word));//stores the suggestion into the list
                        }
                        if (!correctSpellingWithOmission(word).isEmpty()) { //if there is a correctSpellingWithOmission possible, add it as a suggestion
                        	suggestions.addAll(correctSpellingWithOmission(word));
                        }
                        if (!correctSpellingWithInsertion(word).isEmpty()) { //if there is a correctSpellingWithInsertion possible, add it as a suggestion
                        	suggestions.addAll(correctSpellingWithInsertion(word));
                        }
                        if (!correctSpellingWithReversal(word).isEmpty()) { //if there is a correctSpellingWithReversal possible, add it as a suggestion
                        	suggestions.addAll(correctSpellingWithReversal(word));
                        }
                		System.out.println(word + " => " + suggestions);//this prints out all the suggestions
                	}
                }
            }
            sc.close();
        } catch (FileNotFoundException e) {
            System.out.println("File to check not found.");
        }
    	
    	long endtime = System.currentTimeMillis();
    	getEndTime(endtime);
    }

    public static void main(String[] args) {
        // init an object of type Spell
    	long starttime = System.currentTimeMillis();
        Spell spell = new Spell(args[0],args[1]);
        long runtime = endtime - starttime;
        System.out.println("total runtime: "+runtime);
    }

    // this function check if the dictionay is loaded or not
    public static Hashtable<String, Boolean> getDictionary(){
    	return dictionary; //returns the dictionary
    }

    // This function takes a String word as an argument to check if the word exists in the dictionary. 
    public static boolean checkSpelling(String word){
       if (getDictionary().containsKey(word.toLowerCase())) {
           return true;
       }
       else {
    	   return false;
       }
    }

    // This function takes a String input word as argument.
    // The function also uses four different methods (correctSpellingWithSubstitution,
    // correctSpellingWithOmission, correctSpellingWithInsertion, correctSpellingWithReversal)
    // to generate possible corrected spellings for the input word.
    public static boolean suggestCorrections(String word) {
        if (!correctSpellingSubstitution(word).isEmpty()) return true; //if there is a correct spelling substitution possible, can return true that there is possibly suggestions
        if (!correctSpellingWithOmission(word).isEmpty()) return true; //if there is a correct spelling with omission possible, can return true that there is possibly suggestions
        if (!correctSpellingWithInsertion(word).isEmpty()) return true; //if there is a correct spelling with insertion possible, can return true that there is possibly suggestions
        if (!correctSpellingWithReversal(word).isEmpty()) return true; //if there is a correct spelling with reversal possible, can return true that there is possibly suggestions
        else return false; //otherwise, if there are no suggestions, return false
    }

    // This function takes in a string word and tries to correct the spelling by substituting letters and 
    // check if the resulting new word is in the dictionary.
    static ArrayList<String> correctSpellingSubstitution(String word) {
        ArrayList<String> tmpwords = new ArrayList<String>(); //a list to store new suggestions
    	for (int i = 0; i < word.length(); i++) {//this looks at every index of the given word
    	    for(char c = 'a'; c <= 'z'; ++c) {//this iterates through ever letter of the alphabet
    	    	String tmpword = word.substring(0, i) + c + word.substring(i + 1);//puts a new string together with the character subbed in
        		//now check if this newly changed word is a real word
    	    	if (checkSpelling(tmpword) == true && !tmpwords.contains(tmpword)) {//if this word is true spelling and we havent already added it in the list of suggestions,
    	    		tmpwords.add(tmpword); //than we add it to our list of suggestions
    	    	}
    	    }
    	}
    	return tmpwords;
    }

    // This function tries to omit (in turn, one by one) a single character in the misspelled word 
    // and check if the resulting new word is in the dictionary.
    static ArrayList<String> correctSpellingWithOmission(String word) {
        ArrayList<String> tmpwords = new ArrayList<String>();
        for (int i = 0; i < word.length(); i++) {
        	String tmpword = word.substring(0, i) + word.substring(i + 1); //this creates a new string that puts together every part of the word besides a character at the index
        	if (checkSpelling(tmpword) == true && !tmpwords.contains(tmpword)) {
	    		tmpwords.add(tmpword);
        	}
        }
        return tmpwords;
    }

    // This function tries to insert a letter in the misspelled word 
    // and check if the resulting new word is in the dictionary.
    static ArrayList<String> correctSpellingWithInsertion(String word) {
    	ArrayList<String> tmpwords = new ArrayList<String>();
    	for (int i = 0; i < word.length()+1; i++) {//we add +1 since we are adding a character in the middle
    	    for(char c = 'a'; c <= 'z'; ++c) {
    	    	String tmpword = word.substring(0, i) + c + word.substring(i);//this creates a new string that inserts c in the middle
        		//now check if this newly changed word is a real word
    	    	if (checkSpelling(tmpword) == true && !tmpwords.contains(tmpword)) {
    	    		tmpwords.add(tmpword);
    	    	}

    	    }
    	}
    	return tmpwords;
    }
    
    // This function tries swapping every pair of adjacent characters 
    // and check if the resulting new word is in the dictionary.
    static ArrayList<String> correctSpellingWithReversal(String word) {
    	ArrayList<String> tmpwords = new ArrayList<String>();
    	for (int i = 0; i < word.length()-1; i++) {//we -1 there is n-1 possibilities of reversal, where n is the number of characters of words
    		String tmpword = word.substring(0,i) + word.charAt(i+1) + word.charAt(i) + word.substring(i+2); //we basically swap the character at i+1 with i,
    		if (checkSpelling(tmpword) == true && !tmpwords.contains(tmpword)) {
	    		tmpwords.add(tmpword);
    		}
    	}
    	return tmpwords;
    }

}
