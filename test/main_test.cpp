#include "happly.h"

#include <iostream>
#include <string>
#include <chrono>
#include <random>

#include "gtest/gtest.h"

using std::cout;
using std::endl;

// === Test helpers
void DoubleArrayVecEq(std::vector<std::array<double, 3>>& arr1, std::vector<std::array<double, 3>>& arr2) {

  EXPECT_EQ(arr1.size(), arr2.size());

  for (size_t i = 0; i < arr1.size(); i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(arr1[i][j], arr2[i][j]);
    }
  }
}
// void VecEq(std::vector<double>& arr1, std::vector<double>& arr2) {
// EXPECT_EQ(arr1.size(), arr2.size());
// for (size_t i = 0; i < arr1.size(); i++) {
// EXPECT_DOUBLE_EQ(arr1[i], arr2[i]);
//}
//}

// == Test typed reading/writing

// = functors

TEST(TypedReadWriteTest, ReadWriteIntBinaryF) {

  // Create a simple file
  happly::PLYData plyOut;
  plyOut.addElement("test_elem", 5);
  std::vector<int> const testData_int{-3, 0, 2147483647, -2147483647 - 1, 122};
  auto const& testData = testData_int;
  plyOut.getElement("test_elem")
      .addProperty(
          "test_data", [&testData](size_t index) { return testData[index]; },
          [&testData]() { return testData.size(); });
  
  // Binary read/write
  plyOut.write("temp.ply", happly::DataFormat::Binary);
  happly::PLYData plyInB("temp.ply");
  std::vector<int> testDataBinary = plyInB.getElement("test_elem").getProperty<int>("test_data");
  EXPECT_EQ(testData, testDataBinary);
}

TEST(TypedReadWriteTest, ReadWriteFloatBinaryF) {

  // Create a simple file
  happly::PLYData plyOut;
  std::vector<float> const testData_floatBinary{
      3.141592653589793238f,
      -3.141592653589793238f,
      std::numeric_limits<float>::min(),
      std::numeric_limits<float>::max(),
      std::numeric_limits<float>::lowest(),
      std::numeric_limits<float>::epsilon(),
      std::numeric_limits<float>::infinity(),
      -std::numeric_limits<float>::infinity(),
      0.0f,
      -0.0f,
      1e24f,
  };
  auto const& testData = testData_floatBinary;
  plyOut.addElement("test_elem", testData.size());
  plyOut.getElement("test_elem")
      .addProperty(
          "test_data", [&testData](size_t index) { return testData[index]; },
          [&testData]() { return testData.size(); });
  
  // ASCII read/write
  plyOut.write("temp.ply", happly::DataFormat::Binary);
  happly::PLYData plyIn("temp.ply");
  std::vector<float> testDataBinary = plyIn.getElement("test_elem").getProperty<float>("test_data");
  EXPECT_EQ(testData, testDataBinary);
}


// = char
std::vector<char> const testData_char{-3, 4, 11, -12, 122};

