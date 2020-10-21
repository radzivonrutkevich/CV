package triangle;

public abstract class Triangle
{

    Triangle( String...args ){

    }
    Triangle( String str )
    {

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
    }

    public abstract double Perimeter();
    public abstract double Area();

}
