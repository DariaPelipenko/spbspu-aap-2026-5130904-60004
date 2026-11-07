#include <exception>
#include <iostream>
#include <stdexcept>

namespace pelipenko
{

  class MaxEqualCounter
  {
  public:
    MaxEqualCounter()
      : max_length(0),
        length(0),
        prev(0)
    {
    }

    void operator()(long long curr)
    {
      if (length == 0)
      {
        length = 1;
        max_length = 1;
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

      if (length > max_length)
      {
        max_length = length;
      }
    }

    int operator()() const
    {
      return max_length;
    }

  private:
    int max_length;
    int length;
    long long prev;
  };

}

int main()
{
  try
  {
    pelipenko::MaxEqualCounter counter;
    long long curr = 0;

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

      counter(curr);
    }

    std::cout << counter() << "\n";
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
