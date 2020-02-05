#include <iostream>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;



int rfibonacci (int n) {
  if (n == 0) {
    return 0;
  }
  else if (n == 1) {
    return 1;
  }
  else {
    return rfibonacci(n-1) % 65536 + rfibonacci(n-2) % 65536;
  }
}


int ifibonacci (int n) {

  vector<int> array;
  array.push_back(0);
  array.push_back(1);

  for (int i = 2; i <= n; i++){
    array.push_back(array.at(i-1) + array.at(i-2));
  }

  return array.at(n);

}

int** matrixMultiplier (int a[2][2], int b[2][2]){

  int sizeOfSquareMatrix = 2;
  int** c = new int*[sizeOfSquareMatrix];
  for (int i = 0; i < sizeOfSquareMatrix; i++) {
    c[i] = new int[sizeOfSquareMatrix];
  }
  for (int i = 0; i < sizeOfSquareMatrix; i++)
  {
      for (int j = 0; j < sizeOfSquareMatrix; j++)
      {
          c[i][j] = 0;
          for (int k = 0; k < sizeOfSquareMatrix; k++)
          {
              c[i][j] += (a[i][k] * b[k][j]) % 65536;
          }
      }
  }
  return c;

}



int mfibonacci (int n) {
  int matrix[2][2] = {  {0, 1}, {1, 1} };
  int** array;
  for (int i = 0; i < n-1; i++) {
    if (i > 0) {
      int matrix2[2][2] = { {array[0][0], array[0][1]}, {array[1][0], array[1][1]} };
      array = matrixMultiplier(matrix, matrix2);
    }
    else {
      array = matrixMultiplier(matrix, matrix);
    }
  }
  return array[0][1] ;

}



int main(){

    auto start = high_resolution_clock::now();
    int num = rfibonacci(1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "recursive: " + std::to_string(num) << endl;
    cout << std::to_string(duration.count()) + " microseconds" << endl;

    start = high_resolution_clock::now();
    num = ifibonacci(1000000000);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "iterative: " + std::to_string(num) << endl;
    cout << std::to_string(duration.count()) + " microseconds" << endl;

    start = high_resolution_clock::now();
    num = mfibonacci(1000);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "matrix: " + std::to_string(num) << endl;
    cout << std::to_string(duration.count()) + " microseconds" << endl;


    return 0;
}
