#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

string ReverseDomain(string address) {
    string result(address.rbegin(), address.rend());
    return result +'.';
}

class Domain {
private:
    string domain_;
public:
    Domain(string& address)
    : domain_( ReverseDomain(address)) {}
    
    Domain() = default;
    
    bool operator==(const Domain& another) const{       
        return  another.domain_ == domain_;
    }
    
    bool operator<(const Domain& another) const {   
        return  std::lexicographical_compare(domain_.begin(), domain_.end(), another.domain_.begin(), another.domain_.end());
    }
    
    bool IsSubdomain(const Domain& address) const { 
        if(domain_.compare(
            0, domain_.size(), address.domain_, 0, domain_.size()) == 0){
            return true;
        }
        return false;              
    }
};

class DomainChecker {
private:
    vector<Domain> black_list_;
public:
    template <typename IteratorIt>
    DomainChecker(IteratorIt range_begin, IteratorIt range_end) {
        black_list_.assign(range_begin, range_end);
        std::sort(black_list_.begin(), black_list_.end());
        auto last = std::unique(black_list_.begin(), black_list_.end(), [] (Domain& a, Domain& b) 
            { return a.IsSubdomain(b); });
        black_list_.erase(last, black_list_.end());
    }

    bool IsForbidden(const Domain& data) {
        auto it = std::upper_bound(black_list_.begin(), black_list_.end(), data);
        if (it == black_list_.begin() ) {
            return false;
        } else {
            if( (*(it-1)).IsSubdomain(data)){
                return true;
            }
            return false;
        }       
   }
};

std::vector<Domain> ReadDomains(istream& input, size_t number_of_domains ) {
    std::vector<Domain> result;
    result.resize(number_of_domains);
    for (int x = 0; x < static_cast<int>(number_of_domains); ++x) {
        string line;
        getline(input, line);
        Domain bm(line);
        result[x] = bm;
    }
    return result;    
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}