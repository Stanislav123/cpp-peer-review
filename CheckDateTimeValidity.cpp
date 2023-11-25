#include <iostream>
#include <string_view>

using namespace std;


void CheckYear(int year){
    if (year < 1) {
        domain_error("year is too small"s);
    }
    if (year > 9999) {
        domain_error("year is too big"s);
    }

}

void CheckMonth(int month){    
    if (month < 1) {
        throw domain_error("month is too small"s);
    }

    if (month > 12) {
        throw domain_error("month is too big"s);
    }
}

void CheckDay(int day, int month){
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day < 1) {
        throw domain_error("day is too small"s);
    }
    if (day > month_lengths[month - 1]) {
        throw domain_error("day is too big"s);
    }
}

void CheckHour(int hour){
    if (hour < 0 ) {
        throw domain_error("hour is too small"s);
    }
    if (hour > 23) {
        throw domain_error("hour is too big"s);
    }
}

void CheckMinuteAndSecond(int minute, int second){
    f (minute < 0 || second < 0 ) {
        throw domain_error("minute or second is too small"s);
    }
    if (minute > 59 || second > 59) {
        throw domain_error("minute or second is too big"s);
    }

}

void CheckDateTimeValidity(const DateTime& dt) {

    CheckYear(dt.year);
    
    CheckMonth(dt.month); 

    CheckDay(dt.day, dt.month);   

    CheckHour(dt.hour);

    CheckMinuteAndSecond(dt.minute, dt.second);
}

 