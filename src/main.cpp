#include <iostream>
using namespace std;

int main(){
    bool end(false);
    string fin;
    while (not end){
        cout<<"Ecrivez 'fin'"<<endl;
        cin>>fin;
        end= fin=="fin";
    }
    cout<<"Fin de partie"<<endl;
    
    return 0;
}