import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Comparator;
import java.util.HashMap;
import java.util.PriorityQueue;

public class FindKeyWordsInFile {
       
    public static void main(String[] args) {
        if (args.length != 3) { //handles if input file wasnt given
            System.err.println("Usage: java FindKeyWordsInFile k file.txt MostFrequentEnglishWords.txt");
            System.exit(1);
        }
        	
        int k = Integer.parseInt(args[0]); //k is the number of most frequent words to consider
        String inputFileName = args[1]; //input file
        String englishWordsFileName = args[2]; //double check to see if most frequent word in inputfile is from here
        
        String files[] = {inputFileName, englishWordsFileName}; //used to loop through to handle errors below
        
        int exit = 0; //default to 0 meaning dont exit, 1 is exist, used so that system can print all error messages before exiting
        for (String file : files) { //get each file from inputted file
        	try {
                BufferedReader br = new BufferedReader(new FileReader(file)); //read through file
                if (br.readLine() == null) { //if the first line is null, there is nothing in there and it is empty
                	System.err.println("Error: " + file + " is empty"); //print that the file is empty
                	exit = 1; //going to exit after checking for more errors
                }
                br.close(); //closer scanner
            } catch (Exception e) {
            	if (e instanceof FileNotFoundException) {
            		System.err.println("FileNotFoundException: " + file + " was not found"); //if filenotfoundexception was caught, print that the file was not found
                	exit = 1;
            	}
            	else if (e instanceof IOException) {
            		e.printStackTrace(); //if there was an ioexception, print the message
            	}
            }
        }
        
        if (exit == 1) return; //exits program after printing necessary error messages
        
        //initialize our AVL trees
        AVLTree<String, Integer> wordFrequencies = new AVLTree<>();
        AVLTree<String, Void> englishWords = new AVLTree<>();
        AVLTree<String, Integer> keywordFrequencies = new AVLTree<>();
        
        try {
            //Part 1
            // use an AVL tree to compute word frequency for every word in the input file
        	computeWordFrequencies(inputFileName, wordFrequencies);
            
            //Part 2
            // function name => findKMostFrequentWords - use a built-in implementation of a priority queue in 
        	PriorityQueue<String> mostFrequent = findKMostFrequentWords(k, wordFrequencies);
            
            //Part 3
            // function name => filterCommonEnglishWords - if they are not contained in the file englishwords
        	filterCommonEnglishWords(mostFrequent, englishWords, keywordFrequencies, englishWordsFileName, wordFrequencies);
        	
        	keywordFrequencies.inOrderTraversal(); //inOrderTraversal is used to print all the nodes in alphabetical order
            
        } catch (Exception e) { //if there was an exception, print the message
            e.printStackTrace();
        }
    }
    
    static void computeWordFrequencies(String inputFileName, AVLTree<String, Integer> wordFrequencies) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(inputFileName));
        String line;
        while ((line = br.readLine()) != null) { //while there isnt an empty line being read (read till end of file)
        	String[] words = line.toLowerCase().split(" "); //make words case insensitive by converting to lower case and split up words by a space
        	for (String word : words) {
        		word = word.replaceAll("\\p{Punct}", ""); //want to remove all possible punctuation from words, like ending periods or commas to match better
        		int wordfreq;
        		try {
        			wordfreq = wordFrequencies.get(word) + 1; //if able to access value, it is already in tree, add 1 to existing frequency
        		} catch (NullPointerException e) {
        			wordfreq = 1; //if an exception is caught, means it was set to null, meaning word was never in tree, so set freq to 1 as it is the first occurence
        		}
    			wordFrequencies.put(word, wordfreq);         		
        	}
        }
        br.close(); //close reader
//        wordFrequencies.inOrderTraversal(); //prints words in alphabetical order
    }
    
    static PriorityQueue<String> findKMostFrequentWords(int k, AVLTree<String, Integer> wordFrequencies) {
    	PriorityQueue<String> pq = new PriorityQueue<>(new Comparator<String>() {
            public int compare(String s1, String s2) {
                return wordFrequencies.get(s1) - wordFrequencies.get(s2); //this is the custom comparator, compares word frequences and thats how it is sorted
            }
        });
    	    	
    	HashMap<String, Integer> hmap = wordFrequencies.inorder();

//    	 pass lambda expression to forEach()
        hmap.forEach((key, value) -> { //for loop to iterate through keys and values of hmap
        	pq.offer(key); //adds key to priority queue
        	if (pq.size() > k) pq.poll(); //if the size of the priority queue is larger than inputted k, reweigh the pq with poll    	
        	});
//        System.out.println(pq); //peek is front to be removed, lowest val is at front, largest at back.
        return pq; //return the created pq
    }
    
    static void filterCommonEnglishWords(PriorityQueue<String> mostFrequent, AVLTree<String, Void> englishWords, 
    		AVLTree<String, Integer> keywordFrequencies, String englishWordsFileName, AVLTree<String, Integer> wordFrequencies) throws Exception {
    	BufferedReader br = new BufferedReader(new FileReader(englishWordsFileName));
        String line;
        while ((line = br.readLine()) != null) { //while there isnt an empty line being read
        	String[] words = line.toLowerCase().split(" "); //make words case insensitive by converting to lower case and split up words by a space
        	for (String word : words) {
        		word = word.replaceAll("\\p{Punct}", ""); //want to remove all possible punctuation from words, like ending periods or commas to match better
        		englishWords.put(word, null); //put each word in the avl tree, put null as the value, not important		
        	}
        }
        br.close();
        HashMap<String, Void> hmap = englishWords.inorder(); //put the inorder traversal nodes saved into the hmap
        
        hmap.forEach((key, value) -> {
        	if (mostFrequent.contains(key)) {//if an english word is found in the priority queue of most frequent words
        		mostFrequent.remove(key); //then we remove it from the priority queue
        	}
        	});
      
        for (String w : mostFrequent) { //loop through kmost frequent
        	Integer freq = wordFrequencies.get(w); // gets the frequency of that word based on first function
        	keywordFrequencies.put(w, freq); // store the results in keywordFrequencies 
      }
    }
    
}
