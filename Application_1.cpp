#include <iostream>
#include <vector>

// Computes the prefix function for the given pattern.
std::vector<int> compute_prefix_function(const std::string& pattern) {
  int m = pattern.size();
  std::vector<int> prefix_function(m);
  prefix_function[0] = 0;
  int k = 0;
  for (int q = 1; q < m; q++) {
    while (k > 0 && pattern[k] != pattern[q]) {
      k = prefix_function[k - 1];
    }
    if (pattern[k] == pattern[q]) {
      k++;
    }
    prefix_function[q] = k;
  }
  return prefix_function;
}

// Uses the KMP algorithm to search for the pattern in the text.
// Returns a vector of integers containing the starting indices of all occurrences of the pattern in the text.
std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
  int n = text.size();
  int m = pattern.size();
  std::vector<int> prefix_function = compute_prefix_function(pattern);
  std::vector<int> occurrences;
  int q = 0;
  for (int i = 0; i < n; i++) {
    while (q > 0 && pattern[q] != text[i]) {
      q = prefix_function[q - 1];
    }
    if (pattern[q] == text[i]) {
      q++;
    }
    if (q == m) {
      occurrences.push_back(i - m + 1);
      q = prefix_function[q - 1];
    }
  }
  return occurrences;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::string text;
  std::cin >> text;
  std::string pattern = "Anyn";
  std::vector<int> occurrences = kmp_search(text, pattern);
  for (int i = 0; i < (int)occurrences.size(); i++) {
    std::cout << "Pattern occurs at index " << occurrences[i] << std::endl;
  }
  return 0;
}