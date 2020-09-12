#include "base.h"

int main()
{
  std::ifstream fin;
  std::ofstream fout;
  json j{};
  
  fin.open("base.txt");
  if(fin.is_open())
  {
    fin >> j;
    fin.close();
  }

  Base base(j);
  while(true)
  {
    std::cout << "          CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n"
              << "          |||||||| WELCOME TO THE MAIN MENU ||||||||\n\n"
              << "1. Create new account\n"
              << "2. Update information of existing account\n"
              << "3. For transactions\n"
              << "4. Check the details of existing account\n"
              << "5. Removing existing account\n"
              << "6. View costomer's list\n"
              << "7. Exit\n\n"
              << "Enter your choise: ";
    char n{};
    std::cin >> n;
    if (n == '1')
      base.CreateNewAcc();
    else if (n == '2')
      base.EditInfo();
    else if (n == '3')
      base.TransactionMaker();
    else if (n == '4')
      base.PrintInfo();
    else if (n == '5')
      base.RemoveAcc();
    else if (n == '6')
      base.PrintList();
    else if (n == '7')
      break;
    else
      std::cout << "Wrong value\n";
  }
}
