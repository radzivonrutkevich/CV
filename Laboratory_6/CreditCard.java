package bank;

import java.io.Serializable;
import java.util.Date;

public class CreditCard implements Serializable {
    private final int credit_card_number;
    private  int sum_on_cc;
    private boolean is_block = false;
    private final transient Date data;

    CreditCard(int value_credit_card_number, int value_ss)throws Exception{
        if(value_credit_card_number < 100000000 || value_credit_card_number > 999999999) {
            throw new Exception("Номер банковской карты должен содержать 9 цифр");
        }
        else {
            credit_card_number = value_credit_card_number;
        }
        if(value_ss <= 0){
            throw new Exception("Сумма на банковской карте должна быть больше нуля");
        }
        else{
            sum_on_cc = value_ss;
        }
        data = new Date();
    }

    public void block_cc(){
        this.is_block = true;
    }

    public void unblock_cc(){
        this.is_block = false;
    }

    public int getCredit_card_number(){
        return credit_card_number;
    }

    public void pay(int value_pay){
        if(this.sum_on_cc < value_pay){
            System.out.println("Превышен лимит кредита. Ваш счёт будет заблокирован.");
            this.block_cc();
        }
        else{
            this.sum_on_cc -= value_pay;
            System.out.println("Оплата прошла успешно.");
        }
    }
}
