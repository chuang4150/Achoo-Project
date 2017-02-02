#include <iostream> // standard input stream
#include <time.h> // time library for random function
 
 
 
 
using namespace std;
 
 
 
int set_ships(int **& matrix, int size, int num1)
{
    int num_elements_containing_ships = 0;
    num1 = num1*2; // each ship takes up two spaces, so times it by two
    srand(time(NULL)); // starts the randomizer
 
    while (num_elements_containing_ships != num1)
    {
        int x = rand() % size; // picks a size for x thats within the size
        int y = rand() % size; // picks a size for y thats within the size
 
        if (matrix[x][y]==0) //condition where the spot on the grid is empty
        {
            if (x != 0 && x!= size) // condition where the ships is not at the border
            {
                if(matrix[x+1][y] == 0)// condition where the location to the right is open
                {
                    matrix[x+1][y] = 1;//assigning a (half) ship there
                    matrix[x][y]=1; // assigning the other half of the ship. Ships are horizontal only.
                    num_elements_containing_ships += 2; //increasing the number of occupied spots by 2
 
                }
                else if (matrix[x-1][y]) //conditoin where the position left of the point is open
                {
                    matrix[x-1][y] = 1; //refer to above
                                        matrix[x][y]=1;
                                        num_elements_containing_ships += 2;
                }
 
            }
        }
    }
 
 
 
 
/* THIS FUNCTION WILL TAKE IN AS A PARAMETER THE BOARD, THE SIZE OF THE BOARD, AND THE NUMBER OF SHIPS.
 
THIS FUNCTION DOES 2 THINGS: 1) IT SETS UP THE BOARD. ALLOCATE YOUR MEMORY.
 
2) DISTINGUISH BETWEEN ELEMENTS IN THE BOARD THAT HAVE A BATTLESHIP AND DON’T HAVE A BATTLESHIP. LET’S ASSUME ALL SHIPS ARE OF SIZE 2 “PEGS” AND CAN ONLY BE PLACED ON THE BOARD VERTICALLY OR HORIZONTALLY, I.E. NOT DIAGONALLY. THUS... */
 
 
 
 
 
/*HOW WILL YOU DISTINGUISH BETWEEN ELEMENTS IN THE BOARD WITH A SHIP OR WITHOUT ONE? */
 
    return num_elements_containing_ships;
 
}
 
 
 
 
 
int main()
 
{
 
   int ** B;
 
   int size, num_ships, row, col;
 
   int num_hits=0;          //I’m a counter to determine how many of the
 
                           //ships you’ve hit
 
 
 
   cout << "***** Battleship *****" << endl;
 
   cout << "How many rows/columns is the board?";
 
   cin >> size;
 
 
 
/* CREATE THE BATTLESHIP BOARD AND SET ALL ELEMENTS TO 0*/
 
 
 
   cout << "A" << size << "x" << size << "board has been created.\n";
 
   do
   {
       cout << "How many ships? ";
       cin >> num_ships;
       cout <<"not enough room on the board"<< endl;
   }
   while (num_ships*2+1 >= size*size );
 
   B = new int *[size]; //pointing to the first element in the array
 
   for (int i=0; i<size; i++)
   {
       B[i] = new int [size]; //making the array two dimensional
    for (int j=0;j<size;j++)
    {
     B[i][j] = 0; //declaring all the spots in the array as zeros
    }
   }
 
   int num_hits_needed=set_ships(B,size,num_ships);
 
 
 
   while(num_hits!= num_hits_needed)
 
   {
 
     cout << "What row: "<< endl;
 
     cin >> row;
 
     cout << "What col: "<< endl;
 
     cin >> col;
     if (row < size && col < size)
     {
     if (B [row][col] == 1) //if the spot has a ship on it
     {
         B[row][col] = -1; // assinigng as -1 to indicate the user already hit the spot
         cout << "Hit!"<< endl;
         num_hits++; //increase the hit counter by 1
     }
     else if (B[row][col] == 0) //if the spot does not have a ship on it
        {
            cout <<"Miss!" << endl;
        }
        else
        {
            cout <<"Already Hit!" << endl;
        }
     }
 
/*DETERMINE IF IT’S A HIT. IF SO, UPDATE YOUR COUNTER & TELL USER.
 
TAKE INTO CONSIDERATION THE FACT THAT YOUR PLAYER MAY NOT BE THE BRIGHTEST... IF THE USER SELECTS THE SAME ROW/COLUMN OVER AND OVER, THIS SHOULD NOT ERRONEOUSLY REPORT TO THE USER THAT THEY ARE HITTING A NEW SHIP.*/
 
   }
 
 
 
   cout << "You sunk my battleships!" << endl;
 
for (int i=0;i<size;i++) //deleting the inner array
   {
    delete [] B [i];
   }
delete [] B; //deleting the outer array
/*CLEAN UP YOUR MEMORY*/
 
 
 
   return 1;
 
}