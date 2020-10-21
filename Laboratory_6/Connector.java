package bank;

import java.io.*;

public class Connector {

    private final String filename;

    public Connector( String filename ) {
        this.filename = filename;
    }

    public void write( Payments[] band) throws IOException {
        FileOutputStream fos = new FileOutputStream (filename);
        try ( ObjectOutputStream oos = new ObjectOutputStream( fos )) {
            oos.writeInt( band.length );
            for (Payments payments : band) {
                oos.writeObject(payments);
            }
            oos.flush();
        }
    }

    public Payments[] read() throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(filename);
        try ( ObjectInputStream oin = new ObjectInputStream(fis)) {
            int length = oin.readInt();
            Payments[] result = new Payments[length];
            for ( int i = 0; i < length; i++ ) {
                result[i] = (Payments) oin.readObject();
            }
            return result;
        }
    }

}

