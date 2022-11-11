#include <iostream>
using namespace std;

char** reverse_concat (const char* sentences[], int num_of_sentence) {
    int i=0, j=0, k=0;
    char **newarr = new char*[num_of_sentence];
    for(i = 0; i < num_of_sentence ; i++ ) *(newarr+i) = new char[255]; 
    for(i = 0; i < num_of_sentence; i++ ) {
      j = 0;
      while(sentences[i][j++]) {}
      j--;
      while(--j >= 0) newarr[0][k++] = sentences[i][j];
    }
    newarr[0][k]=0; 
    for(i = 1 ; i < num_of_sentence; i++ ) { 
      for(j = 0; j < k; j++ ) {
        newarr[i][j] = newarr[0][j]; 
      }
      newarr[i][j] = 0;
    }
    return newarr;
 
}


int main() {
    //Example sentence
    const char* sentence[] = { "Hello World", "Hi World", "Heyo World" };
    int num_of_sentence = 3;
    char** p_result = reverse_concat(sentence, num_of_sentence);
    //Print result
    for (int i = 0; i < num_of_sentence; i++) {
     cout << p_result[i] << endl;
     }
    return 0;
}
