package bank;

import java.io.Serializable;
import java.util.Date;

public class Payments implements Serializable {
    private final Date data;
    private final BankAccount ba;
    private final CreditCard cc;

    public Payments(int value_bank_account, int value_credit_card_number, int value_sumcc, int value_sumba)throws Exception{

        ba = new BankAccount(value_bank_account, value_sumba);
        cc = new CreditCard(value_credit_card_number, value_sumcc);
        data = new Date();
    }

    public String toString() {
        return new String(AppLocale.getString(AppLocale.CCnumber) + ": " + cc.getCredit_card_number() + " " +
                AppLocale.getString( AppLocale.BAnumber ) + ": " + ba.getBank_account()+ " " +
                AppLocale.getString( AppLocale.creation ) + ": " + data);
    }

}
