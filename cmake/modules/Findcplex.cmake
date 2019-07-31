if (NOT CPLEX_ROOT_DIR)
    set(CPLEX_ROOT_DIR "" CACHE PATH "Folder contains Gurobi library")
endif ()

if (NOT CPLEX_ROOT_DIR)
    file(GLOB CPLEX_ROOT_DIR /opt/ibm/ILOG/CPLEX_Studio_Community129)
endif ()
set(_CPLEX_INCLUDE_LOCATIONS "${CPLEX_ROOT_DIR}")
#set(_GUROBI_LIB_LOCATIONS "${GUROBI_ROOT_DIR}/linux64/lib")

#get_filename_component(_GUROBI_ROOT_DIR_NAME ${GUROBI_ROOT_DIR} NAME)
#string(REGEX MATCH "[0-9][0-9]" _GUROBI_VERSION_STRING ${_GUROBI_ROOT_DIR_NAME})

find_path(CPLEX_INCLUDE_DIR ilcplex/ilocplex.h
        HINTS "${CPLEX_ROOT_DIR}/cplex/include"
        PATHS "/usr/local/include")

find_path(CONCERT_INCLUDE_DIR ilconcert/ilomodel.h
        HINTS "${CPLEX_ROOT_DIR}/concert/include"
        PATHS "/usr/local/include")

find_library(CONCERT_LIBRARY concert
        HINTS "${CPLEX_ROOT_DIR}/concert/lib/x86-64_linux/static_pic/"
        PATHS "/usr/local/lib/concert"
        PATH_SUFFIXES lib)

find_library(_CPLEX_LIBRARY_cplex cplex
        HINTS "${CPLEX_ROOT_DIR}/cplex/lib/x86-64_linux/static_pic"
        PATHS "/usr/local/lib/cplex"
        PATH_SUFFIXES lib)

find_library(_CPLEX_LIBRARY_iloplex ilocplex
        HINTS "${CPLEX_ROOT_DIR}/cplex/lib/x86-64_linux/static_pic"
        PATHS "/usr/local/lib/cplex"
        PATH_SUFFIXES lib)

find_library(_CPLEX_LIBRARY_cplexdistmip cplexdistmip
        HINTS "${CPLEX_ROOT_DIR}/cplex/lib/x86-64_linux/static_pic"
        PATHS "/usr/local/lib/cplex"
        PATH_SUFFIXES lib)

set(CPLEX_LIBRARY "${_CPLEX_LIBRARY_iloplex}" "${_CPLEX_LIBRARY_cplex}" "${_CPLEX_LIBRARY_cplexdistmip}")
message(STATUS ${CPLEX_LIBRARY})


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CPLEX DEFAULT_MSG CPLEX_INCLUDE_DIR CONCERT_INCLUDE_DIR CONCERT_LIBRARY CPLEX_LIBRARY)