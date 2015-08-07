// CSE 331 HW8 Extra Credit
// Daniel Thompson
// A43550656
// To compile:
// make
// OR
// g++ -o LCS lcs.cpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

int main(int argc, char *argv[])
{
	// check to make sure there are the correct number of arguments
	if(argc!=3)
	{
		cout << "wrong number of arguments!" << endl;
		return 0;
	}
	
   	ifstream fin;		// input stream
   	vector<int> x, y;	// vectors x and y for first and second files
   	
   	// open first file and see if it opens properly
   	fin.open(argv[1]);
	if(!fin.is_open())
	{
		cout << argv[1] << " did not open properly!" << endl;
		return 0;
	}
	
	int inputNumber;
	
	// read through first file
	while(fin >> inputNumber)
		x.push_back(inputNumber);
	
	fin.close();
	
	// open second file and see if it opens properly
	fin.open(argv[2]);
	if(!fin.is_open())
	{
		cout << argv[2] << " did not open properly!" << endl;
		return 0;
	}
	
	// read through second file
	while(fin >> inputNumber)
		y.push_back(inputNumber);	
	
	fin.close();
	
        vector< vector<int> > m ( x.size()+1, vector<int> (y.size()+1) );
        vector< vector<int> > t ( x.size()+1, vector<int> (y.size()+1) );
        
        //Initialize matrix
        for(int i = 0; i<=x.size(); i++)
            m[i][0] = 0;
        
        for(int j = 0; j<=y.size(); j++)
            m[0][j] = 0;
        
        
        for(int i = 1; i<=x.size();i++){
            for(int j=1; j<=y.size(); j++){
                if(x[i-1] == y[j-1]){
                    m[i][j] = m[i-1][j-1] + 1;
                    t[i][j] = 0;
                } else {
                    if(m[i][j-1] > m[i-1][j]){
                        m[i][j] = m[i][j-1];
                        t[i][j] = 1;
                    } else {
                        m[i][j] = m[i-1][j];
                        t[i][j] = -1;
                    }
                }
            }
        }
        
        
        int a = x.size();
        int b = y.size();
        deque<int> output;
        
        while (a >= 1 && b >= 1){
            if(t[a][b] == 0){
                output.push_front(x[a-1]);
                a--;
                b--;
            } else if (t[a][b]==-1){
                b--;
            } else {
                a--;
            }
        }
        
        ostringstream oss;
        for(int i = 0; i<output.size(); i++){
            oss << output[i];
            if(i+1 < output.size())
                oss << " ";
        }
        
        cout << oss.str() << endl;
	return 0;
}
