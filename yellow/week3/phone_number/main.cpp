#include <iostream>
#include "phone_number.h"
int main() {
PhoneNumber kek{"7-495-111-22-33"};
 cout << kek.GetCountryCode();
 cout << kek.GetCityCode();
 cout << kek.GetLocalNumber();
 cout << kek.GetInternationalNumber();


    return 0;


}
