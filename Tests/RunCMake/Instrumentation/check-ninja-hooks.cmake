set(NUM_TRIES 30)
set(DELAY 1)

if (NOT EXISTS ${v1}/preBuild.hook)
  set(RunCMake_TEST_FAILED "preBuild hook did not run\n")
endif()

macro(hasPostBuildArtifacts)
  if (NOT postBuildRan AND EXISTS ${v1}/postBuild.hook)
    set(postBuildRan 1)
  endif()
  if (NOT dataDirClean)
    file(GLOB snippets "${v1}/data/*")
    if ("${snippets}" STREQUAL "")
      set(dataDirClean 1)
    endif()
  endif()
endmacro()

set(postBuildRan 0)
set(dataDirClean 0)
foreach(_ RANGE ${NUM_TRIES})
  hasPostBuildArtifacts()
  if (postBuildRan AND dataDirClean)
    break()
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} -E sleep ${DELAY})
endforeach()

if (NOT postBuildRan)
  string(APPEND RunCMake_TEST_FAILED "postBuild hook did not run\n")
endif()
if (NOT dataDirClean)
  string(APPEND RunCMake_TEST_FAILED "Snippet files not fully removed post build\n")
endif()
