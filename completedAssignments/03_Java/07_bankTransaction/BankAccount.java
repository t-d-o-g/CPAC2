public class BankAccount
{  public BankAccount()
   {  balance = 0;
   }

   public BankAccount(double initialBalance)
   {  balance = initialBalance;
   }
 
   public void deposit(double amount) 
   {  balance = balance + amount;
   }

   public void withdraw(double amount) 
   {  balance = balance - amount;
   }

   public double getBalance()
   {  return balance; 
   }
   
   public void transfer(BankAccount other, double amount)
   {  withdraw(amount);
      other.deposit(amount);
   }

   private double balance; 
}
