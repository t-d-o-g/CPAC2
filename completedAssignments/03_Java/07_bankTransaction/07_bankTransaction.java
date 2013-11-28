public class CAT
{  public static void main(String[] args)
   {   CheckingAccount account = new CheckingAccount(0);
       ConsoleReader console = new ConsoleReader(System.in);
       int x, choice; 
       double amount; 

       do
       {
          System.out.println("   Menu options		");
          System.out.println();
          System.out.println("   1)  Check Balance	");
          System.out.println("   2)  Make Deposit	");
          System.out.println("   3)  Make Withdraw	");
          System.out.println("   4)  Quit		");
          System.out.println();
          System.out.print("   Enter a choice:		"); 

          choice = console.readInt(); 

          if (choice == 1)
          {
             System.out.println("   Your balance is $" + account.getBalance());
             System.out.println();
          }  

          else if (choice == 2)
          {
             System.out.print("   Enter deposit amount: ");            
             amount = console.readInt();
             System.out.println("   The fee is $" + account.checkFees());
             System.out.println();
             if (amount >= (account.getBalance() + account.checkFees()))
             {
                account.deposit(amount);
                account.deductFees();
             }
             else
             {
                System.out.println("   Insufficient Funds to make this transaction.");
                System.out.println();
             }
          }

          else if (choice == 3)
          {
             System.out.print("   Enter withdraw amount: ");
             amount = console.readInt();
             System.out.println("   The fee is $" + account.checkFees());
             System.out.println();
             if ((amount + account.checkFees()) <= account.getBalance())
             {
                account.withdraw(amount);
                account.deductFees();
             }
             else
             {  System.out.println("   Insufficient Funds to make this transaction.");
                System.out.println();
             }
          }
       }
       while (choice != 4); 
   }
}