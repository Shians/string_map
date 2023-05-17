setClass("StringMap",
    slots = list(
        cppObj = "externalptr"
    ),
    prototype = list(
        cppObj = NULL
    )
)

setMethod("initialize", "StringMap",
    function(.Object, keys, values) {
        .Object@cppObj <- createStringMapRcpp(keys, values)
        .Object
    }
)

setGeneric("get_val", function(x, key) {
    standardGeneric("get_val")
})

setMethod("get_val", signature(x = "StringMap", key = "character"),
    function(x, key) {
        get_valRcpp(x@cppObj, key)
    }
)

setGeneric("StringMap", function(keys, values) {
    standardGeneric("StringMap")
})

setMethod("StringMap", signature(keys = "character", values = "character"),
    function(keys, values) {
        new("StringMap", keys = keys, values = values)
    }
)

setMethod("show", "StringMap",
    function(object) {
        cat("StringMap object:\n")
        cat("Keys:\n")
        print(names(object@cppObj))
        cat("Values:\n")
        cat(get_val(object, names(object@cppObj)))
    }
)

setMethod("show", "StringMap",
    function(object) {
        keys <- get_first_6_keysRcpp(object@cppObj)
        vals <- get_first_6_valsRcpp(object@cppObj)
        size <- sizeRcpp(object@cppObj)
        values <- get_val(object, keys)
        cat("StringMap object:\n")
        cat(glue::glue("{1:6}. [{keys}] -> [{values}]"), sep = "\n")
        cat("...", format(size - 6, scientific = FALSE), "more elements")
    }
)
