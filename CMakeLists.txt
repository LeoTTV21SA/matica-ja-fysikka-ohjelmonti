# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.10)

# Project Hybrid Cognitive Architecture
project(TTV21SPMatematiikkaaJaFysiikaaPeliohjelmoijille)

##
## Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

file(GLOB_RECURSE MAT_PHYS_INC_FILES "./include/*.h")
add_subdirectory("ext/mikroplot-main")
# Lisää GKM kirjasto projektiin
add_subdirectory("ext/glm-master")

# Tässä cppcheck integrointi, jos haluatte kokeilla:
#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
#if (CMAKE_CXX_CPPCHECK)
#	list(
#		APPEND CMAKE_CXX_CPPCHECK
#		    "-j 24"
#			"--enable=all"
#			"--force"
#			"--inline-suppr"
#			"--language=c++"
#			"--std=c++20"
#			"--template='{file}({line}):({severity}) {message}'"
#			"--output-file=cppcheck_report.md"
#			"--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#		)
#endif()

add_executable(1_functions notebooks/1_functions.cpp ${MAT_PHYS_INC_FILES})
add_executable(2_simple_draw notebooks/2_simple_draw.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(2_simple_draw mikroplot)
add_executable(3_integration notebooks/3_integration.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(3_integration mikroplot)
add_executable(4_newton notebooks/4_newton.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(4_newton mikroplot)
add_executable(5_lin_alg notebooks/5_lin_alg.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(5_lin_alg mikroplot)

add_executable(6_matrix notebooks/main_matrix.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(6_matrix mikroplot)

add_executable(7_collisions notebooks/7_collisions.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(7_collisions mikroplot)


add_executable(test_integration submissions/t2/test_integration.cpp ${MAT_PHYS_INC_FILES})
target_link_libraries(test_integration mikroplot)

add_executable(test_draw_functions submissions/t1/test_draw_functions.cpp )
target_link_libraries(test_draw_functions mikroplot)

add_executable(test_math submissions/t3/test_math.cpp submissions/t3/math.cpp  submissions/t3/math.h )
target_link_libraries(test_math  mikroplot)

add_executable( test_sat submissions/t4/test_sat.cpp submissions/t4/sat.h)
target_link_libraries(test_sat mikroplot glm)

add_executable( particle_demo submissions/t5/particle_demo.cpp submissions)
target_link_libraries(particle_demo mikroplot glm)

add_executable( spring_demo submissions/t6/spring_demo.cpp submissions)
target_link_libraries(spring_demo mikroplot glm)

add_executable( t7_t8_harjotustyo submissions/t7_t8_harjotustyo/t7_t8_harjotustyo.cpp submissions)
target_link_libraries(t7_t8_harjotustyo mikroplot glm)

add_executable(11_sat_collision  notebooks/11_sat_collosion.cpp)
target_link_libraries(11_sat_collision mikroplot glm)

# Fysiikan esimerkit , jotka käyttvät glm-kirjastoa
add_executable(8_phys_points notebooks/8_phys_points.cpp)
target_link_libraries(8_phys_points  mikroplot glm)

