#include "CGAL/Combination_enumerator.h"
#include <iostream>
#include <vector>

using namespace std;

void print(std::vector<int>& v)
{
	cout << "{";
	for(int i=0; i<v.size(); ++i)
	{
		cout << v[i];
		if( i < v.size() - 1)
			cout<<" ";
	}
	cout << "}";
}

void fill_all_indices(vector<int>& all, int first, int last)
{
	int i = 0;
	for(int v = first; v <= last; ++v)
	{
		all[i] = v;
		++i;
	}
	assert(i == last - first + 1);
  assert(all.size() == i);
}

unsigned int do_enumerations(const int k, const int first, const int last)
{

  unsigned int n(0);
  //cout << "Taking " << k << " distinct integers in the range [" << first << ", " << last << "]:\n";

  CGAL::Combination_enumerator<int> combi(k, first, last + 1);
  
  int range1 = k;
  int range2 = last - first + 1 - k;

  vector<int> pair1;
  pair1.resize(range1);
  vector<int> pair2;
  pair2.resize(range2);

  vector<int> all(last - first + 1);
  fill_all_indices(all, first, last);

  while( ! combi.finished() ) 
  {
      //cout << " {";
      for(int i = 0; i < k; ++i) 
      {
          //cout << combi[i];

           pair1[i] = combi[i];

          //if( i < k - 1 )
          //    cout << ' ';
      }
      //cout << '}';


      sort(pair1.begin(), pair1.end());
      sort(all.begin(), all.end());

      /*
      std::vector<int>::iterator it = 
        std::set_difference(pair1.begin(), pair1.end(), all.begin(), all.end(), pair2.begin());
        */

      //pair2.resize(it - pair2.begin());

      set_difference(pair1.begin(), pair1.end(), all.begin(), all.end(), back_inserter(pair2));

      print(pair1); cout << " "; print(pair2);
      cout << endl;
      
      ++n;
      ++combi;
  }
  //cout << endl << "Enumerated " << n << " combinations." << endl;

  return n;
}



int main()
{

    const int first(1), last(3);

    vector<int> s = {1 , 2 , 3};

    unsigned int N(0);
    for(const int k : s)
    {
    	unsigned int n = do_enumerations(k, first, last);
    	N += n;
    }

    cout << "Enumerated " << N << " combinations." << endl;



   


    return 0;
}
