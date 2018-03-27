cmake_minimum_required(VERSION 3.6)
project(coco_to_antlr)

# TODO: test finding & using coco on windows
find_program(COCO  NAMES cococpp Coco.exe  HINTS .. )
if(NOT COCO)
        message(FATAL_ERROR "Coco/R executable not found")
endif()
set(COCO_FRAME_DIR /home/azrael/Job/OCX_Parser/coco/coco_frame_files)
message("frames at ${COCO_FRAME_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
set(CMAKE_CXX_STANDARD 14)

set(GRAMMAR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/coco_to_antlr.atg)
set(generated_source_files
        ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Scanner.h
        ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Parser.h
)
set_source_files_properties(${generated_source_files} PROPERTIES GENERATED TRUE)
set(SOURCE_FILES
        CocoAST.cpp
        CocoAST.h
        CocoAstVisitor.cpp
        CocoAstVisitor.h
        CodeGenerator.cpp
        CodeGenerator.h
        AntlrOptimizer.cpp
        AntlrOptimizer.h

        main.cpp
        common.h
        ${generated_source_files}
)

# generate using Coco
add_custom_command(
        OUTPUT ${generated_source_files}
        COMMAND ${COCO} ${GRAMMAR_FILE} -namespace coco_to_antlr -frames ${COCO_FRAME_DIR} -o ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Parser from ${GRAMMAR_FILE} with ${COCO}"
        DEPENDS ${COCO_FRAME_DIR}/Scanner.frame
        DEPENDS ${COCO_FRAME_DIR}/Parser.frame
        MAIN_DEPENDENCY ${GRAMMAR_FILE}
        DEPENDS ${COCO}
        BYPRODUCTS trace.txt
)

include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}" )
add_executable(coco_to_antlr ${SOURCE_FILES})
target_include_directories (coco_to_antlr PRIVATE "${CMAKE_CURRENT_BINARY_DIR}" )
