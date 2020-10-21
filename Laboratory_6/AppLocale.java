package bank;

import java.util.Locale;
import java.util.ResourceBundle;

public class AppLocale {
    private static final String strMsg = "Msg";
    private static Locale loc = Locale.getDefault();
    private static ResourceBundle res =
            ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );

    static Locale get() {
        return AppLocale.loc;
    }

    static void set( Locale loc ) {
        AppLocale.loc = loc;
        res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
    }

    static ResourceBundle getBundle() {
        return AppLocale.res;
    }

    static String getString( String key ) {
        return AppLocale.res.getString(key);
    }
    public static final String CCnumber= "CCnumber";
    public static final String BAnumber ="BAnumber";
    public static final String creation="creation";
}
