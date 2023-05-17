#include <Rcpp.h>
#include <unordered_map>
#include <vector>

using namespace Rcpp;

// Define a class to encapsulate the unordered_map
class StringMap {
public:
    StringMap(std::vector<std::string> keys, std::vector<std::string> values) {
        if (keys.size() != values.size()) {
            stop("input vectors must have equal length.");
        }

        _map = std::unordered_map<std::string, std::string>();
        for (size_t i = 0; i < values.size(); ++i) {
            if (i < 6) {
                _first_6_keys.push_back(keys[i]);
                _first_6_vals.push_back(values[i]);
            }
            _map[keys[i]] = values[i];
        }
    }

    StringVector get_val(const std::vector<std::string>& keys) {
        StringVector values;
        for (const auto& key : keys) {
            auto const it = _map.find(key);
            if (it != _map.end()) {
                values.push_back(it->second);
            } else {
                values.push_back(NA_STRING);
            }
        }
        return values;
    }

    std::vector<std::string> get_first_6_keys() {
        return _first_6_keys;
    }

    std::vector<std::string> get_first_6_vals() {
        return _first_6_vals;
    }

    size_t size() {
        return _map.size();
    }

private:
    std::unordered_map<std::string, std::string> _map;
    std::vector<std::string> _first_6_keys;
    std::vector<std::string> _first_6_vals;
};

// // Define a function to retrieve a value from the unordered_map

// [[Rcpp::export]]
SEXP createStringMapRcpp(std::vector<std::string> keys, std::vector<std::string> values) {
    StringMap* str_map = new StringMap(keys, values);
    Rcpp::XPtr<StringMap> xptr(str_map, true);
    return xptr;
}

// [[Rcpp::export]]
StringVector get_valRcpp(SEXP str_map_ptr, std::vector<std::string> keys) {
    Rcpp::XPtr<StringMap> map_ptr(str_map_ptr);
    return map_ptr->get_val(keys);
}

// [[Rcpp::export]]
std::vector<std::string> get_first_6_keysRcpp(SEXP str_map_ptr) {
    Rcpp::XPtr<StringMap> map_ptr(str_map_ptr);
    return map_ptr->get_first_6_keys();
}

// [[Rcpp::export]]
std::vector<std::string> get_first_6_valsRcpp(SEXP str_map_ptr) {
    Rcpp::XPtr<StringMap> map_ptr(str_map_ptr);
    return map_ptr->get_first_6_vals();
}

// [[Rcpp::export]]
size_t sizeRcpp(SEXP str_map_ptr) {
    Rcpp::XPtr<StringMap> map_ptr(str_map_ptr);
    return map_ptr->size();
}
