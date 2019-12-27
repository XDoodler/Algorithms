import java.io.*;
import java.util.*;

class Codeforces{
	String handle;
	int rating;
	public Codeforces(String a, int b) {
		//System.out.println("CF Constructor : User : " + a + ", Rating : " + b);
		handle = a; rating = b;
	}
	public void display() {
		System.out.println("Codeforces : User : " + handle + ", Rating : " + rating);
		Hackerearth he = new Hackerearth();
		he.display(handle, rating);
	}

}
class Hackerearth{
	String handle;
	int rating;
	public void display(String a, int b) {
		System.out.println("Hackerearth : User : " + a + ", Rating : " + b);
		handle = a; rating = b;
	}
}
public class Codechef {

    public static void main(String[] args) {

    	Scanner sc = new Scanner(System.in);
    	String x = sc.next();
    	int y = sc.nextInt();
    	//Codechef cc = new Codeforces(x, y);
		Codeforces cf = new Codeforces(x, y);
    	cf.display();
    	System.out.println("Codechef Ratings : User : " + x + ", Rating : " + y);

    }
}

/*
input:
nuttela 2000

output:
Codeforces : User : nuttela, Rating : 2000
Hackerearth : User : nuttela, Rating : 2000
Codechef Ratings : User : nuttela, Rating : 2000
*/
