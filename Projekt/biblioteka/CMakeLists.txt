cmake_minimum_required(VERSION 3.11)

project(Biblioteka)
FILE(GLOB SRCFILES src/model/*.cpp)
FILE(GLOB INCFILES include/model/*.h)
set(SOURCE_FILES ${SRCFILES}
                 ${INCFILES})

add_library(Biblioteka ${SOURCE_FILES})

#dolacz katalog z plikami naglowkowymi include z projektu biblioteka do sciezek
target_include_directories(Biblioteka PUBLIC include)

find_package (Boost 1.60 COMPONENTS system date_time unit_test_framework REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
		test/master.cpp
		test/ClientTest.cpp
		test/VehicleTest.cpp
		test/RentTest.cpp   )

add_executable (TestALL ${SOURCE_TEST_FILES})
add_executable (TestClient test/master.cpp test/ClientTest.cpp)
add_executable (TestVehicle test/master.cpp test/VehicleTest.cpp)
add_executable (TestRent test/master.cpp test/RentTest.cpp)


target_link_libraries (TestALL
		Biblioteka
		${Boost_LIBRARIES}
		)
target_link_libraries (TestClient
		Biblioteka
		${Boost_LIBRARIES}
		)
target_link_libraries (TestVehicle
		Biblioteka
		${Boost_LIBRARIES}
		)
target_link_libraries (TestRent
		Biblioteka
		${Boost_LIBRARIES}
		)

enable_testing()
add_test(TestBiblioteki1 TestALL TestClient TestVehicle TestRent
        --report_level=detailed
        --log_level=all
        --color_output=yes
       )

#add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
#        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
