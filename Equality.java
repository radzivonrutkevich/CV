import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static class Pair{
        public final int first_element;
        public final int second_element;
        Pair(int value_1, int value_2){
            first_element = value_1;
            second_element = value_2;
        }
    }

    public static int[] parent;
    public static int[] size;
    public static void make_set (int n) {
        parent = new int[n+1];
        size = new int[n+1];
        for(int i = 1; i < parent.length; i++){
            size[i] = 1;
            parent[i] = i;
        }
    }

    public static int find_set (int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find_set(parent[x]);
    }

    public static void union_sets (int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if(x != y){
            if(size[x] < size[y]) {
                int tmp = x;
                x = y;
                y = tmp;
            }
            parent[y] = x;
            size[x] += size[y];
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        boolean marker = true;
        Scanner in = new Scanner(new File("equal-not-equal.in"));
        String[] str = in.nextLine().split(" ");
        int n = Integer.parseInt(str[0]);
        int m = Integer.parseInt(str[1]);
        boolean checker = true;
        int first_variable, second_variable;
        String sign;
        Pair obj;
        ArrayList<Pair> array = new ArrayList<>();
        make_set(n);
        for(int i = 1; i <= m; i++){
            str = in.nextLine().split(" ");
            first_variable = Integer.parseInt(str[0].substring(1,str[0].length()));
            sign = str[1];
            second_variable = Integer.parseInt(str[2].substring(1,str[2].length()));
            if(sign.equals("==")){
                union_sets(first_variable,second_variable);
            }
            else{
                obj = new Pair(first_variable,second_variable);
                array.add(obj);
            }
        }

        for (Pair pair : array) {
            if (find_set(pair.first_element) == find_set(pair.second_element)) {
                checker = false;
            }
        }

        try(FileWriter writer = new FileWriter("equal-not-equal.out", false))
        {
            if(checker){
                writer.write("Yes");
            }
            else{
                writer.write("No");
            }
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
