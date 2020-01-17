#include "head.h"

int main(){
    ifstream triangles("Triangles.bin", ios::binary);
    ofstream results("Results.txt", ios::out | ios::trunc);
    if(!triangles.is_open() || !results.is_open()){
        cout<<"Can't open file. Check it please!"<<endl;
        return 0;
    }
    cout<<"Successfull opened the file.."<<endl;

    int a = 0, b = 0, c = 0, n = 0;
    triangles.read(reinterpret_cast<char*>(&n), sizeof(char));
    cout << n << endl;
    float *buffer = new float[n*3];
    for(int i = 0; i < n*3; i++){
        triangles.read(reinterpret_cast<char*>(&buffer[i]), sizeof(float));
    }
    double *result = new double[3*n];
    cout<<"Successfull read from file.."<<endl;

    for(int i = 0; i < n*3; i += 3){
        a = i;
        b = i + 1;
        c = i + 2;
        find_tg(buffer[a], buffer[b], buffer[c], &result[i]);
    }

    for(int i = 0; i < n * 3; i++){
        results << result[i] << endl;
    }
}