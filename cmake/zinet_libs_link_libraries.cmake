
# ZtMain
target_link_libraries(ZtMain PRIVATE spdlog)

# ZtFrame
target_link_libraries(ZtFrame PRIVATE ZtMain)
target_link_libraries(ZtFrame PRIVATE sfml-graphics sfml-system sfml-window sfml-audio)

# ZtReflection
target_link_libraries(ZtReflection PRIVATE ZtMain)