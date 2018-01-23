#include <CGAL/Combination_enumerator.h>
#include <iostream>
#include <vector>
#include <algorithm>

void print(std::vector<int>& v)
{
  for(int i=0; i<v.size(); ++i)
  {
    std::cout << v[i] << " ";
  }
}

int do_permutations(const int s, std::vector<int>& hs,
                    std::vector<std::vector<int>>& subsets)
{

  const int first = hs.front();
  const int last = hs.back();
  std::sort(hs.begin(), hs.end());

  std::vector<int> p1(s);
  std::vector<int> p2(hs.size() - s);

  CGAL::Combination_enumerator<int> permutations(s, first, last + 1);

  int p = 0;
  while(!permutations.finished())
  {
    for(int i=0; i<s; ++i)
    {
      p1[i] = permutations[i];
      ++p;
    }

    std::sort(p1.begin(), p1.end());    
    std::set_symmetric_difference(p1.begin(), p1.end(), hs.begin(), hs.end(), 
                                  std::back_inserter(p2));

    print(p1); std::cout << "--"; print(p2);

    subsets.push_back(p1);
    subsets.push_back(p2);
  }

}


int main()
{

  const int s = 1;
  std::vector<int> hs = {1, 2, 3};

  std::vector<std::vector<int>> phi;
  do_permutations(s, hs, phi);


  for(int i=0; i < phi.size(); ++i)
  {
    print(phi[i]);
    std::cout << std::endl;
  }


  return 0;
}
