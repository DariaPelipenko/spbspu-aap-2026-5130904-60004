#include <exception>
#include <iostream>
#include <stdexcept>

namespace pelipenko
{
  struct MaxEqualCounter
  {
    MaxEqualCounter():
      max_length_(0),
      length_(0),
      prev_(0)
    {}

    void operator()(long long curr)
    {
      if (length_ == 0)
      {
        length_ = 1;
        max_length_ = 1;
      }

      if (curr == prev_)
      {
        ++length_;
      }
      else
      {
        length_ = 1;
        prev_ = curr;
      }

      if (length_ > max_length_)
      {
        max_length_ = length_;
      }
    }

    int operator()() const
    {
      return max_length_;
    }

  private:
    int max_length_;
    int length_;
    long long prev_;
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
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
