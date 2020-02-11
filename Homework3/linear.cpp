//bool somePredicate(double x)
//{
//    return x < 0;
//} FOR TESTING PURPOSES

// Return true if the somePredicate function returns false for at
    // least one of the array elements; return false otherwise.
  bool anyFalse(const double a[], int n)
  {
      if (n <= 0)
          return false; //No elements were false
      if (n == 1)
          return somePredicate(a[0]); //Return the bool value of the predicate
      return anyFalse(a+1, n-1); //Recursion statement
  }

    // Return the number of elements in the array for which the
    // somePredicate function returns true.
  int countTrue(const double a[], int n)
  {
      if (n <= 0) //Case if falls off edge
          return 0;
      if (n == 1) //Base case
      {
          if (somePredicate(a[0])) //If true, return 1 to count up by one
              return 1;
          else
              return 0;
      }
      int first = countTrue(a, n/2);
      int second = countTrue(a+n/2, n-n/2); //dIvIDe aNd COunQUeR the array
      return first + second;
  }

    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
  int firstTrue(const double a[], int n)
  {
      if (n <= 0)
          return -1; //Nothing true
      if (n == 1)
      {
          if (!somePredicate(a[0])) //If false, return 0
              return 0;
      }
      int position = firstTrue(a+1, n-1); //Obtain the value of the first true value
      if (position != -1) //If we ran into a true value, return its position
          return 1 + position;
      else
          return -1; //If nothing was true, return -1
  }

    // Return the subscript of the smallest element in the array (i.e.,
    // return the smallest subscript m such that a[m] <= a[k] for all
    // k from 0 to n-1).  If the function is told to examine no
    // elements, return -1.
  int positionOfSmallest(const double a[], int n)
  {
      if (n <= 0)
          return -1; //No elements
      if (n == 1)
          return 0;
      int position = positionOfSmallest(a+1, n-1);
      if (a[0] <= a[position+1]) //Check smallest value against first value
          return 0; //Return the first array position if it is the smallest
      else
          return position+1; //Otherwise, return the array position of the smallest value
  }

    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not contain
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    10 50 40 20 50 40 30
    // then the function should return true if a2 is
    //    50 20 30
    // or
    //    50 40 40
    // and it should return false if a2 is
    //    50 30 20
    // or
    //    10 20 20
  bool contains(const double a1[], int n1, const double a2[], int n2)
  {
      if (n1 <= 0)
          return false;
      if (n2 <= 0)
          return true; //As specified in specs
      if (a1[0] == a2[0])
      {
          if (contains(a1+1, n1-1, a2+1, n2-1)) //Find the value
              return true; //Return true if we found it
          else if (contains(a1+1, n1-1, a2, n2)) //Find the value in other positions
              return true; //Return true if we found it
      }
      return false; //The array did not contain any element in the other array
  }
