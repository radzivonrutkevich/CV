package bank;

import java.io.Serializable;
import java.util.Date;

public class BankAccount implements Serializable {
    private final int bank_account;
    private int sum_on_bank_account;
    private final transient Date data;

    BankAccount(int value_bank_account, int value_sumba)throws Exception{
        if(value_bank_account < 100000 || value_bank_account > 999999){
            throw new Exception("Номер банковского счёта должен содержать 6 цифр.");
        }
        else {
            bank_account = value_bank_account;
        }
        if(value_sumba <= 0){
            throw new Exception("Сумма на банковском счёте не может быть меньше 0");
        }
        else {
            sum_on_bank_account = value_sumba;
        }
        data = new Date();
    }

    public int getBank_account() {
        return bank_account;
    }

    public void transfer (int sum, BankAccount o) throws Exception{
        if(sum <= 0){
            throw new Exception("Сумма перевода должна быть больше 0.");
        }
        else {
            if (sum <= this.sum_on_bank_account) {
                sum_on_bank_account -= sum;
                o.sum_on_bank_account += sum;
                System.out.println("Перевод прошёл успешно.");
            } else {
                System.out.println("Недостаточно денег на счёте.");
            }
        }
    }

    public void null_bank_account(){
        this.sum_on_bank_account = 0;
    }
}
