#include "map.hpp"
#include <iostream>
#include <map>
#include <string>
#include "tree.hpp"
#include "include/iterator.hpp"

// using namespace std;

int main(void){

    ft::map<int, std::string> m;

    m.insert(ft::pair<int, std::string>(40, "me"));
    m.insert(ft::pair<int, std::string>(35, "Show"));
    m.insert(ft::pair<int, std::string>(10, "Dok2"));
    m.insert(ft::pair<int, std::string>(90, "6"));
    m.insert(ft::pair<int, std::string>(65, "money"));
    m.insert(ft::pair<int, std::string>(20, "ZICO"));
    m.insert(ft::pair<int, std::string>(50, "the"));


    ft::map<int, std::string>::iterator iter;

    //접근방법 1
    for(iter = m.begin(); iter != m.end(); iter++){
        std::cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    std::cout << std::endl;

    //접근방법 2
    for(iter = m.begin(); iter != m.end(); iter++){
        std::cout << "[" << (*iter).first << ", " << (*iter).second << "]" << " " ;
    }


    return 0;
}
