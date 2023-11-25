#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename Person, typename DBLogLevel>
class DBInfo {
public:
DBInfo(string_view name, int db_connect_timeout, bool db_exceptions, DBLogLevel db_log_level)
    : name_(name), time_out_(db_connect_timeout), exceptions_(db_exceptions), db_log_level_(db_log_level_) {}

string GetName() const {
    return name_;
}

int GetTimeOut() const {
    return time_out_;
}

bool GetExceptions() const {
    return exceptions_;
}

DBLogLeve Getloglevel() const {
    return db_log_level_;
}

private:
    string name_;
    int time_out_;
    bool exceptions_;
    DBLogLeve db_log_level_;

};

class FilterParams {
public:
    FilterParams(int min_age, int max_age, string_view name_filter)
        : min_age_(min_age), max_age_(max_age), name_filter_(name_filter) {}

    int GetMinAge() const {
        return min_age_;
    }

    int GetMaxAge() const {
        return max_age_;
    }

    string GetNameFilter() const {
        return name_filter_;
    }

private:
    int min_age_;
    int max_age_;
    string name_filter_;
};



template <typename Person, typename DBLogLevel>
vector<Person> LoadPersons(DBInfo person, FilterParams info) {

    DBConnector connector(person.GetExceptions(), person.Getloglevel());

    DBHandler db;

    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(person.GetName(), person.GetTimeOut());
    }
    else {
        db = connector.Connect(person.GetName(), person.GetTimeOut());
    }

    if (!person.GetExceptions() && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << info.GetMinAge() << " and "s << info.GetMaxAge() << " "s
        << "and Name like '%"s << db.Quote(info.GetNameFilter()) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;

    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }


    return persons;
}