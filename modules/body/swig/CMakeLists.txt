SET_SOURCE_FILES_PROPERTIES("body.i" PROPERTIES CPLUSPLUS ON)
SET(SWIG_MODULE_body_EXTRA_SRCS
  "body/lyonwholebodymodel.i"
  "body/landmarkstranslator.i"
  "body/plugingait.i"
  "body/skeletonhelper.i"
  "body/externalwrenchassigner.i"
  "body/simplegaitforceplatetofeetassigner.i")
SET(SWIG_MODULE_body_EXTRA_FLAGS
  # "-debug-tmsearch"
  "-I${PROJECT_SOURCE_DIR}/modules/base/swig"
  "-I${PROJECT_SOURCE_DIR}/modules/bindings/swig"
  "-I${SWIG_DIR}/Lib")

IF(BUILD_MATLAB_BINDINGS)
  SET(BODY_MATLAB_SRCS
    "body.i"
    "../../bindings/include/openma/matlab/mexFunction.def")
  SET(CMAKE_SWIG_OUTDIR "${OPENMA_EXECUTABLE_PATH}/swig/matlab/openma")
  SET(SWIG_MODULE_bodyMEX_EXTRA_DEPS
    ${SWIG_MODULE_body_EXTRA_SRCS}
    "body_matlab.i")
  SET(SWIG_MODULE_bodyMEX_EXTRA_FLAGS
    "-module" "ma.body"
    "-mexname" "bodyMEX"
    ${SWIG_MODULE_body_EXTRA_FLAGS}
    "-I${SWIG_DIR}/Lib/matlab")
  SWIG_ADD_MODULE(bodyMEX matlab "${BODY_MATLAB_SRCS}")
  SWIG_LINK_LIBRARIES(${SWIG_MODULE_bodyMEX_REAL_NAME} body bindings ${MATLAB_LIBRARIES})
  TARGET_INCLUDE_DIRECTORIES(${SWIG_MODULE_bodyMEX_REAL_NAME} PRIVATE "${MATLAB_INCLUDE_DIR}")
  SET_TARGET_PROPERTIES(${SWIG_MODULE_bodyMEX_REAL_NAME} PROPERTIES
    COMPILE_DEFINITIONS "_SWIG_MATLAB"
    LIBRARY_OUTPUT_DIRECTORY "${OPENMA_EXECUTABLE_PATH}/swig/matlab/openma"
    PREFIX ""
    SUFFIX ".${MATLAB_MEXFILE_EXT}")
ENDIF()

IF(BUILD_PYTHON_BINDINGS)
  SET(BODY_PYTHON_SRCS
    "body.i")
  SET(CMAKE_SWIG_OUTDIR "${OPENMA_EXECUTABLE_PATH}/swig/python/openma/ma")
  SET(SWIG_MODULE_bodyPY_EXTRA_DEPS
    ${SWIG_MODULE_body_EXTRA_SRCS}
    "body_python.i")
  SET(SWIG_MODULE_bodyPY_EXTRA_FLAGS
    ${SWIG_MODULE_body_EXTRA_FLAGS}
    "-I${SWIG_DIR}/Lib/python")
  SWIG_ADD_MODULE(bodyPY python "${BODY_PYTHON_SRCS}")
  SWIG_LINK_LIBRARIES(bodyPY body bindings ${PYTHON_LIBRARY})
  TARGET_INCLUDE_DIRECTORIES(${SWIG_MODULE_bodyPY_REAL_NAME} PRIVATE "${PYTHON_INCLUDE_DIR}")
  SET_TARGET_PROPERTIES(${SWIG_MODULE_bodyPY_REAL_NAME} PROPERTIES
    OUTPUT_NAME "_body"
    LIBRARY_OUTPUT_DIRECTORY "${OPENMA_EXECUTABLE_PATH}/swig/python/openma/ma")
ENDIF()