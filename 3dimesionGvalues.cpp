#include <stdio.h>
#include <bits/stdc++.h>
#include <list>

using namespace std;

int const rows = 120;
int const cols = 120;
int const layers = 2;

int getValue(int l, int r, int c, int mat[layers][rows][cols]) {
    
    // initialize list to store the direct followers values
    list<int> MinimumExclude;
    // to the left
    for (int i = (r-1); i >= 0; i--){
        MinimumExclude.push_back(mat[l][i][c]);
    }
    // downward
    for (int i = (c-1); i >= 0; i--){
        MinimumExclude.push_back(mat[l][r][i]);
    }
    // to a deeper layer 
    for (int i = (l-1); i >= 0; i--){
        MinimumExclude.push_back(mat[i][r][c]);
    }

    int max = r;
    if(c > max){max = c;}
    if(l > max){max = l;}
    
    for(int i = 0; i <= max; i++){
        for(int j = (i+1); j <= max; j++){
           
            int z = i^j;
            
            if ((r - i) >= 0 && (c - j) >= 0 && (l-z) >= 0){
                MinimumExclude.push_back(mat[l - z][r - i][c - j]);
                        
            }
            if ((r - i) >= 0 && (c - z) >= 0 && (l-j) >= 0){
                MinimumExclude.push_back(mat[l - j][r - i][c - z]);   
                     
            }
            if ((r - j) >= 0 && (c - i) >= 0 && (l-z) >= 0){
                MinimumExclude.push_back(mat[l - z][r - j][c - i]);      
                    
            }
            if ((r - j) >= 0 && (c - z) >= 0 && (l-i) >= 0){
                MinimumExclude.push_back(mat[l - i][r - j][c - z]);   
                         
            }
            if ((r - z) >= 0 && (c - i) >= 0 && (l - j) >= 0){
 
                MinimumExclude.push_back(mat[l - j][r - z][c - i]);      
                
            }
            if ((r - z) >= 0 && (c - j) >= 0 && (l - i) >= 0){
                MinimumExclude.push_back(mat[l - i][r - z][c - j]);        
                 
            }
        }
    }

    MinimumExclude.sort();
    MinimumExclude.unique();
    
    int run = 0;
    for (list<int>::iterator it = MinimumExclude.begin(); it != MinimumExclude.end(); ++it) {
        if (run != *it){
             if ( l==0 && r ==1 & c ==1){
                cout<< "run = "<<run<<endl;
                cout<< "*it = "<<*it<<endl;

             }
            return run;
        }
        run++;
    }   
    
    return run;
}
// given diagonal and layer, return how many PP points skiped over it
int DiagonalSkiped(int mat[layers][rows][cols],  int z, int d){
    int count = 0; 
    int row = 0; 
    int col = row + d;

    // keep count pp's until the diagonal has a pp on it
    while (mat[z][row][col] != 0){

        // boolean variable to realize if the diagonal has been skipped
        bool PPbeforeCurrentCell = false;

        for(int i = 0; i < col; i++){
            if (mat[z][row][i]==0){
                PPbeforeCurrentCell = true;
            }
        }
        if(!PPbeforeCurrentCell){
            count++;
        }
        row++;
        col++;
    }
    return count;
}

// given row and layer, return how many diagonals p-position skiped

int PPSkip(int mat[layers][rows][cols],  int z, int r){

    // variable to count the skiped diadonals
    int count = 0;

    // for loop to ensure that the pp is not to the left of the main diagonal
    for(int i = 0; i < r; i++){
        if(mat[z][r][i] == 0){
            return -1;
        }
    }
    // variable to iterate the row r
    int pointer = r;

    // iterating the row to the right side
    while(mat[z][r][pointer]!=0){ 
        
        bool DiagonalEmptyUptoCurrentRow = true;

        int diagoanlLength = r;
        int i = 1;
        
        //iterating the diagonal all the way down
        while (i <= diagoanlLength){
            
            if (mat[z][r - i][pointer - i] == 0) {
                DiagonalEmptyUptoCurrentRow = false;
            }
            i++;
        }
        if (DiagonalEmptyUptoCurrentRow) {
            count++;
            
        }
        pointer++;          
    }
    return count;
}


int main() {

    // initialize 3D array
    int mat[layers][rows][cols];

    // initialize all elements to -1
        for (int z = 0; z < layers; z++) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    mat[z][i][j] = -1;
                }         
            }
        }

    // assign values
    for (int z = 0; z < layers; z++) {
        for (int i = 0; i < rows; i++) {
            for (int j = i; j < cols; j++) {

                // assign value only if its not assigned yet
                if (mat[z][i][j] == -1)  {
                     
                int value = getValue(z,i,j, mat); 

                mat[z][i][j] = value;        

                if(i < layers && j <rows && z< cols) {
                    mat[i][j][z] = value;
                }
                if(i < layers && z < rows && j < cols) {
                    mat[i][z][j] = value;
                }
                if(z < layers && j <rows && i< cols) {
                    mat[z][j][i] = value;
                }
                if(j < layers && i <rows && z< cols) {
                    mat[j][i][z] = value;
                }
                if(j < layers && z <rows && i< cols) {
                    mat[j][z][i] = value;
                }
                }                
            }         
        }
    }
    int i,j = 0;
    for ( i = 0; i < 15; ++i)
    {
        for ( j = 0; j < 15; ++j)
        {
            std::cout << mat[1][i][j] << ' ';
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 50; i++){
            cout <<"in row "<<i<< " the p- position skipped " <<PPSkip(mat, 2, i)<< " diagonals" <<endl;

    }
    // cout <<"diagonal 3 " <<DiagonalSkiped(mat, 1, 3) <<endl;

    return 0 ;
}
