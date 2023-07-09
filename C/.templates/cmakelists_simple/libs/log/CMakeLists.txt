add_library(log "")

target_sources(log
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/log.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/log.c
)

target_include_directories(log
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
)