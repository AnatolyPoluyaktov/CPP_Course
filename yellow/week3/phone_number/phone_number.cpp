#include "phone_number.h"

#include <sstream>
#include <stdexcept>

#include <iostream>

 PhoneNumber::PhoneNumber(const string &international_number) {
     if (international_number.empty())
     {
         throw std::invalid_argument(international_number);
     }
     istringstream ss(international_number);
     char first;
     std::string X;
     std::string Y;
     std::string Z;
     ss >> first;
     if (first != '+') {

         throw std::invalid_argument("Wrong date format: " + international_number);
     }
     std::getline(ss,country_code_, '-');
     if (country_code_.empty() ) {
        throw std::invalid_argument(international_number);
     }
     std::getline(ss,city_code_, '-');

     if (city_code_.empty() ) {
         throw std::invalid_argument(international_number);
     }
     std::getline(ss,local_number_);
      if (local_number_.empty() || ss.peek() != EOF)
      {
          throw std::invalid_argument(international_number);
      }

}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
    return  "+" + country_code_ + "-" + city_code_+ "-" + local_number_;
}
