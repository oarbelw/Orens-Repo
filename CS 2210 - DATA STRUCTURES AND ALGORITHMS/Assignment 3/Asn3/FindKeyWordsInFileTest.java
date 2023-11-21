import java.io.BufferedReader;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.PriorityQueue;

public class FindKeyWordsInFileTest {
    public static void main(String[] args) {
        int k = Integer.parseInt(args[0]);//k is the number of most frequent words to consider
        String inputFile = args[1];//input file
        String wordListFile = args[2];//double check to see if most frequent word in inputfile is from here
        String s = Integer.toString(k);//used to make as input for main function
        
        //initialize our AVL trees
        AVLTree<String, Integer> wordFrequencies = new AVLTree<>();
        AVLTree<String, Void> englishWords = new AVLTree<>();
        AVLTree<String, Integer> keywordFrequencies = new AVLTree<>();
        
        // prepare arguments to input and test FindKeyWordsinFile
        String[] arguments = {s, inputFile, wordListFile};
        
        String str = "-"; //used to separate test to make more clean
        
//        Test 1 - Test to check if the program reads the input file and creates the word frequency correctly.
        File outfile = new File("out.txt"); //used to redirect output to, dont care to see it in terminal or console, just need to see if test passed
	    outfile.deleteOnExit(); //when program is done, can delete this temporary file
        try {
			FindKeyWordsInFile.computeWordFrequencies(inputFile, wordFrequencies); //computes word frequency
		    System.setOut(new PrintStream(new FileOutputStream(outfile))); // redirects the output to the file out.txt
			wordFrequencies.inOrderTraversal();
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console
	        BufferedReader br = new BufferedReader(new FileReader(outfile));
	        String line;
	        while ((line = br.readLine()) != null) { //while there isnt an empty line being read (read till end of file)
	        	String[] words = line.split(" "); //split words by space into string list
                Integer.parseInt(words[1]); //check if the second value in the line is a number, as it needs to be a frequency, so convert it to integer and if doesnt work there is an error in how word frequency was created
	        } //if there is an error here, it would be a NumberFormatException
	        br.close();
		    System.out.println("Test 1 passed: Input file read and word frequency created successfully."); //if no exceptions triggered, test passed
	    } catch (Exception e) {
	    	if (e instanceof FileNotFoundException) {
	    		System.err.println("Test 1 failed: Input file not found");
	    	}
	    	if  (e instanceof NumberFormatException) {
	    		System.err.println("Test 1 failed: the frequency wasnt computed properly.");
	    	}
	    	else {
	    		System.err.println("Test 1 failed: word frequency wasnt created correctly.");
	    	}
	    }
				 
        System.out.println(str.repeat(100)); //seperated tests
        
//        Test 2 - Test to check if the program finds the k most frequent words correctly
        
        try {
        	PriorityQueue<String> pq = FindKeyWordsInFile.findKMostFrequentWords(k, wordFrequencies);
		    System.setOut(new PrintStream(new FileOutputStream(outfile))); // redirects the output to the file out.txt
		    System.out.println(pq);
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console
		    System.out.println("Test 2 passed: K most frequent words found successfully."); //if no exceptions were raised
		    
		} catch (Exception e) {
			System.err.println("Test 2 failed: K most frequent words were not found successfully.");
		};
		
		System.out.println(str.repeat(100));
		
//		Test 3 - Test to check if the program filters common English words correctly.
		try {
        	PriorityQueue<String> pq = FindKeyWordsInFile.findKMostFrequentWords(k, wordFrequencies);
        	FindKeyWordsInFile.filterCommonEnglishWords(pq, englishWords, keywordFrequencies, wordListFile, wordFrequencies);
		    System.setOut(new PrintStream(new FileOutputStream(outfile))); // redirects the output to the file out.txt
		    keywordFrequencies.inOrderTraversal();
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console
		    System.out.println("Test 3 passed: Common English words filtered successfully.");
		} catch (Exception e) {
			System.err.println("Test 3 failed: Common English words were not filtered successfully.");
		};

		System.out.println(str.repeat(100));
		
//		Test 4 - Test to check if the program generates the correct output for file3.txt, lets set k to 20 so we can test properly.
		String f3 = "file3.txt"; //set file to be file3.txt
		String s4 = Integer.toString(20); //set k to be 20
		String ewords = "MostFrequentEnglishWords.txt"; //well use the same english words 
        String[] a = {s4, f3, ewords}; //get ready to input into main
        
        String[] file3corr = //correct output for file3 with k=20 and with MostFrequentEnglishWords.txt
        	{"banana 4\n"
        			+ "carrot 4\n"
        			+ "elephant 8\n"
        			+ "fern 4\n"
        			+ "gardenia 4\n"
        			+ "grapefruit 4\n"
        			+ "igloo 4\n"
        			+ "kangaroo 4\n"
        			+ "lily 8\n"
        			+ "magnolia 4\n"
        			+ "umbrella 8\n"
        			+ "vanilla 4\n"
        			+ "violet 8\n"
        			+ "waffle 4\n"
        			+ "xray 4"};

		try {
			FileWriter writer = new FileWriter("file3corr.txt"); //creates the file3corr.txt so that we can put correct output in that file
			File file = new File("file3corr.txt");
			file.deleteOnExit(); //deletes file after use
	        for(String l: file3corr) {
	          writer.write(l + System.lineSeparator());//writes lines
	        }
	        writer.close();
	        
		    System.setOut(new PrintStream(new FileOutputStream(new File ("t4.txt")))); // redirects the output to the file t4.txt
		    File f = new File("t4.txt");
			f.deleteOnExit(); //deletes file after use
			FindKeyWordsInFile.main(a);	//run the main function with the set arguments
			
			Path file1 = Path.of("file3corr.txt");
			Path file2 = Path.of("t4.txt");
			
			//read file to strings
	        String str1 = Files.readString(file1);
	        String str2 = Files.readString(file2);
	        
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console

		    if (!str1.equals(str2)) throw new Exception(); //if the expected output doesnt equal the output we achieved, incorrect results, throw exception
		    System.out.println("Test 4 passed: Program generated correct output for file3.txt.");
		} catch (Exception e) {
			System.err.println("Test 4 failed: Program did not generate correct output for file3.txt.");
		};

		System.out.println(str.repeat(100));
		
		
//		Test 5 - Test to check if the program handles empty input files.
		try {			
		    System.setErr(new PrintStream(new FileOutputStream(outfile))); // redirects the error output back to the file out.txt
		    System.setOut(new PrintStream(new FileOutputStream(outfile))); // redirects the output back to the file out.txt
		    FindKeyWordsInFile.main(arguments); //runs main program
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console
		    Path f = Path.of("out.txt");
	        String string = Files.readString(f).replace("\n", ""); //reads output and puts to string
	        //get the 2 possible error messages if it is empty
	        String errmess1 = "Error: " + inputFile.toString() + " is empty";
	        String errmess2 = "Error: " + wordListFile.toString() + " is empty";
	        //gets string of content of both input files
	        Path f1 = Path.of(inputFile.toString());
	        String string1 = Files.readString(f1).replace("\n", "");
	        Path f2 = Path.of(wordListFile.toString());
	        String string2 = Files.readString(f2).replace("\n", "");
	        if (!string1.isEmpty() && !string2.isEmpty()) { //if both files and english files are not empty, cannot have empty input file error
	        	System.out.println("Test 5 passed: Program handled these non empty input files.");
	        }
	        else if (errmess1.equals(string) || errmess2.equals(string)) {//if either one of the error messages is the output, handled the empty input files
	        	System.out.println("Test 5 passed: Program handles empty input files.");
	        }
	        else throw new Exception();
		} catch (Exception e) {
			System.out.println("Test 5 failed: Program does not handle empty input files, maybe this file doesnt exist?");
		}
		
		System.out.println(str.repeat(100));
		
//		Test 6 - Test to check if the program handles non-existing input files.
		try {			
		    System.setErr(new PrintStream(new FileOutputStream(outfile))); // redirects the error output back to the file out.txt
		    System.setOut(new PrintStream(new FileOutputStream(outfile))); // redirects the output back to the file out.txt
		    FindKeyWordsInFile.main(arguments);
			System.out.flush(); // flushes the output to the file
		    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out))); // redirects the output back to the console
		    Path f = Path.of("out.txt");
	        String string = Files.readString(f).replace("\n", "");
	        String errmess1 = "FileNotFoundException: " + inputFile.toString() + " was not found";
	        String errmess2 = "FileNotFoundException: " + wordListFile.toString() + " was not found";
	        if (errmess1.equals(string) || errmess2.equals(string)) {//if the output of running the main function is the error message we predict, the program handles non-existing input files
	        	System.out.println("Test 6 passed: Program handles non-existing input files.");
	        }
	        File finputFile = new File(inputFile);
	        File fwordListFile = new File(wordListFile);
	        
	        //check if both the inputted files exist
	        if (finputFile.exists() && !finputFile.isDirectory()) {
	        	if (fwordListFile.exists() && !fwordListFile.isDirectory()) {
	        		System.out.println("Test 6 passed: Program handles existing input files.");
	        	}
	        }
	        else throw new Exception();
		} catch (Exception e) {
			System.out.println("Test 6 failed: Program does not handle non-existing input files, maybe this file exists.");
		}
    }
}
