add_executable(program_name main.c)
  
# add_subdirectory(subdir_name)

target_link_libraries(program_name
  PRIVATE
    log
    #tiny-aes
    #...
  )
