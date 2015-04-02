/******************************************************************************
 * NAME: BYRON JAY INOCENCIO
 *       CAITLIN CAGAMPAN
 * 
 * DATE: 1/28/2015
 * 
 * FILE: benchtree.cpp
 * 
 * OVERVIEW: Provides a way to display statistical information regarding 
 * average comparisons for the data structures RST, BST, and Red-Black
 * Trees (set). The user gives 4 command line parameters 
 *         
 *         1) a valid data structure to be tested: "bst", "rst" or "set"
 *         2) specification of sorting : "sorted", "shuffled"
 *         3) the maximum container size: an integer value
 *         4) the amount of iterations to be tested: an integer value
 * 
 * Given these 4 parameters, the data structure will be tested and a table
 * displaying the average amount of comaprisons will be displayed for each
 * container size over the amount of iterations given.
 *
 * 
 * ASSIGNMENT NUMBER: PA2
 *
 *
******************************************************************************/

#include "RST.hpp"
#include "BST.hpp"
#include <set>
#include <iostream>
#include "countint.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

/* Prints out the information of the benchmarking arguments to standard output
 *
 * Input
 *    dataStructure - the container for benchmarking, either BST, RST, or set
 *    sortType - the inputted ordering type, either sorted or shuffled
 *    maxSize - maximum size of the container to be built
 *    iteration - amount of runs that will be done and averaged over
 *
 */ 
void displayResults(string dataStructure, string sortType, int maxSize, 
                    int iteration){

    const char separator = ' ';   //space set between columns
    const int  nWidth = 10;       //width for N column
    const int  avgWidth = 15;     //width for avgcomps column
    const int  stdevWidth = 15;   //width for stdev column

    //prints out the specified information for benchmarking
    cout<< endl;
    cout<< "# Benchmarking average number of comparisons ";
    cout<< "for successful find" << endl;
    cout<< "# Data structure: " << dataStructure << endl;
    cout<< "# Data: " << sortType << endl;
    cout<< "# N is power of 2, minus 1, from 1 to " << maxSize << endl;
    cout<< "# Averaging over " << iteration << " runs for each N" << endl;
    cout<< "#" <<endl;

    //sets up the table headers
    cout<< left << setw(nWidth) << setfill(separator) << "#   N";
    cout<< left << setw(avgWidth) << setfill(separator) << "   avgcomps";
    cout<< left << setw(stdevWidth) << setfill(separator) << "stdev"; 
    cout<< endl;       
    
}


/* Computes the benchmarking calculations to be analyzed, including average
 * comparisons and standard deviations.
 *
 * Input
 *    dataStructure - the container for benchmarking, either BST, RST, or set
 *    isSorted - true if the sortType is sorted, false if it's shuffled
 *    maxSize - maximum size of the container to be built
 *    iteration - amount of runs that will be done and averaged over
 *
 */ 
void makeResults(string dataStructure, bool isSorted, 
                        int maxSize, int iteration){
    
    int n = 1;  //number of keys in the structure 
    int x = 1;  //counter to increment the calculations for n

    const char separator = ' ';  //space set between columns
    const int  nWidth = 5;       //width for N column   
    const int  avgWidth = 15;    //width for avgcomps column
    const int  stdevWidth = 15;  //width for stdev column

    //runs for each N amount of nodes until the max size of the container
    while(n <= maxSize){
     
      double total = 0;            //stores sum of average comparisons
      double totalAvg = 0;         //stores overall average of comparisons
      double square = 0;           //stores square of comparisons
      double totalSquare = 0;      //stores sum of squares
      double totalSquareAvg = 0;   //stores average of squared comparisons
      double stdev = 0;            //stores standard deviations

      //runs each iteration 
      for(int count = 0; count<iteration; count++){
         
        std::vector<countint> v; //initializes our vector
        v.clear();               

        //adds maxSize amount of data to our vector
        for(int i=0; i< n; ++i){
           v.push_back(i); 
        }

        //checks if we need to shuffle the vector
        if(!isSorted)
            std::random_shuffle(v.begin(),v.end());
        
        if(dataStructure == "rst"){
             
             //creates a new RST container
             RST<countint>* r = new RST<countint>();
                        
             std::vector<countint>::iterator vit = v.begin();
             std::vector<countint>::iterator ven = v.end();

             //iterates through our vector and inserts into container
             for(vit = v.begin(); vit != ven; ++vit)
                 r->insert(*vit);
            
             countint::clearcount();

             //finds each item in the container
             for(vit = v.begin(); vit != ven; ++vit)
                r->find(*vit);

             delete r;
             r = NULL;
        }

        else if(dataStructure == "bst"){
             BST<countint>* b = new BST<countint>();
                       
             //creates a new RST container 
             std::vector<countint>::iterator vit = v.begin();
             std::vector<countint>::iterator ven = v.end();

             //iterates through our vector and inserts into container
             for(vit = v.begin(); vit != ven; ++vit)
                 b->insert(*vit);

             countint::clearcount();

             //finds each item in the container
             for(vit = v.begin(); vit != ven; ++vit)
                b->find(*vit);

             delete b;
             b = NULL;
        }

        else if(dataStructure == "set"){
             set<countint>* s = new set<countint>();
            
             //creates a new RST container 
             std::vector<countint>::iterator vit = v.begin();
             std::vector<countint>::iterator ven = v.end();

             //iterates through our vector and inserts into container
             for(vit = v.begin(); vit != ven; ++vit)
                 s->insert(*vit);

             countint::clearcount();

             //finds each item in the container
             for(vit = v.begin(); vit != ven; ++vit)
                s->find(*vit);

            delete s;
            s=NULL; 
        }
 
        //catches erroneous input. this block should never run 
        else{
             cout<<"ERROR: INVALID DATASTRUCTURE. TERMINATING" << endl;
             exit(0);
        }

        //get average amount of comparisons
        double avgcomps = countint::getcount()/(double)n ;        
        
        //sum the total amount of comparisons
        total = total + avgcomps;

        //square average amount of comparisons
        square = pow(avgcomps,2); 

        //sum the total amount of squared comparisons
        totalSquare = totalSquare + square;

     }
        //overall average number of comparisons
        totalAvg = total/iteration;

        //overall average squared number of comparisons
        totalSquareAvg = totalSquare/iteration;

        stdev = sqrt(abs(totalSquareAvg-(pow(totalAvg,2))));

        //fills in the rest of the table with data 
        cout << right <<setw(nWidth) << setfill(separator)<< n;
        cout << right <<setw(avgWidth) <<setfill(separator)<< totalAvg ;
        cout << right <<setw(stdevWidth) <<setfill(separator)<< stdev<<endl;
        
        //calculates N pattern 
        x++;
        n = (pow(2,x)-1);
        
    }
}


