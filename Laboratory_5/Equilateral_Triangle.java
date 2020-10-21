package triangle;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.lang.Math;

class Equilateral_Triangle extends Triangle implements
        Comparable<Equilateral_Triangle>,
        Iterable<String>, Iterator<String>
{

    public static final String[] names =
            {
                    "Side_1",
                    "Side_2",
                    "Angle",
                    "Color_circuit",
                    "Color_casting"
            };
    //String TEMPLATE="Side_1 = %d, Side_2 = %d, Color_circuit = %s, Color_casting = %s";
    public static String[] formatStr =  {
            "%-9s",   //
            "%-9s",   //
            "%-9s",   //
            "%-17s",    //
            "%-17s"    //
    };
    public static String getSortByName(int sortBy) {
        return Equilateral_Triangle.names[sortBy];
    }

    public static Comparator<Equilateral_Triangle> getComparator(int sortBy)
    {
        return new Comparator<Equilateral_Triangle> () {
            @Override
            public int compare(Equilateral_Triangle c0, Equilateral_Triangle c1) {
                return c0.areas[sortBy].compareTo( c1.areas[sortBy]);
            }
        };
    }
    private String[] areas = null;
    public int length() {
        return areas.length;
    }
    public String getArea( int idx ) {
        if ( idx >= length() || idx < 0 ) {
            throw new IndexOutOfBoundsException();
        }
        return areas[idx];
    }
    public void setArea( int idx, String value )
    {
        if ( idx >= length() || idx < 0 ) {
            throw new IndexOutOfBoundsException();
        }

        areas[idx] = value;
    }
    public Iterator<String> iterator() {
        reset();
        return this;
    }
    private int iterator_idx = 0;
    public void reset() {
        iterator_idx = 0;
    }
    public boolean hasNext() {
        return iterator_idx >= areas.length ? false: true;
    }
    public void remove() {
        //
    }
    public String next() {
        if ( iterator_idx < areas.length ) {
            return areas[iterator_idx++];
        }
        reset();
        return null;
    }

    public int compareTo( Equilateral_Triangle cy ) {
        return areas[0].compareTo( cy.areas[0] );
    }

    public String toString() {
        if ( areas == null ) {
            return " | | | | ";
        }
        String res = areas[0];
        for ( int i = 1; i < areas.length; i++ ) {
            res += "|" + areas[i];
        }
        return res;
    }
    private void setup( String[] args ) {

        areas = new String[names.length];
        int i = 0;
        for (; i < args.length; i++ ) {
            setArea( i, args[i] );
        }
        while ( i < names.length ) {
            areas[i++] = "";
        }
    }
    Equilateral_Triangle ( String str )
    {
        super(str);
        int num = 1, idx = 0, idxFrom = 0;
        while (( idx = str.indexOf( '|', idxFrom ))!= -1 )
        {
            idxFrom = idx + 1;
            num++;
        }

        String[] args = new String[num];

        idx = 0; idxFrom = 0; num = 0;
        while (( idx = str.indexOf( '|', idxFrom ))!= -1 )
        {
            args[num++] = str.substring( idxFrom, idx );
            idxFrom = idx + 1;
        }
        args[num] = str.substring( idxFrom );
        setup( args );

    }
    Equilateral_Triangle( String...args ){
        setup( args );
    }

    @Override
    public double Perimeter()
    {

        double perimeter=0;
        double thirdside = Math.sqrt((Double.parseDouble(this.areas[0]) *  Double.parseDouble(this.areas[0])) + (Double.parseDouble(this.areas[1]) *  Double.parseDouble(this.areas[1])) - 2 * Double.parseDouble(areas[0]) * Double.parseDouble(areas[1]) * Math.cos(Double.parseDouble(areas[2])));
        perimeter+= Double.parseDouble(this.areas[0]) + Double.parseDouble(this.areas[1]) + thirdside ;

        return perimeter;
    }

    @Override
    public double Area()
    {
        double area=0;

        area=Double.parseDouble(this.areas[0])*Double.parseDouble(this.areas[1])*(Math.sin(Double.parseDouble(this.areas[2]))) / 2;

        return area;
    }


    private static String format( Iterable<String> what ) {
        String result = "";
        int idx = 0;
        for( String str : what ) {
            result += String.format( formatStr[idx++], str );
        }
        return result;
    }

    public static String format() {
        return Equilateral_Triangle.format( Arrays.asList(Equilateral_Triangle.names ));
    }

    public static String format( Equilateral_Triangle cn ) {
        return Equilateral_Triangle.format(((Iterable<String>) cn ));
    }

}
