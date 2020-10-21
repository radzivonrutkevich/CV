import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
	try(FileReader file = new FileReader("input.txt")){
        Scanner in= new Scanner(new File("input.txt"));
        long vertex_amount = in.nextLong();
        String binary = Long.toBinaryString(vertex_amount);
        try(FileWriter writer = new FileWriter("output.txt", false))
        {
            for(int i = binary.length() - 1; i > -1; i--){
                if(binary.charAt(i) == '1'){
                    writer.write(Long.toString(((binary.length() - 1) - i) )+'\n');
                }
            }
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
    }
	catch(IOException ex){
        System.out.println(ex.getMessage());
    }
    }
}
