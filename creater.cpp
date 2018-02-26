#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

main(){
ofstream file("file.txt");
int n;
file << "integer" << " string" << " string" << " double" << endl;
file << "Key" << " TheFirstString" << " TheSecondString" << " SqrtOfKey" << endl;
cin >> n;
for(int i = 1; i <= n; i++){
    file << i << " String" << i << " TheEndOfTheLine" << i << " " << sqrt(i) << endl;
}
file.close();
}

