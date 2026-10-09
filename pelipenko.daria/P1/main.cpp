#include <exception>
#include <iostream>
#include <stdexcept>

namespace pelipenko
{

  int findMaxRun()
  {
    long long prev = 0;
    long long curr = 0;
    bool first = true;
    int length = 0;
    int maxLength = 0;

    while (true)
    {
      if (!(std::cin >> curr))
      {
        throw std::invalid_argument("Input is not a sequence of integers");
      }

      if (curr == 0)
      {
        break;
      }

      if (first)
      {
        prev = curr;
        length = 1;
        maxLength = 1;
        first = false;
        continue;
      }

      if (curr == prev)
      {
        ++length;
      }
      else
      {
        length = 1;
        prev = curr;
      }

      if (length > maxLength)
      {
        maxLength = length;
      }
    }

    return maxLength;
  }

} // namespace pelipenko

int main()
{
  try
  {
    const int answer = pelipenko::findMaxRun();
    std::cout << answer << "\n";
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
