#include "hardmon/CSensorReader.hpp"
#include "hardmon/Utils.hpp"

#include "mock/CStorageMock.hpp"

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include <yaml-cpp/yaml.h>

#include <gtest/gtest.h>

class CSensorReaderTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

namespace bf = boost::filesystem;

using ::testing::AtLeast;
using ::testing::NiceMock;

ACTION_P2(ReturnFromAsyncCall, RetVal, SemDone)
{
    SemDone->post();
    return RetVal;
}

ACTION_P(VoidFromAsyncCall, SemDone)
{
    SemDone->post();
}

TEST_F(CSensorReaderTest, appendValue)
{
    boost::interprocess::interprocess_semaphore semDone(0);

    auto storage = std::make_shared<NiceMock<CStorageMock>>();

    auto reader = hardmon::CSensorReader(storage);

    YAML::Node nodeSensors =
      YAML::Load(string_format("[ "
                               " { "
                               "  sensor: regular-file, "
                               "  id: test-sensor, "
                               "  interval: 5, "
                               "  params: { "
                               "   filename: %s,"
                               "  },"
                               " },"
                               "] ",
                               (bf::path(__FILE__).parent_path() / "testdata" / "static_42.txt").c_str()));

    reader.configureSensors(nodeSensors);

    reader.start();

    EXPECT_CALL(*storage, appendValue("test-sensor", 42)).Times(AtLeast(1)).WillOnce(VoidFromAsyncCall(&semDone));

    boost::posix_time::ptime until = boost::posix_time::second_clock::universal_time() + boost::posix_time::seconds(1);
    EXPECT_TRUE(semDone.timed_wait(until));

    reader.stop();
}
