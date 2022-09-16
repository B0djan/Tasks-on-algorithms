/*
    -- A. ГРАФ ПОДСТРОК --
    В свой первый рабочий день стажер Слава решил как следует изучить офис. Бродя по коридорам, Слава начал смотреть на английские названия переговорок.
Вскоре он заметил, что названия переговорок имеют некий дисбаланс в буквосочетаниях - неужели в Яндексе изобрели какой-то свой диалект английского языка?
Славу очень заинтересовала эта тема, поэтому он решил построить модель буквосочетаний и изучить его.
Первым делом данную модель необходимо построить. Слава выбрал формат графа:
    название переговорки S=s1s2…sn−1sn образует n−2 буквосочетания длины 3: w1=s1s2s3, w2=s2s3s4, w3=s3s4s5 …wn−2=sn−2sn−1sn;
    если для какого-то из буквосочетаний wi еще нет вершины в графе, то она создается;
    для каждой пары буквосочетаний (wi,wi+1) добавляется ориентированное ребро веса 1, или увеличивается вес существующего ребра на 1.
Таким образом получается граф G с v вершинами и e ориентированными ребрами. Между некоторыми вершинами может быть несколько дуг (от a к b и от b к a).
Помогите Славе по заданному набору названий переговорок найти количество вершин в получившемся графе и вывести ориентированные ребра между вершинами.

    -- ФОРМАТ ВВОДА --
В первой строке записано одно целое число T (1≤T≤40000) — количество переговорок, которые встретил Слава по пути к рабочему месту.
В каждой из T следующих строк записано одно название переговорки Si (4≤|Si|≤30). Все названия состоят из строчных букв английского алфавита.

    -- ФОРМАТ ВЫВОДА --
В первой строке выведите количество вершин v в графе G.
Во второй строке выведите количество пар вершин e, между которыми есть ориентированные ребра.
В каждой из следующих e строк выведите слово ws, соответствующее началу ребра, затем слово wf, соответствующее концу ребра,
 и вес ориентированного ребра из вершины ws в wf.
Ребра вы можете перечислить в произвольном порядке.
 */


#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

struct pair_hash
{
    template <typename first, typename second>
    std::size_t operator() (const std::pair<first, second> &pair) const {
        return std::hash<first>()(pair.first) ^ std::hash<second>()(pair.second);
    }
};

struct graph {
    /* @brief: отображение из ребра <from, to> в вес ребра */
    std::unordered_map<std::pair<std::string, std::string>, uint16_t, pair_hash> edge_to_cost;
    /* @brief: множество всех узлов графа / или узлов из без пары */
    std::unordered_set<std::string> nodes;

    graph() = default;

    /* @brief: Добавляет ребро и увеличивает его вес */
    void add_edge(std::string::iterator from_begin,
                  std::string::iterator from_end,
                  std::string::iterator to_begin,
                  std::string::iterator to_end)
    {
        edge_to_cost[{{from_begin, from_end}, {to_begin, to_end}}]++;
    }

    /* @brief: добавляет узел */
    void add_node(std::string::iterator begin,
                  std::string::iterator end)
    {
        nodes.insert({begin, end});
    }

    void print() {
        std::cout << nodes.size() << '\n';
        std::cout << edge_to_cost.size() << '\n';
        for (const auto& [edge, cost] : edge_to_cost) {
            std::cout << edge.first << ' '
                      << edge.second << ' '
                      << cost << '\n';
        }
    }
};

int main() {
    uint16_t n;
    std::cin >> n;
    graph graph{};
    for (uint16_t i = 0; i < n; ++i) {
        std::string input_str;
        std::cin >> input_str;
        for (auto it_begin = input_str.begin(), it_end = input_str.begin() + 2;
             it_end != input_str.end()-1;
             ++it_begin, ++it_end)
        {
            graph.add_node(it_begin, it_end + 1);
            graph.add_edge(it_begin, it_end + 1, it_begin + 1, it_end + 2);
        }
        graph.add_node(input_str.end()-3, input_str.end());
    }
    graph.print();
    return 0;
}