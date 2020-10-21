package tourism;

import java.io.Serializable;
import java.util.Scanner;

public class Tourism implements Serializable {
    private String name_of_tour = null;
    private String name_of_client = null;
    private int price_for_day = 0;
    private int amount_of_days = 0;
    private int fair = 0;
    private int cost_of_travel = 0;
    public static Tourism read(Scanner fin ) {
        Tourism bill = new Tourism();
        bill.name_of_tour = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        bill.name_of_client = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        bill.price_for_day = Integer.parseInt(fin.nextLine());
        if ( ! fin.hasNextLine()) return null;
        bill.amount_of_days = Integer.parseInt(fin.nextLine());
        if ( ! fin.hasNextLine()) return null;
        bill.fair = Integer.parseInt(fin.nextLine());
        if ( ! fin.hasNextLine()) return null;
        bill.cost_of_travel = Integer.parseInt(fin.nextLine());
        return bill;
    }

    Tourism(){}

    public String toString() {
        return "Название тура: " + name_of_tour + "|" +
                "Имя клиента: " + name_of_client + "|" +
                "Цена за день: " + price_for_day + "|" +
                "Количество дней: " + amount_of_days + "|" +
                "Цена проезда : " + fair + "|" +
                "Цена путешествия: " + cost_of_travel;
    }

}
