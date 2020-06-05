import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
   public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        //code to read values 
        Movie objArr[] = new Movie[4];
        for (int i = 0; i < 4; ++i) {
            int w,y,z;
            String x;
            w = sc.nextInt();
            x = sc.next();
            y = sc.nextInt();
            z = sc.nextInt();
            objArr[i] = new Movie(w,x,y,z);
        }
        String dir;
        int rat, bud;
        dir = sc.next();
        rat = sc.nextInt();
        bud = sc.nextInt();
        int avg = findAvgBudgetByDirector(objArr, dir);
        if (avg != -1) {
          System.out.println(avg);
        }
        Movie res = getMovieByRatingBudget(objArr, rat, bud);
    }

    public static int findAvgBudgetByDirector (Movie[] movies, String director)
      {
          int sum = 0, count = 0;
          for (int i = 0; i < 4; ++i) {
            if(movies[i].director.equalsIgnoreCase(director)) {
              sum += movies[i].budget;
              count++;
            }
          }
          if (sum == 0) {
            System.out.println("Sorry - The given director has not yet directed any movie");
            return -1;
          }
          else {
            int average = (sum / count);
            return average;
          }
      }

    public static Movie getMovieByRatingBudget(Movie[] movies, int rating, int budget)
      {
          Movie obj = new Movie(0,"",0,0);
          if (budget%rating != 0) {
            System.out.println("Sorry - No movie is available with the specified rating and budget requirement");
            return obj;
          }
          int res = 0;
          for (int i = 0; i < 4; ++i) {
            if (movies[i].rating == rating && movies[i].budget == budget) 
              res = movies[i].movieId;
          }
          System.out.println(res);
          return obj;
      }
}

class Movie
{
    int movieId, rating, budget;
    String director;

    public Movie(int a, String b, int c, int d) {
      movieId = a;
      director = b;
      rating = c;
      budget = d;
      
    }
}
