#include <bits/stdtr1c++.h>

struct paticipant {
    std::string name;
    int score = 0;
    int penalty = 0;

    paticipant(const std::string& name, int score, int penalty) : name(name), score(score), penalty(penalty) {};
};

bool operator< (const paticipant& lhs, const paticipant& rhs) {
    if (lhs.score == rhs.score)
        return lhs.penalty < rhs.penalty;
    return lhs.score > rhs.score;
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    std::unordered_map<std::string, int> disciplines;
    for (int i = 0; i < n; ++i) {
        std::string name;
        int count;
        std::getline(std::cin, name, ',');
        std::cin >> count;
        disciplines[name] = count;
        std::cin.ignore();
    }

    std::unordered_map<std::string, std::set<paticipant>> map_discipline_to_participant;

    int k;
    std::cin >> k;
    std::cin.ignore();
    for (int i = 0; i < k; ++i) {
        std::string name;
        std::string discipline_name;
        int score;
        int penalty;
        std::getline(std::cin, name, ',');
        std::getline(std::cin, discipline_name, ',');
        std::cin >> score;
        std::cin.ignore();
        std::cin >> penalty;
        std::cin.ignore();
        map_discipline_to_participant[discipline_name].insert({name, score, penalty});
    }

    std::set<std::string> paticipants;
    for (const auto& [d_name, p_number] : disciplines) {
        int max_number = 0;
        for (auto it = map_discipline_to_participant[d_name].begin();
                  it != map_discipline_to_participant[d_name].end() && max_number < p_number;
                  ++it, ++max_number)
        {
            paticipants.insert(it->name);
        }
    }

    for (const auto& p : paticipants)
        std::cout << p << '\n';
    return 0;
}

