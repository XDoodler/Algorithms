import java.io.*;
import java.util.*;

public class SeiveOfErasthones {

    public static void main(String[] args) {

    	Scanner sc = new Scanner(System.in);
    	// Seive of erasthones
    	int N = (int)(1e2 + 6);
    	Vector <Integer> seive =  new Vector<Integer>();
    	boolean isPrime[] = new boolean[N];
    	for (int i = 0; i < N; ++i) {
    		isPrime[i] = true;
    	}
    	isPrime[0] = isPrime[1] = false; 
    	for (int i = 2; i < N; ++i) {
    		if (isPrime[i]) {
    			for (int j = (i*i); j < N; j += i) {
    				isPrime[j] = false;
    			}
    		}
    	}

    	for (int i = 1; i < N; ++i) {
    		if(isPrime[i]) {
    			//System.out.print(i + " ");
    			seive.add(i);
    		}
    	}

    	for (int i = 0; i < seive.size(); ++i) {
    		System.out.println(seive.get(i));
    	}

    }
}
