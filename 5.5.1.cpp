#include <iostream>
#include <vector>
#include <thread>
#include <future>


void find_min(const std::vector<int>& vec, int start, int end, std::promise<int> promise)
{
   int minIndex = start;

   for (int i = start + 1; i <= end; i++)
   {
      if (vec[i] < vec[minIndex])
      {
         minIndex = i;
      }
   }

   promise.set_value(minIndex);
}


void sort(std::vector<int>& vec)
{
   int n = vec.size();

   for (int i = 0; i < n - 1; i++)
   {
      std::promise<int> promise;
      std::future<int> future = promise.get_future();

      std::thread t(find_min, std::ref(vec), i, n - 1, std::move(promise));

      int minIndex = future.get();

      if (minIndex != i)
      {
         std::swap(vec[i], vec[minIndex]);
      }

      t.join();
   }
}

int main()
{
   std::vector<int> vec = { 64, 25, 12, 22, 11 };

   std::cout << "vec before sort: ";

   for (auto num : vec)
   {
      std::cout << num << " ";
   }

   std::cout << std::endl;

   sort(vec);

   std::cout << "vec after sort: ";

   for (int num : vec)
   {
      std::cout << num << " ";
   }

   std::cout << std::endl;

   return 0;
}
