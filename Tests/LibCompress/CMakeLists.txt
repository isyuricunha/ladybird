set(TEST_SOURCES
    TestDeflate.cpp
    TestGzip.cpp
    TestLzw.cpp
    TestPackBits.cpp
    TestZlib.cpp
)

foreach(source IN LISTS TEST_SOURCES)
    serenity_test("${source}" LibCompress LIBS LibCompress)
endforeach()
