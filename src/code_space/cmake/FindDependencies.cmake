# if JOT_FIND_QUIETLY is true, set JOT_FIND_TYPE to QUIET
# Only the error message that the library cannot be found will be output, 
# and the search process will not be output.
# if JOT_FIND_QUIETLY is false, set JOT_FIND_TYPE to REQUIRED
# If the library cannot be found, the build will fail.
if(JOT_FIND_QUIETLY)
    set(JOT_FIND_TYPE QUIET)
else()
    set(JOT_FIND_TYPE REQUIRED)
endif()

# Find the required libraries
if(TESTS_ENABLED)
    find_package(GTest ${JOT_FIND_TYPE})
endif()
