#pragma once
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

class Base
{
  private:
     json j{};

  public:
     Base();
     Base(json js);
     Base(const Base &b);
     ~Base();
     void CreateNewAcc();
     void EditInfo();
     void TransactionMaker();
     void PrintInfo();
     void PrintList();
     void RemoveAcc();
};
