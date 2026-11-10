#include <iostream>
#include <cstddef>
#include <cctype>

namespace pelipenko
{
  void getStr(std::istream& in, char* buf, std::size_t max_size);
  std::size_t getLen(const char* str);
  void getCommonLetters(const char* str1, const char* str2, char* out);
}

int main()
{
  const std::size_t MAX_SIZE = 1000;
  char str1[MAX_SIZE] = {0};
  char res[MAX_SIZE] = {0};
  const char* const str2 = "def_ghk";

  pelipenko::getStr(std::cin, str1, MAX_SIZE);

  if (pelipenko::getLen(str1) == 0)
  {
    std::cerr << "Error: Empty input\n";
    return 1;
  }

  pelipenko::getCommonLetters(str1, str2, res);

  std::cout << res << '\n';

  return 0;
}

void pelipenko::getStr(std::istream& in, char* buf, std::size_t max_size)
{
  std::size_t len = 0;
  char ch = 0;

  while (in.get(ch) && ch != '\n' && (len + 1) < max_size)
  {
    buf[len] = ch;
    ++len;
  }

  buf[len] = '\0';
}

std::size_t pelipenko::getLen(const char* str)
{
  std::size_t len = 0;

  while (str[len] != '\0')
  {
    ++len;
  }

  return len;
}

void pelipenko::getCommonLetters(const char* str1, const char* str2, char* out)
{
  const std::size_t ALPHABET_SIZE = 26;
  bool found_letters[ALPHABET_SIZE] = {false};

  for (std::size_t i = 0; str2[i] != '\0'; ++i)
  {
    if (std::isalpha(static_cast< unsigned char >(str2[i])))
    {
      const char lower_ch = std::tolower(static_cast< unsigned char >(str2[i]));

      for (std::size_t j = 0; str1[j] != '\0'; ++j)
      {
        const char current_ch = std::tolower(static_cast< unsigned char >(str1[j]));

        if (current_ch == lower_ch)
        {
          found_letters[lower_ch - 'a'] = true;
          break;
        }
      }
    }
  }

  std::size_t pos = 0;

  for (std::size_t i = 0; i < ALPHABET_SIZE; ++i)
  {
    if (found_letters[i])
    {
      out[pos] = static_cast< char >('a' + i);
      ++pos;
    }
  }

  out[pos] = '\0';
}
