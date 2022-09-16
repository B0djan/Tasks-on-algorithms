#include <bits/stdtr1c++.h>

int main() {
    std::string first, second;
    std::cin >> first >> second;
    std::string answer (first.size(), 'I');
    std::vector<int> countSymbol (256, 0);

    for (int i = 0; i < first.size(); ++i) {
        if (first[i] == second[i]) {
            answer[i] = 'P';
        } else {
            countSymbol[first[i]] += 1;
        }
    }

    for (int i = 0; i < second.size(); ++i) {
        if (second[i] != first[i]) {
            if (countSymbol[second[i]] > 0) {
                answer[i] = 'S';
                countSymbol[second[i]] -= 1;
            }
        }
    }

    std::cout << answer << std::endl;
    return 0;
}

