#include <iostream>
#include <fstream>
#include <new>
#include <stdexcept>
#include <cstddef>
#include <exception>

namespace pelipenko
{
  const size_t MAX_SIZE = 10000;

  bool isUpperTriangular(const int* arr, const size_t n, const size_t m)
  {
    if (n != m)
    {
      return false;
    }

    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < m; ++j)
      {
        if (i > j && arr[i * m + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  void readMatrix(std::istream& input, int* arr, const size_t n, const size_t m)
  {
    for (size_t i = 0; i < n * m; ++i)
    {
      if (!(input >> arr[i]))
      {
        throw std::logic_error("Not correct matrix elements");
      }
    }
  }
}

int main(int argc, char* argv[])
{
  int* dynamic_arr = nullptr;

  try
  {
    if (argc != 4)
    {
      throw std::invalid_argument("Not correct arguments count");
    }

    if (argv[1][0] == '\0' || (argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
    {
      throw std::invalid_argument("First parameter must be 1 or 2");
    }
    const int type_arr = argv[1][0] - '0';

    std::ifstream input(argv[2]);
    if (!input.is_open())
    {
      throw std::logic_error("Could not open input file");
    }

    size_t n = 0;
    size_t m = 0;
    if (!(input >> n >> m))
    {
      throw std::logic_error("Could not read dimensions");
    }

    if (m != 0 && n > pelipenko::MAX_SIZE / m)
    {
      throw std::logic_error("Matrix is too large");
    }

    int fixed_arr[pelipenko::MAX_SIZE];
    int* arr = nullptr;

    if (type_arr == 1)
    {
      if (n * m > pelipenko::MAX_SIZE)
      {
        throw std::logic_error("Matrix does not fit in static array");
      }
      arr = fixed_arr;
    }
    else
    {
      dynamic_arr = new int[n * m];
      arr = dynamic_arr;
    }

    pelipenko::readMatrix(input, arr, n, m);

    std::ofstream output(argv[3]);
    if (!output.is_open())
    {
      throw std::logic_error("Could not open output file");
    }

    const bool result = pelipenko::isUpperTriangular(arr, n, m);
    output << (result ? "true" : "false") << '\n';

    delete[] dynamic_arr;
    dynamic_arr = nullptr;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    delete[] dynamic_arr;
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    delete[] dynamic_arr;
    return 2;
  }

  return 0;
}
