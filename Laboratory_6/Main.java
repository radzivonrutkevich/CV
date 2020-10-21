package bank;

import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.net.PasswordAuthentication;
import java.util.Locale;

public class Main {
    public static Payments[] createBand() throws Exception {
        Payments[] band = new Payments[3];
        band[0] = new Payments( 378932,459873267,8743,913);
        band[1] = new Payments( 675982,639871111,9003,714);
        band[2] = new Payments(870911,300099999,8332,111);
        return band;
    }

    public static void main(String[] args){
        try(ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("info.dat")))
        {
            Payments obj_1 = new Payments(345631,459873210,5776,200);
            oos.writeObject(obj_1);
        }
        catch (Exception ex){
            System.out.println(ex.getMessage());
        }
        try {
            Connector con = new Connector("info.dat");
            con.write(createBand());
            Payments[] band = con.read();
            for ( Payments n : band ) {
                System.out.println( n.toString() );
            }
        }
        catch ( Exception e ) {
            System.err.println(e);
        }

    }
}