TEST(TypedReadWriteTest, ReadWriteCharASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char;
    plyOut.getElement("test_elem").addProperty<char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<char> testDataASCII = plyIn.getElement("test_elem").getProperty<char>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteCharBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char;
    plyOut.getElement("test_elem").addProperty<char>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<char> testDataBinary = plyInB.getElement("test_elem").getProperty<char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteCharBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char;
    plyOut.getElement("test_elem").addProperty<char>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<char> testDataBinary = plyInB.getElement("test_elem").getProperty<char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned char
std::vector<unsigned char> const testData_unsigned_char{3, 0, 11, 255, 122};

TEST(TypedReadWriteTest, ReadWriteUCharASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char;
    plyOut.getElement("test_elem").addProperty<unsigned char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<unsigned char> testDataASCII = plyIn.getElement("test_elem").getProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteUCharBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char;
    plyOut.getElement("test_elem").addProperty<unsigned char>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned char> testDataBinary = plyInB.getElement("test_elem").getProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteUCharBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char;
    plyOut.getElement("test_elem").addProperty<unsigned char>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned char> testDataBinary = plyInB.getElement("test_elem").getProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = short
std::vector<short> const testData_short{-3, 4, 32767, -32768, 122};

TEST(TypedReadWriteTest, ReadWriteShortASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short;
    plyOut.getElement("test_elem").addProperty<short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<short> testDataASCII = plyIn.getElement("test_elem").getProperty<short>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteShortBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short;
    plyOut.getElement("test_elem").addProperty<short>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<short> testDataBinary = plyInB.getElement("test_elem").getProperty<short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteShortBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short;
    plyOut.getElement("test_elem").addProperty<short>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<short> testDataBinary = plyInB.getElement("test_elem").getProperty<short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned short
std::vector<unsigned short> const testData_unsigned_short{3, 0, 11, 65535, 122};

TEST(TypedReadWriteTest, ReadWriteUShortASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short;
    plyOut.getElement("test_elem").addProperty<unsigned short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<unsigned short> testDataASCII = plyIn.getElement("test_elem").getProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteUShortBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short;
    plyOut.getElement("test_elem").addProperty<unsigned short>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned short> testDataBinary =
        plyInB.getElement("test_elem").getProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteUShortBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short;
    plyOut.getElement("test_elem").addProperty<unsigned short>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned short> testDataBinary =
        plyInB.getElement("test_elem").getProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = int
std::vector<int> const testData_int{-3, 0, 2147483647, -2147483647 - 1, 122};

TEST(TypedReadWriteTest, ReadWriteIntASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int;
    plyOut.getElement("test_elem").addProperty<int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<int> testDataASCII = plyIn.getElement("test_elem").getProperty<int>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteIntBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int;
    plyOut.getElement("test_elem").addProperty<int>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<int> testDataBinary = plyInB.getElement("test_elem").getProperty<int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteIntBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int;
    plyOut.getElement("test_elem").addProperty<int>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<int> testDataBinary = plyInB.getElement("test_elem").getProperty<int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned int
std::vector<unsigned int> const testData_unsigned_int{3, 0, 4294967295, 15, 122};

TEST(TypedReadWriteTest, ReadWriteUIntASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int;
    plyOut.getElement("test_elem").addProperty<unsigned int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<unsigned int> testDataASCII = plyIn.getElement("test_elem").getProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteUIntBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int;
    plyOut.getElement("test_elem").addProperty<unsigned int>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned int> testDataBinary = plyInB.getElement("test_elem").getProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteUIntBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int;
    plyOut.getElement("test_elem").addProperty<unsigned int>("test_data", testData, rw);

    // Binary read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyInB("temp.ply");
    std::vector<unsigned int> testDataBinary = plyInB.getElement("test_elem").getProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = float
std::vector<float> const testData_floatBinary{
    3.141592653589793238f,
    -3.141592653589793238f,
    std::numeric_limits<float>::min(),
    std::numeric_limits<float>::max(),
    std::numeric_limits<float>::lowest(),
    std::numeric_limits<float>::epsilon(),
    std::numeric_limits<float>::infinity(),
    -std::numeric_limits<float>::infinity(),
    0.0f,
    -0.0f,
    1e24f,
};

TEST(TypedReadWriteTest, ReadWriteFloatASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    std::vector<float> testData{
        3.141592653589793238f,
        -3.141592653589793238f,
        std::numeric_limits<float>::min(),
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::epsilon(),
        // std::numeric_limits<float>::infinity(),     // these DO NOT work right now, due to how ostream works
        //-std::numeric_limits<float>::infinity(),
        0.0f,
        -0.0f,
        1e24f,
    };
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<float> testDataASCII = plyIn.getElement("test_elem").getProperty<float>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteFloatBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    auto const& testData = testData_floatBinary;
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<float> testDataBinary = plyIn.getElement("test_elem").getProperty<float>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteFloatBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    auto const& testData = testData_floatBinary;
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<float> testDataBinary = plyIn.getElement("test_elem").getProperty<float>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = double
std::vector<double> const testData_doubleBinary{
    3.141592653589793238,
    -3.141592653589793238,
    std::numeric_limits<double>::min(),
    std::numeric_limits<double>::max(),
    std::numeric_limits<double>::lowest(),
    std::numeric_limits<double>::epsilon(),
    std::numeric_limits<double>::infinity(),
    -std::numeric_limits<double>::infinity(),
    0.0,
    -0.0,
    1e24,
};

TEST(TypedReadWriteTest, ReadWriteDoubleASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    std::vector<double> testData{
        3.141592653589793238,
        -3.141592653589793238,
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::lowest(),
        std::numeric_limits<double>::epsilon(),
        // std::numeric_limits<double>::infinity(),     // these DO NOT work right now, due to how ostream works
        //-std::numeric_limits<double>::infinity(),
        0.0,
        -0.0,
        1e24,
    };
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<double> testDataASCII = plyIn.getElement("test_elem").getProperty<double>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedReadWriteTest, ReadWriteDoubleBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    auto const& testData = testData_doubleBinary;
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<double> testDataBinary = plyIn.getElement("test_elem").getProperty<double>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedReadWriteTest, ReadWriteDoubleBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    auto const& testData = testData_doubleBinary;
    plyOut.addElement("test_elem", testData.size());
    plyOut.getElement("test_elem").addProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<double> testDataBinary = plyIn.getElement("test_elem").getProperty<double>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = signed char list
std::vector<std::vector<char>> const testData_char_list{
    {3}, {3, 0, 11, -128, 127}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteCharASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char_list;
    plyOut.getElement("test_elem").addListProperty<char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<char>> testDataASCII = plyIn.getElement("test_elem").getListProperty<char>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteCharBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char_list;
    std::cout << "size: " << testData.size() << std::endl;
    for (auto& v : testData) {
      std::cout << "sub size: " << v.size() << std::endl;
    }
    plyOut.getElement("test_elem").addListProperty<char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<char>> testDataBinary = plyIn.getElement("test_elem").getListProperty<char>("test_data");
    std::cout << "size: " << testDataBinary.size() << std::endl;
    for (auto& v : testDataBinary) {
      std::cout << "sub size: " << v.size() << std::endl;
    }
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteCharBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_char_list;
    plyOut.getElement("test_elem").addListProperty<char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<char>> testDataBinary = plyIn.getElement("test_elem").getListProperty<char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned char list
std::vector<std::vector<unsigned char>> const testData_unsigned_char_list{
    {3}, {3, 0, 11, 255, 122}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteUCharASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char_list;
    plyOut.getElement("test_elem").addListProperty<unsigned char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned char>> testDataASCII =
        plyIn.getElement("test_elem").getListProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUCharBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char_list;
    plyOut.getElement("test_elem").addListProperty<unsigned char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned char>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUCharBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_char_list;
    plyOut.getElement("test_elem").addListProperty<unsigned char>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned char>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned char>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = signed short list
std::vector<std::vector<short>> const testData_short_list{
    {3}, {-3, 4, 32767, -32768, 122}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteShortASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short_list;
    plyOut.getElement("test_elem").addListProperty<short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<short>> testDataASCII = plyIn.getElement("test_elem").getListProperty<short>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteShortBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short_list;
    plyOut.getElement("test_elem").addListProperty<short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<short>> testDataBinary = plyIn.getElement("test_elem").getListProperty<short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteShortBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_short_list;
    plyOut.getElement("test_elem").addListProperty<short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<short>> testDataBinary = plyIn.getElement("test_elem").getListProperty<short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned short list
std::vector<std::vector<unsigned short>> const testData_unsigned_short_list{
    {3}, {3, 0, 11, 65535, 122}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteUShortASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short_list;
    plyOut.getElement("test_elem").addListProperty<unsigned short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned short>> testDataASCII =
        plyIn.getElement("test_elem").getListProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUShortBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short_list;
    plyOut.getElement("test_elem").addListProperty<unsigned short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned short>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUShortBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_short_list;
    plyOut.getElement("test_elem").addListProperty<unsigned short>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned short>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned short>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = signed int list
std::vector<std::vector<int>> const testData_int_list{
    {3}, {-3, 0, 2147483647, -2147483647 - 1, 122}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteIntASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int_list;
    plyOut.getElement("test_elem").addListProperty<int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<int>> testDataASCII = plyIn.getElement("test_elem").getListProperty<int>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteIntBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int_list;
    plyOut.getElement("test_elem").addListProperty<int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<int>> testDataBinary = plyIn.getElement("test_elem").getListProperty<int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteIntBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_int_list;
    plyOut.getElement("test_elem").addListProperty<int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<int>> testDataBinary = plyIn.getElement("test_elem").getListProperty<int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = unsigned int list
std::vector<std::vector<unsigned int>> const testData_unsigned_int_list{
    {3}, {3, 0, 4294967295, 15, 122}, {}, {}, {3, 11},
};

TEST(TypedListReadWriteTest, ReadWriteUIntASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int_list;
    plyOut.getElement("test_elem").addListProperty<unsigned int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned int>> testDataASCII =
        plyIn.getElement("test_elem").getListProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUIntBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int_list;
    plyOut.getElement("test_elem").addListProperty<unsigned int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned int>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteUIntBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_unsigned_int_list;
    plyOut.getElement("test_elem").addListProperty<unsigned int>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<unsigned int>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<unsigned int>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}


// = float list
std::vector<std::vector<float>> const testData_float_list{
    {3.f, 14.44f, 42.4242f},
    {
        3.141592653589793238f,
        -3.141592653589793238f,
        std::numeric_limits<float>::min(),
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::epsilon(),
        0.0f,
        -0.0f,
        1e24f,
    },
    {},
    {1.1f},
    {-121.5f, 1.111f},
};

TEST(TypedListReadWriteTest, ReadWriteFloatASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_float_list;
    plyOut.getElement("test_elem").addListProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<float>> testDataASCII = plyIn.getElement("test_elem").getListProperty<float>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteFloatBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_float_list;
    plyOut.getElement("test_elem").addListProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<float>> testDataBinary = plyIn.getElement("test_elem").getListProperty<float>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteFloatBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_float_list;
    plyOut.getElement("test_elem").addListProperty<float>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<float>> testDataBinary = plyIn.getElement("test_elem").getListProperty<float>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// = double list
std::vector<std::vector<double>> const testData_double_list{
    {3., 14.44, 42.4242},
    {
        3.141592653589793238,
        -3.141592653589793238,
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::lowest(),
        std::numeric_limits<double>::epsilon(),
        0.0,
        -0.0,
        1e24,
    },
    {},
    {1.1},
    {-121.5, 1.111},
};

TEST(TypedListReadWriteTest, ReadWriteDoubleASCII) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_double_list;
    plyOut.getElement("test_elem").addListProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::ASCII);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<double>> testDataASCII = plyIn.getElement("test_elem").getListProperty<double>("test_data");
    EXPECT_EQ(testData, testDataASCII);
  }
}
TEST(TypedListReadWriteTest, ReadWriteDoubleBinary) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_double_list;
    plyOut.getElement("test_elem").addListProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::Binary);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<double>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<double>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}
TEST(TypedListReadWriteTest, ReadWriteDoubleBinarySwap) {

  for (int rw = 0; rw < 2; ++rw) {
    // Create a simple file
    happly::PLYData plyOut;
    plyOut.addElement("test_elem", 5);
    auto const& testData = testData_double_list;
    plyOut.getElement("test_elem").addListProperty<double>("test_data", testData, rw);

    // ASCII read/write
    plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);
    happly::PLYData plyIn("temp.ply");
    std::vector<std::vector<double>> testDataBinary =
        plyIn.getElement("test_elem").getListProperty<double>("test_data");
    EXPECT_EQ(testData, testDataBinary);
  }
}

// === Test error and utility behavior

// Errors get thrown
TEST(ErrorTest, NonexistantElement) {
  happly::PLYData emptyPly;
  EXPECT_THROW(emptyPly.getElement("test_elem");, std::runtime_error);
}

TEST(ErrorTest, NonexistantProperty) {

  happly::PLYData emptyPly;
  emptyPly.addElement("test_elem", 11);

  EXPECT_THROW(emptyPly.getElement("test_elem").getProperty<int>("test_prop");, std::runtime_error);
}

TEST(ErrorTest, WrongSize) {

  happly::PLYData emptyPly;
  emptyPly.addElement("test_elem", 11);
  std::vector<int> data{1, 3, 4};

  EXPECT_THROW(emptyPly.getElement("test_elem").addProperty("bad_prop", data), std::runtime_error);
}

TEST(ErrorTest, WrongSizeList) {

  happly::PLYData emptyPly;
  emptyPly.addElement("test_elem", 11);
  std::vector<std::vector<int>> data{{1}, {3}, {4, 4}};

  EXPECT_THROW(emptyPly.getElement("test_elem").addListProperty("bad_prop", data), std::runtime_error);
}

TEST(ErrorTest, WhiteSpaceInElementName) {
  happly::PLYData ply;
  ply.addElement("test elem", 11);
  EXPECT_THROW(ply.validate(), std::runtime_error);
}

TEST(ErrorTest, WhiteSpaceInPropertyName) {
  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<int> data{1, 3, 4};
  ply.getElement("test_elem").addProperty("test prop", data);
  EXPECT_THROW(ply.validate(), std::runtime_error);
}


// Removal
TEST(RemovalTest, RemoveReplaceTest) {
  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<int> data{1, 3, 4};
  ply.getElement("test_elem").addProperty("data", data);

  EXPECT_EQ(data, ply.getElement("test_elem").getProperty<int>("data"));

  // Replace with new
  std::vector<int> data2{5, 5, 5};
  ply.getElement("test_elem").addProperty("data", data2);
  EXPECT_EQ(data2, ply.getElement("test_elem").getProperty<int>("data"));
}

// Type promotion
TEST(TypePromotionTest, PromoteFloatToDouble) {

  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<float> dataF{1.0, 3.0, 4.0};
  std::vector<double> dataD{1.0, 3.0, 4.0};
  ply.getElement("test_elem").addProperty("data", dataF);


  EXPECT_EQ(dataD, ply.getElement("test_elem").getProperty<double>("data"));
}

TEST(TypePromotionTest, DontPromoteDoubleToFloat) {

  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<float> dataF{1.0, 3.0, 4.0};
  std::vector<double> dataD{1.0, 3.0, 4.0};
  ply.getElement("test_elem").addProperty("data", dataD);


  EXPECT_THROW(ply.getElement("test_elem").getProperty<float>("data"), std::runtime_error);
}

TEST(TypePromotionTest, PromoteUnsigned) {

  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<unsigned char> dataC{1, 3, 5};
  ply.getElement("test_elem").addProperty("data", dataC);


  std::vector<unsigned short> dataS{1, 3, 5};
  std::vector<unsigned int> dataI{1, 3, 5};
  std::vector<unsigned long long int> dataL{1, 3, 5};
  std::vector<size_t> dataSZ{1, 3, 5};

  EXPECT_EQ(dataC, ply.getElement("test_elem").getProperty<unsigned char>("data"));
  EXPECT_EQ(dataS, ply.getElement("test_elem").getProperty<unsigned short>("data"));
  EXPECT_EQ(dataI, ply.getElement("test_elem").getProperty<unsigned int>("data"));
  //EXPECT_EQ(dataL, ply.getElement("test_elem").getProperty<unsigned long long int>("data"));
  EXPECT_EQ(dataSZ, ply.getElement("test_elem").getProperty<size_t>("data"));
}

TEST(TypePromotionTest, PromoteSigned) {

  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<char> data{1, -3, 5};
  ply.getElement("test_elem").addProperty("data", data);


  std::vector<char> dataC{1, -3, 5};
  std::vector<short> dataS{1, -3, 5};
  std::vector<int> dataI{1, -3, 5};
  std::vector<long long int> dataL{1, -3, 5};
  std::vector<int64_t> data64{1, -3, 5};

  EXPECT_EQ(dataC, ply.getElement("test_elem").getProperty<char>("data"));
  EXPECT_EQ(dataS, ply.getElement("test_elem").getProperty<int16_t>("data"));
  EXPECT_EQ(dataS, ply.getElement("test_elem").getProperty<short>("data"));
  EXPECT_EQ(dataI, ply.getElement("test_elem").getProperty<int32_t>("data"));
  EXPECT_EQ(dataI, ply.getElement("test_elem").getProperty<int>("data"));
  //EXPECT_EQ(dataL, ply.getElement("test_elem").getProperty<long long int>("data"));
  EXPECT_EQ(data64, ply.getElement("test_elem").getProperty<int64_t>("data"));
}

TEST(TypePromotionTest, DontPromoteAcrossSign) {

  happly::PLYData ply;
  ply.addElement("test_elem", 3);
  std::vector<int> dataI{1, -3, 5};
  std::vector<unsigned int> dataUI{1, 3, 5};
  ply.getElement("test_elem").addProperty("dataI", dataI);
  ply.getElement("test_elem").addProperty("dataUI", dataUI);


  // Make sure data is there
  EXPECT_EQ(dataI, ply.getElement("test_elem").getProperty<int>("dataI"));
  EXPECT_EQ(dataUI, ply.getElement("test_elem").getProperty<unsigned int>("dataUI"));

  // But throws if we cross signedness
  EXPECT_THROW(ply.getElement("test_elem").getProperty<int>("dataUI"), std::runtime_error);
  EXPECT_THROW(ply.getElement("test_elem").getProperty<unsigned int>("dataI"), std::runtime_error);
}

TEST(TypePromotionTest, PromoteFaceInd) {

  happly::PLYData ply;
  ply.addElement("face", 3);
  std::vector<std::vector<unsigned short>> faceInds{{1, 3, 4}, {0, 2, 4, 5}, {1, 1, 1}};
  std::vector<std::vector<size_t>> faceIndsS{{1, 3, 4}, {0, 2, 4, 5}, {1, 1, 1}};
  ply.getElement("face").addListProperty("vertex_indices", faceInds);

  std::vector<std::vector<size_t>> faceIndGet = ply.getFaceIndices();

  EXPECT_EQ(faceIndsS, faceIndGet);
}

TEST(TypePromotionTest, FaceIndSign) {

  happly::PLYData ply;
  ply.addElement("face", 3);
  std::vector<std::vector<short>> faceInds{{1, 3, 4}, {0, -2, 4, 5}, {1, 1, 1}};
  std::vector<std::vector<int>> faceIndsI{{1, 3, 4}, {0, -2, 4, 5}, {1, 1, 1}};
  std::vector<std::vector<unsigned int>> faceIndsU{{1, 3, 4}, {0, 2, 4, 5}, {1, 1, 1}};
  ply.getElement("face").addListProperty("vertex_indices", faceInds);

  std::vector<std::vector<int>> faceIndGetI = ply.getFaceIndices<int>();
  EXPECT_EQ(faceIndsI, faceIndGetI);
  
  std::vector<std::vector<unsigned int>> faceIndGetU = ply.getFaceIndices<unsigned int>();
  EXPECT_NE(faceIndsU, faceIndGetU);
}

TEST(TypePromotionTest, FaceIndThrow) {

  happly::PLYData ply;
  ply.addElement("face", 3);
  std::vector<std::vector<uint64_t>> faceInds{{1, 3, 1LL << 40}, {0, 2, 4, 5}, {1, 1, 1}};
  EXPECT_THROW(ply.getElement("face").addListProperty("vertex_indices", faceInds), std::runtime_error);
}

// === Test reading mesh-like files
TEST(MeshTest, ReadWriteASCIIMesh) {

  // = Read in an interesting mesh file
  happly::PLYData plyIn("../sampledata/platonic_shelf_ascii.ply", false);
  plyIn.validate();

  std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
  std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices();


  // = Write out the mesh file
  happly::PLYData plyOut;
  plyOut.addVertexPositions(vPos);
  plyOut.addFaceIndices(fInd);

  plyOut.validate();
  plyOut.write("temp.ply");


  // = Read the mesh file in again and make sure it hasn't changed
  happly::PLYData plyIn2("temp.ply", false);
  plyIn2.validate();

  std::vector<std::array<double, 3>> vPos2 = plyIn2.getVertexPositions();
  std::vector<std::vector<size_t>> fInd2 = plyIn2.getFaceIndices();

  DoubleArrayVecEq(vPos, vPos2);
  EXPECT_EQ(fInd, fInd2);
}

TEST(MeshTest, ReadWriteBinaryMesh) {

  // = Read in an interesting mesh file
  happly::PLYData plyIn("../sampledata/platonic_shelf.ply", false);
  plyIn.validate();

  std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
  std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices();


  // = Write out the mesh file
  happly::PLYData plyOut;
  plyOut.addVertexPositions(vPos);
  plyOut.addFaceIndices(fInd);

  plyOut.validate();
  plyOut.write("temp.ply", happly::DataFormat::Binary);


  // = Read the mesh file in again and make sure it hasn't changed
  happly::PLYData plyIn2("temp.ply", false);
  plyIn2.validate();

  std::vector<std::array<double, 3>> vPos2 = plyIn2.getVertexPositions();
  std::vector<std::vector<size_t>> fInd2 = plyIn2.getFaceIndices();

  DoubleArrayVecEq(vPos, vPos2);
  EXPECT_EQ(fInd, fInd2);
}

TEST(MeshTest, ReadWriteBinarySwapMesh) {

  // = Read in an interesting mesh file
  happly::PLYData plyIn("../sampledata/platonic_shelf_big_endian.ply", false);
  plyIn.validate();

  std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
  std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices();


  // = Write out the mesh file
  happly::PLYData plyOut;
  plyOut.addVertexPositions(vPos);
  plyOut.addFaceIndices(fInd);

  plyOut.validate();
  plyOut.write("temp.ply", happly::DataFormat::BinaryBigEndian);


  // = Read the mesh file in again and make sure it hasn't changed
  happly::PLYData plyIn2("temp.ply", false);
  plyIn2.validate();

  std::vector<std::array<double, 3>> vPos2 = plyIn2.getVertexPositions();
  std::vector<std::vector<size_t>> fInd2 = plyIn2.getFaceIndices();

  DoubleArrayVecEq(vPos, vPos2);
  EXPECT_EQ(fInd, fInd2);
}

// === Test stream interfaces
TEST(MeshTest, ReadWriteASCIIMeshStream) {

  // = Read the PLY from an input stream
  std::ifstream file ("../sampledata/platonic_shelf_ascii.ply");
  happly::PLYData plyIn(file, false);
  plyIn.validate();
  file.close();

  std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
  std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices();


  // = Write the mesh file to a stringstream
  std::stringstream ioBuffer;
  happly::PLYData plyOut;
  plyOut.addVertexPositions(vPos);
  plyOut.addFaceIndices(fInd);

  plyOut.validate();

  plyOut.write(ioBuffer);


  // = Read the mesh file in again and make sure it hasn't changed
  happly::PLYData plyIn2(ioBuffer, false);
  plyIn2.validate();

  std::vector<std::array<double, 3>> vPos2 = plyIn2.getVertexPositions();
  std::vector<std::vector<size_t>> fInd2 = plyIn2.getFaceIndices();

  DoubleArrayVecEq(vPos, vPos2);
  EXPECT_EQ(fInd, fInd2);
}

TEST(MeshTest, ReadWriteBinaryMeshStream) {

  // = Read in an interesting mesh file
  std::ifstream file ("../sampledata/platonic_shelf_ascii.ply");
  happly::PLYData plyIn(file, false);
  plyIn.validate();
  file.close();

  std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
  std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices();


  // = Write out the mesh to a stringstream
  std::stringstream ioBuffer;
  happly::PLYData plyOut;
  plyOut.addVertexPositions(vPos);
  plyOut.addFaceIndices(fInd);

  plyOut.validate();
  plyOut.write(ioBuffer, happly::DataFormat::Binary);


  // = Read the mesh file in again and make sure it hasn't changed
  happly::PLYData plyIn2(ioBuffer, false);
  plyIn2.validate();

  std::vector<std::array<double, 3>> vPos2 = plyIn2.getVertexPositions();
  std::vector<std::vector<size_t>> fInd2 = plyIn2.getFaceIndices();

  DoubleArrayVecEq(vPos, vPos2);
  EXPECT_EQ(fInd, fInd2);
}


TEST(PerfTest, WriteReadFloatList) {

  // Parameters
  size_t innerSizeMax = 10;
  size_t N = 100000;

  // Random number makers
  std::mt19937 gen(777);
  std::uniform_int_distribution<int> distInnerSize(1, innerSizeMax);
  std::uniform_int_distribution<int> distValues(0, 1000000);

  // Generate a long list of junk data
  std::vector<std::vector<int>> testVals;
  for (size_t i = 0; i < N; i++) {
    size_t innerCount = distInnerSize(gen);
    std::vector<int> innerVals;
    for (size_t j = 0; j < innerCount; j++) {
      int val = distValues(gen);
      innerVals.push_back(val);
    }
    testVals.push_back(innerVals);
  }

  // Start timing
  auto tStart = std::chrono::steady_clock::now();

  // Create a ply file
  happly::PLYData plyOut;
  plyOut.addElement("testElem", N);
  plyOut.getElement("testElem").addListProperty<int>("testVals", testVals);

  // Write it to a stream
  std::stringstream ioBuffer;
  plyOut.write(ioBuffer, happly::DataFormat::Binary);

  // = Read from stream
  // (note that this DOES NOT actually access the property, but simply opening the stream parses everything)
  happly::PLYData plyIn(ioBuffer, false);

  // Finish timing
  auto tEnd = std::chrono::steady_clock::now();
  std::cout << "  time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart).count() << "us" << std::endl;
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
