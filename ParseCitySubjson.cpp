#include <vector>

#include <iostream>
#include <string_view>

using namespace std;

struct CountryName {
    string value;
    explicit CountryName (const string& v)
        : value(v)
    {
    }
};

struct CountryIsoCode {
    string value;
    explicit CountryIsoCode(const string& v)
        : value(v)
    {
    }
};

struct CountryPhoneCod {
    string value;
    explicit CountryPhoneCod(const string& v)
        : value(v)
    {
    }
};

struct CountryTimeZone {
    string value;
    explicit CountryTimeZone(const string& v)
        : value(v)
    {
    }
};

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
template <typename City, typename Json, typename Language>
void ParseCitySubjson( vector<City>& cities,
                        const Json& json, 
                        CountryName country_name,
                        CountryIsoCode country_iso_code, 
                        CountryPhoneCod country_phone_code, 
                        CountryTimeZone country_time_zone,
                        const vector<Language>& languages) {
    
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          country_phone_code + city_obj["phone_code"s].AsString(), country_name, country_iso_code,
                          country_time_zone, languages });
    }
}


// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
template <typename City, typename Json, typename Language, typename Country>
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
            });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], country.name, country.iso_code, country.phone_code,
            country.time_zone, country.languages);
    }
}