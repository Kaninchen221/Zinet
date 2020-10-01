
target_link_libraries(Sandbox PRIVATE ZtSystem)

target_link_libraries(ZtMain PRIVATE spdlog)

target_link_libraries(ZtSystem PRIVATE ZtMain)