/* XPLORE 2019 - 28 DECEMBER JAVA Object Oriented Programming Problem */

/* nuttela - Soham Chakrabarti */

import java.io.*;
import java.util.*;

// Movie Class
class Movie {

	// global variables
	String nameOfMovie, nameOfProducingComapny, genre;	
	double budget;

	// getters and setters (constructor)
	public Movie(String a, String b, String c, double d) {	
		nameOfMovie = a;
		nameOfProducingComapny = b;
		genre = c;
		budget = d;
	}
}

// Solution Class

public class Solution {
	public static void main(String[] args) {

		// declaring scanner class
		Scanner sc = new Scanner(System.in);

		//declare array of objects from 'Movie' class
		Movie objectArray[] = new Movie[4];

		String w, x, y;
		double z;
		for (int i = 0; i < 4; ++i) {

			//user inputs
			w = sc.next();
			x = sc.next();
			y = sc.next();
			z = sc.nextDouble();

			// build object with params
			Movie tempObject = new Movie(w, x, y, z);

			//push tempObject into the objectArray
			objectArray[i] = tempObject;
		}

		//input the genre to be checked
		String a = sc.next();

		// call getBudgetRating() to get outputs
		getBudgetRating(a, objectArray);

	}
	public static Movie[] getBudgetRating(String checkGenre, Movie[] movieObject) {

		for (int i = 0; i < 4; ++i) {

			// check if movie genre is same as the provided genre.
			if (movieObject[i].genre.equals(checkGenre)) { // genre matched

				if (movieObject[i].budget > 80000000) { // if movie budget greater than 80000000
					System.out.println("High Budget Movie");
				}
				else {
					System.out.println("Low Budget Movie");
				}
			}	
			else { // skip movie object
				continue;
			}
		}	
		return movieObject;
	}
}

/*
Input 
-------
Batman
DC
Action
950000000
Spiderman
Marvel
Action
1200000000
Inception
xyz
Scifi
100000
Intersteller
xyz
Scifi
890900
Action


Output
--------
High Budget Movie
High Budget Movie

*/
