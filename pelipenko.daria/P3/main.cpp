#include <iostream>
#include <fstream>
#include <new>

namespace pelip
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
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: invalid number of arguments.\n";
    return 1;
  }

  const int typeArr = argv[1][0] - '0';
  if ((typeArr != 1 && typeArr != 2) || argv[1][1] != '\0')
  {
    std::cerr << "Error: first argument must be 1 or 2.\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Error: could not open input file.\n";
    return 2;
  }

  size_t n = 0;
  size_t m = 0;
  if (!(input >> n >> m))
  {
    std::cerr << "Error: could not read matrix dimensions.\n";
    return 2;
  }

  if (m != 0 && n > pelip::MAX_SIZE / m)
  {
    std::cerr << "Error: matrix is too large.\n";
    return 2;
  }

  int fixArr[pelip::MAX_SIZE];
  int* arr = nullptr;
  int* arrd = nullptr;

  if (typeArr == 1)
  {
    if (n * m > pelip::MAX_SIZE)
    {
      std::cerr << "Error: matrix does not fit in static array.\n";
      return 2;
    }
    arr = fixArr;
  }
  else if (typeArr == 2)
  {
    try
    {
      arrd = new int[n * m];
      arr = arrd;
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Error: not enough memory.\n";
      return 2;
    }
  }

  for (size_t i = 0; i < n * m; ++i)
  {
    if (!(input >> arr[i]))
    {
      delete[] arrd;
      std::cerr << "Error: could not read matrix elements.\n";
      return 2;
    }
  }

  std::ofstream output(argv[3]);
  if (!output.is_open())
  {
    delete[] arrd;
    std::cerr << "Error: could not open output file.\n";
    return 2;
  }

  const bool result = pelip::isUpperTriangular(arr, n, m);
  output << (result ? "true" : "false") << '\n';

  delete[] arrd;

  return 0;
}
