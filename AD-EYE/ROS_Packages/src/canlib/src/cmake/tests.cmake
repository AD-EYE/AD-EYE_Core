enable_testing()
add_subdirectory(googletest)


add_executable(test_e2e_protector
  ${DBC_FILES}
  ${COMMON_SRC}
  HAL/can_socketcan.cpp
  e2e_protector.cpp
  dbc_reader.cpp
  can_frame.cpp
  E2E/src/E2E_P01.c
  E2E/src/E2E_P05.c
  Crc/src/Crc_8.c
  Crc/src/Crc_16.c
  tests/test_e2e_protector.cpp
)

target_link_libraries(test_e2e_protector
  GTest::gtest
)

add_test(NAME E2EProtectorTest.AdpLiReqFromAPI COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdSecSteerStsSafeGroup COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.SSMBDegraded COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.BrkDegradedRdnt COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.SSMDegraded COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimSteerStsSafeGroup COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.ClstrSts1ForAutnmsDrv COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.ClstrSts2ForAutnmsDrv COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AutnmsDrvModMngtGlbSafe1 COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.BrkDegraded COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.WhlLockSts COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimPose COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimPSSGroupSafe8 COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdSecSteerActvnGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrpsnTqDir COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.DrvrPrsntGroup COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimVehSpdGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimALgtDataRawSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimWhlAgEstimdGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimALatDataRawSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimVLatSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimWhlRotDirReSafe1 COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimWhlRotToothCntr COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.PrimYawRateSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdFreeDst COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdWhlLockReq COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimWhlAgReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdSecWhlAgReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdNomALgtReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdPrimALgtLimReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.AdSecALgtLimReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.SecAdNomALgtReqGroupSafe COMMAND test_e2e_protector)
add_test(NAME E2EProtectorTest.SecYawRateSafe COMMAND test_e2e_protector)


add_executable(test_dbc_reader
  ${DBC_FILES}
  ${COMMON_SRC}
  HAL/can_socketcan.cpp
  e2e_protector.cpp
  dbc_reader.cpp
  can_frame.cpp
  E2E/src/E2E_P01.c
  E2E/src/E2E_P05.c
  Crc/src/Crc_8.c
  Crc/src/Crc_16.c
  tests/test_dbc_reader.cpp
)

target_link_libraries(test_dbc_reader
  GTest::gtest_main
)

add_test(NAME DBCReaderTest.getSignalInfo COMMAND test_dbc_reader)
add_test(NAME DBCReaderTest.getSignalInfo_Exception COMMAND test_dbc_reader)
add_test(NAME DBCReaderTest.getSignalGroupInfo COMMAND test_dbc_reader)
add_test(NAME DBCReaderTest.getSignalGroupInfo_Exception COMMAND test_dbc_reader)
add_test(NAME DBCReaderTest.getFrameInfo COMMAND test_dbc_reader)
add_test(NAME DBCReaderTest.getFrameInfo_Exception COMMAND test_dbc_reader)


add_executable(test_can_sender
  ${DBC_FILES}
  ${COMMON_SRC}
  HAL/can_socketcan.cpp
  e2e_protector.cpp
  dbc_reader.cpp
  can_frame.cpp
  E2E/src/E2E_P01.c
  E2E/src/E2E_P05.c
  Crc/src/Crc_8.c
  Crc/src/Crc_16.c
  tests/test_can_sender.cpp
)

target_link_libraries(test_can_sender
  GTest::gtest
)

add_test(NAME CANSenderTest.sendSignalGroup COMMAND test_can_sender)