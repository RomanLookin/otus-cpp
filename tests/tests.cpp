#include <gtest/gtest.h>
#include <vector>
#include "../lib.h"

TEST(test_version, test_customcompBack)
{
    ip_addr ip_adr1(10, 1, 1, 1);
    ip_addr ip_adr2(1, 1, 1, 2);
	
	ASSERT_TRUE(customComp_back(ip_adr1, ip_adr2));
}
TEST(test_version, test_customcompBack2)
{
    ip_addr ip_adr1(1, 10, 1, 1);
    ip_addr ip_adr2(1, 1, 1, 2);

    ASSERT_TRUE(customComp_back(ip_adr1, ip_adr2));
}
TEST(test_version, test_customcompBack3)
{
    ip_addr ip_adr1(1, 1, 10, 1);
    ip_addr ip_adr2(1, 1, 1, 2);

    ASSERT_TRUE(customComp_back(ip_adr1, ip_adr2));
}
TEST(test_version, test_customcompBack4)
{
    ip_addr ip_adr1(1, 1, 1, 1);
    ip_addr ip_adr2(10, 1, 1, 2);

    ASSERT_FALSE(customComp_back(ip_adr1, ip_adr2));
}
TEST(test_version, test_customcompBack5)
{
    ip_addr ip_adr1(1, 1, 1, 1);
    ip_addr ip_adr2(1, 10, 1, 2);

    ASSERT_FALSE(customComp_back(ip_adr1, ip_adr2));
}
TEST(test_version, test_customcompBack6)
{
    ip_addr ip_adr1(1, 1, 10, 1);
    ip_addr ip_adr2(1, 1, 1, 2);

    ASSERT_TRUE(customComp_back(ip_adr1, ip_adr2));
}

TEST(test_version, test_split)
{
	std::string str = {"1.1.1.0\t2\t3"};
	std::vector<std::string> str_split = split(str, '\t');
	std::vector<std::string> str_ok{"1.1.1.0", "2", "3"};
	ASSERT_TRUE(str_split == str_ok);
}
TEST(test_version, test_get_ip_adr)
{
	std::string str = {"1.1.1.0\t2\t3"};
	bool ok = true;
	std::vector<int> octets_int = get_ip_adr(str, ok);
	ASSERT_TRUE(ok && (octets_int.at(0) == 1) && (octets_int.at(1) == 1) && (octets_int.at(2) == 1) && (octets_int.at(3) == 0));

}



	
	