int main(int argc, char* argv[]) {

    srand(time(NULL));
 
   //catastrophic check for the right amount of arguments
   if(argc != 5){
     cout<<"error: incorrect amount of arguments\n";
     return 0;
   }
  
   /*stores command line arguments as strings*/

   string arg1(argv[1]);          // stores a valid datastructure argument
   string arg2(argv[2]);          // stores a valid ordering argument
   int maxSize = atoi(argv[3]);   // stores the size char as an int
   int iteration = atoi(argv[4]); // stores the iteration char as an int
   bool isSorted = false;         // true if the ordering is sorted, 
                                  // false if shuffled
  
   /*validates for correct user input for data structure */
   if(!(arg1 == "rst" || arg1 == "bst" || arg1 == "set" )){
      cerr<<"error: not a valid data structure to be tested \n";
      return 0;
    }
   
   if(arg1 == "rst"){

       /*case for inserted in sorted order */
       if(arg2 == "sorted"){
          displayResults(arg1,arg2,maxSize,iteration);
          isSorted = true;
          makeResults(arg1,isSorted,maxSize,iteration);
       }
       
       /*case for insertion in shuffled order */
       else if(arg2 == "shuffled"){
          displayResults(arg1,arg2,maxSize,iteration);
          makeResults(arg1,isSorted,maxSize,iteration);
   
       }

       /*catastrophic case*/
       else{
          cerr<<"ERROR: not valid input"; //catastrophic error, 
          return 0;                       //should not be reached
       }
   }

   else if(arg1 =="bst"){
       /*case for inserted in sorted order */
       if(arg2 == "sorted"){
          displayResults(arg1,arg2,maxSize,iteration); 
          isSorted = true;
          makeResults(arg1,isSorted,maxSize,iteration);
                   
       }
       
       /*case for insertion in shuffled order */
       else if(arg2 == "shuffled"){
          displayResults(arg1,arg2,maxSize,iteration); 
          makeResults(arg1,isSorted,maxSize,iteration);
    
       }

       /*catastrophic case*/
       else{
          cerr<<"ERROR: not valid input"; //catastrophic error, 
          return 0;                       //should not be reached
       }


   }

   else if(arg1 =="set"){
       /*case for inserted in sorted order */
       if(arg2 == "sorted"){
          displayResults(arg1,arg2,maxSize,iteration);
          isSorted = true;
          makeResults(arg1,isSorted,maxSize,iteration);

       }
       
       /*case for insertion in shuffled order */
       else if(arg2 == "shuffled"){
          displayResults(arg1,arg2,maxSize,iteration); 
          makeResults(arg1,isSorted,maxSize,iteration);
      
       }

       /*catastrophic case*/
       else{
          cerr<<"ERROR: not valid input"; //catastrophic error, 
          return 0;                       //should not be reached
       }
   }

   else{
     /*catastrophic error. should not be reachable */
     cerr<<"ERROR: INVALID ARGUMENT."; 
   }  
  
}    
