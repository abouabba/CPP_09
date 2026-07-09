# include <algorithm>
# include <vector>
# include <iostream>



int main() {
    std::vector<int> vc;
    vc.push_back(2);
    vc.push_back(3);
    vc.push_back(4);
    vc.push_back(7);
    vc.push_back(9);


    /////   [0 11] [6  9] [10  12]

    std::vector<int>::iterator limitTt = std::find(vc.begin(), vc.end(), 7);
    std::vector<int>::iterator it = std::lower_bound(vc.begin(), limitTt + 1, 8);

    std::cout << *limitTt << std::endl;
    std::cout << *it << std::endl;
    vc.insert(it, 5);

    for (size_t i = 0; i < vc.size(); i++)
    {
        std::cout << vc.at(i) << " ";
    }
    
}