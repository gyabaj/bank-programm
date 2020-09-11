#include "base.h"

std::ofstream fout;

Base::Base():j{}{}
Base::Base(json js):j(js){}
Base::Base(const Base &b): j(b.j){}
Base::~Base(){}
void Base::CreateNewAcc() /// 1.
{
  std::string fNm{};
  std::string lNm{};
  int bYear{};
  int bMonth{};
  int bDay{};
  std::string accNum{};
  double balance{};

  std::cout << "\nPlease enter\n"
            << "first name: ";
  std::cin >> fNm;
  std::cout << "last name: ";
  std::cin >> lNm;
  std::cout << "birth date (YY MM DD): ";
  std::cin >> bYear >> bMonth >> bDay;
  std::cout << "account number: ";
  std::cin >> accNum;
  std::cout << "balance: ";
  std::cin >> balance;
  j[accNum] = { {"first name", fNm},
                {"last name", lNm},
                {"birth date", {bYear, bMonth, bDay}},
                {"balance", balance},
                {"account number", accNum} };
  fout.open("base.txt");
  fout << j;
  std::cout << "New account created successfully\n\n";
  fout.close();
}
void Base::EditInfo()///// 2.
{
  std::string accNum{};
  std::cout << "Please enter changing account number: ";
  std::cin >> accNum;
  bool notExist = true;
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    if (temp["account number"] == accNum)
      notExist = false;
  }
  if (notExist)
  {
    std::cout << "Tere is no matching account number\n\n";
    return;
  }
  std::string fNm{};
  std::string lNm{};
  int bYear{};
  int bMonth{};
  int bDay{};
  double balance{};
  bool dontChanged = true;
  while(true)
  {
    std::cout << "|||||||||||| Edit menu ||||||||||||\n\n"
              << "1. Edit name\n"
              << "2. Edit birth date\n"
              << "3. Edit balance\n"
              << "4. Exit\n\n";
    char n{};
    std::cin >> n;
    if(n == '1')
    {
      std::cout << "Please enter new first name: ";
      std::cin >> fNm;
      std::cout << "Please enter new last name: ";
      std::cin >> lNm;
      j[accNum]["first name"] = fNm;
      j[accNum]["last name"] = lNm;
      dontChanged = false;
    }
    else if(n == '2')
    {
      std::cout << "Please enter new birth year: ";
      std::cin >> bYear;
      std::cout << "Please enter new birth month: ";
      std::cin >> bMonth;
      std::cout << "Please enter new birth day: ";
      std::cin >> bDay;
      j[accNum]["birth date"] = { bYear, bMonth, bDay};
      dontChanged = false;
    }
    else if(n == '3')
    {
      std::cout << "Please enter new balance: ";
      std::cin >> balance;
      j[accNum]["balance"] = balance;
      dontChanged = false;
     }
     else if(n == '4')
       break;
     else
       std::cout << "Wrong value\n";
  }
  if(dontChanged)
    return;
  fout.open("base.txt");
  if(fout.is_open())
  {
    fout << j;
    fout.close();
    std::cout << "Account changed successfully\n";
  }
}
void Base::TransactionMaker()//// 3.
{
  std::string sender{};
  std::string recipient{};
  double amount{};
  double temp{};
  std::cout << "Please enter sender account number: ";
  std::cin >> sender;
  bool notExist = true;
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    if (temp["account number"] == sender)
      notExist = false;
  }
  if (notExist)
  {
    std::cout << "Tere is no matching sender account number\n\n";
    return;
  }
  notExist = true;
  std::cout << "Please enter recipient account number: ";
  std::cin >> recipient;
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    if (temp["account number"] == recipient)
      notExist = false;
  }
  if (notExist)
  {
    std::cout << "Tere is no matching recipient account number\n\n";
    return;
  }
  std::cout << "Please enter sending amount: ";
  std::cin >> amount;
  temp = j[sender]["balance"];
  temp -= amount;
  if(temp >= 0)
    j[sender]["balance"] = temp;
  else
  {
    std::cout << "There is not enough money on sending account " << sender << '\n';
    return;
  }
  temp = j[recipient]["balance"];
  temp += amount;
  j[recipient]["balance"] = temp;
  fout.open("base.txt");
  if(fout.is_open())
  {
    fout << j;
    fout.close();
    std::cout << "Transaction done successfully\n";
  }
}
void Base::PrintInfo()//// 4.
{
  std::string accNum{};
  std::cout << "Please enter account number: ";
  std::cin >> accNum;
  bool notExist = true;
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    if (temp["account number"] == accNum)
      notExist = false;
  }
  if (notExist)
  {
    std::cout << "Tere is no matching account number\n\n";
    return;
  }
  std::cout << "account number: " <<  j[accNum]["account number"] << "\n"
            << "first name:     " <<  j[accNum]["first name"] << "\n"
            << "last name:      " <<  j[accNum]["last name"] << "\n"
            << "birth date:     " <<  j[accNum]["birth date"] << "\n"
            << "balance:        " <<  j[accNum]["balance"] << "\n\n";
}
void Base::RemoveAcc()//// 5.
{
  std::string accNum{};
  std::cout << "Please enter removing account number: ";
  std::cin >> accNum;
  bool notExist = true;
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    if (temp["account number"] == accNum)
      notExist = false;
  }
  if (notExist)
  {
    std::cout << "Tere is no matching account number\n\n";
    return;
  }
  j.erase(j.find(accNum));

  fout.open("base.txt");
  if (fout.is_open())
  {
    fout << j;
    fout.close();
    std::cout << "The account removed successfully\n\n";
  }
}
void Base::PrintList()///// 6.
{
  for(json::iterator it = j.begin(); it != j.end(); ++it)
  {
    json temp = *it;
    std::cout << "account number: " <<  temp["account number"] << "\n"
              << "first name:     " <<  temp["first name"] << "\n"
              << "last name:      " <<  temp["last name"] << "\n"
              << "birth date:     " <<  temp["birth date"] << "\n"
              << "balance:        " <<  temp["balance"] << "\n\n";
  }
}

                                                                                                                 161,3         64%


                                                                                                                 105,3         48%

                                                   
