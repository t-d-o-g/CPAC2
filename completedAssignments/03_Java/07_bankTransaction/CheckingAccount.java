public class CheckingAccount extends BankAccount
{  public CheckingAccount(int initialBalance)
   {  // construct superclass
      super(initialBalance);
      
      // initialize transaction count
      transactionCount = 1; 
   }

   public void deposit(double amount) 
   {  transactionCount++;
      // now add amount to balance 
      super.deposit(amount); 
   }
   
   public void withdraw(double amount) 
   {  transactionCount++;
      // now subtract amount from balance 
      super.withdraw(amount); 
   }

   public void deductFees()
   {  if (transactionCount >= FREE_TRANSACTIONS)
      {  double fees = TRANSACTION_FEE *
            (transactionCount - FREE_TRANSACTIONS);
         super.withdraw(fees);
      }
   }

   public double checkFees()
   { double fee;
     fee = 0; 
     if (transactionCount >= FREE_TRANSACTIONS)
      {     fee = TRANSACTION_FEE *
            ((transactionCount + 1) - FREE_TRANSACTIONS);
      }
      return fee;
   }

   private int transactionCount;

   private static final int FREE_TRANSACTIONS = 3;
   private static final double TRANSACTION_FEE = 2.0;
}
