# Simple string to string lookup in R

This pair of scripts is used to add the ability to create an efficient lookup table for an R package. It wraps the `unordered_map` class from C++ via Rcpp for efficiency. For now I do not want this to become an R package until I have time to extend it into a more fully featured hash map.

## Usage

To include this into your package use this from your R package root:
```
download.file("https://github.com/shians/string_map/raw/main/string_map.R", "R/string_map.R")
download.file("https://github.com/shians/string_map/raw/main/string_map.R", "src/string_map.cpp")
```

## Example

wrapper <- StringMap(
    keys = paste0("key", 1:1e5),
    values = paste0("value", 1:1e5)
)

get_val(wrapper, key = c("key1", "foo", "bar", "key10", "key100"))
