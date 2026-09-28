add_test([=[RegisterTest.initalValueEqReset]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=RegisterTest.initalValueEqReset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RegisterTest.initalValueEqReset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/registerTest.cpp:20]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.LdaImmediateFF_SameAsBefore]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.LdaImmediateFF_SameAsBefore]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.LdaImmediateFF_SameAsBefore]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:35]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.LdaImmediateZero_SetsZeroFlag]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.LdaImmediateZero_SetsZeroFlag]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.LdaImmediateZero_SetsZeroFlag]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:61]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.LdaImmediate80_PreservesOldNegativeBug]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.LdaImmediate80_PreservesOldNegativeBug]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.LdaImmediate80_PreservesOldNegativeBug]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:72]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.ImpliedClc_DecodeDoesNotAdvancePc]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.ImpliedClc_DecodeDoesNotAdvancePc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.ImpliedClc_DecodeDoesNotAdvancePc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:83]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.ImpliedSeiCli]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.ImpliedSeiCli]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.ImpliedSeiCli]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:97]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.NopIsSingleByte]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.NopIsSingleByte]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.NopIsSingleByte]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:109]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.DecodeResolvesHandler]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.DecodeResolvesHandler]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.DecodeResolvesHandler]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:116]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.DecodeZeroPage_EffectiveAddress]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.DecodeZeroPage_EffectiveAddress]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.DecodeZeroPage_EffectiveAddress]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:127]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.DecodeAbsoluteX_AddsX]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.DecodeAbsoluteX_AddsX]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.DecodeAbsoluteX_AddsX]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:140]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.DecodeRelative_ComputesTarget]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.DecodeRelative_ComputesTarget]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.DecodeRelative_ComputesTarget]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:154]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CpuFixture.DecodeIndirectX_WrapsZeroPage]=]  /home/ruifag/6502/tests/sfot-tests [==[--gtest_filter=CpuFixture.DecodeIndirectX_WrapsZeroPage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CpuFixture.DecodeIndirectX_WrapsZeroPage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/ruifag/6502/tests/decodeTest.cpp:164]==]
    WORKING_DIRECTORY [==[/home/ruifag/6502/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(sfot-tests_TESTS [==[RegisterTest.initalValueEqReset]==] [==[CpuFixture.LdaImmediateFF_SameAsBefore]==] [==[CpuFixture.LdaImmediateZero_SetsZeroFlag]==] [==[CpuFixture.LdaImmediate80_PreservesOldNegativeBug]==] [==[CpuFixture.ImpliedClc_DecodeDoesNotAdvancePc]==] [==[CpuFixture.ImpliedSeiCli]==] [==[CpuFixture.NopIsSingleByte]==] [==[CpuFixture.DecodeResolvesHandler]==] [==[CpuFixture.DecodeZeroPage_EffectiveAddress]==] [==[CpuFixture.DecodeAbsoluteX_AddsX]==] [==[CpuFixture.DecodeRelative_ComputesTarget]==] [==[CpuFixture.DecodeIndirectX_WrapsZeroPage]==])
