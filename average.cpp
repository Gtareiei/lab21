#include<iostream>
#include<cstdlib>
using namespace std ;
int main (int argc , char * argv[]) {
    double sum = 0 ;
    double ave ;
    if(argc == 1 ) {
        cout<<"Please input numbers to find average. \n" ;       
    }
    else {
        for(int i = 1 ; i < argc ; i++) {
            sum += atof(argv[i] ) ;
        }   
    
    ave = sum/(argc-1) ;
    cout<<"---------------------------------\n" ;
    cout<<"Average of "<< argc - 1  << " numbers = "<< ave <<endl ;
    cout<<"---------------------------------\n" ;
    }

} 
