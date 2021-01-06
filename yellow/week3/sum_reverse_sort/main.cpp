#include <iostream>
#include "test_runner.h"
#include "sum_reverse_sort.h"
int main() {
    std::cout<<Sum(3,4) << std::endl;
    std::cout<<Reverse("privet")<< std::endl;
    vector<int> kek = {3,5,1,0,-3};
    Sort(kek);
    for (int i = 0 ; i < kek.size(); i++)
    {
        cout <<kek[i]<< " ";
    }
    return 0;
}
