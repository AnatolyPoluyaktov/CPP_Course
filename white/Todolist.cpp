#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector< string > k (vector<vector <string> > v2,int razn,int siz){
    vector<string>v1;
    while(razn!=0){
     int i= siz-razn;
    v1.insert(end(v1), begin(v2[i]), end(v2[i]));
    --razn;
    }

    return v1;
}
int NumberOfDays(int a){

    switch ( a )
         {
            case 1:
               return 31;

            case 2:
               return 28;

            case 3:
               return 31;
            case 4:
               return 30;
            case 5:
               return 31;
            case 6:
               return 30;
            case 7:
               return 31;
            case 8:
               return 31;
            case 9:
               return 30;
            case 10:
               return 31;
            case 11:
               return 30;
            case 12:
               return 31;
         }
      return 0;
}
int main()
{
    int n;
    string command,bussines;
    int day;
    int mounth =1;
    cin >> n;
    vector<vector<string> > number_of_bussines(31);

    for(int i = 0;i < n;++i){

        //cout<<i<<" ";
        cin>> command;
        if(command == "ADD"){
            cin >> day >> bussines;
            number_of_bussines[day-1].push_back(bussines);

        }
        else if(command == "NEXT"){

            int current = NumberOfDays(mounth);
            if(mounth == 12)
                mounth=0;
            ++mounth;
            int next = NumberOfDays(mounth);

            if(next > current){
            number_of_bussines.resize(next);
            }
            else if(next <current){
                //cout<<"F";
                vector<string>l;
            l=k(number_of_bussines,current-next,current);

           // for(auto r:l)
              //  cout<<r<<" ";
            number_of_bussines.resize(next);


            for(int q = 0;q<l.size();++q){
                number_of_bussines[next-1].push_back(l[q]);

            }
            /*for(int z =0 ;z<next;++z){
                for(int f=0;f<number_of_bussines[z].size();++f){
                    if(number_of_bussines[z][f]!="")
                        cout<<number_of_bussines[z][f]<<" ";
                }
            }*/



            }

        }
        else if(command == "DUMP"){
            cin>>day;
            cout<<number_of_bussines[day-1].size()<<" ";
            for(int f=0;f<number_of_bussines[day-1].size();++f){
                if(number_of_bussines[day-1][f]!="")
                    cout<<number_of_bussines[day-1][f]<<" ";
            }
            cout<<endl;
        }

    }

    return 0;
}
/*
  4
  ADD 31 F
  ADD 30 A
  ADD 1 t
  NEXT
  */
