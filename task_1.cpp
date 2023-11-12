#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const int MAX_READERS = 1e+5 + 1;
const int MAX_PAGES = 1e+3;

class ReadingStimulation {
private:
    std::vector<int> read_;
    std::vector<int> reading_results_;
    int count_users_ = 0;
private:
    void PrintStats(std::istream& in_stream);
    void AddReaders(std::istream& in_stream);
public:
    ReadingStimulation(std::istream& in_stream);
};

void ReadingStimulation::PrintStats(std::istream& in_stream) {
     int person = 0;
     in_stream >> person;           
     if (read_[person] == 0) {              
         std::cout << '0' << std::endl;
     } else if (count_users_ == 1) {
         std::cout << '1' << std::endl;                                
     } else {
         double count = 0; 
         count = count_users_ - reading_results_[read_[person]];
         if (count != 0) {
             double result =  count / (count_users_-1) ;   
             std::cout << std::setprecision(6) << result << std::endl;
         } else {
             std::cout << '0' << std::endl;
         }
     } 
}

void ReadingStimulation::AddReaders(std::istream& in_stream){
    int user = 0;
    in_stream >> user;
    int progress = 0 ;
    in_stream >> progress;
             
    if (read_[user] == 0){
        ++count_users_;
    }                      
    for(int x = (read_[user]+1); x <= progress; ++x) {
        ++reading_results_[x];
    }
    read_[user] = progress;  
}

ReadingStimulation::ReadingStimulation(std::istream& in_stream) {
        read_.resize(MAX_READERS, 0);
        reading_results_.resize(MAX_PAGES, 0);
        int person_count = 0;
        in_stream >> person_count;
        for (int i = 0; i < person_count; ++i) {
            std::string command;
            in_stream >> command;                    
            if (command == "CHEER") {
                PrintStats(in_stream);                          
            } else {
                AddReaders(in_stream);              
            }
    }
}
    
int main(){
     ReadingStimulation bm(std::cin);  
}

