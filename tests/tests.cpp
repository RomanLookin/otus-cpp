#define TEST_MODULE test_version
#include <gtest/gtest.h>
#include <vector>
#include "../lib.h"

TEST(test_version, simple_test)
{
    int vers = version();
    ASSERT_TRUE( vers > 0);
}

TEST(test_version, test_customcompBack)
{
    ip_addr ip_adr1(1, 1, 1, 1);
    ip_addr ip_adr2(1, 1, 1, 2);
	
	ASSERT_TRUE(customComp_back(ip_adr1, ip_adr2));
}

/*TEST(test_version, test_customcompforw)
{
	ip_addr ip_adr1 {1, 1, 1, 2};
	ip_addr ip_adr2 {1, 1, 1, 1};
	
	ASSERT_TRUE(customComp_Forw(ip_adr1, ip_adr2));
}

TEST(test_version, test_sort_ip_adr)
{
    std::vector<ip_addr> vec_ip_adr{
		{1, 1, 1, 2},
		{1, 1, 1, 1}
	};
	
    std::vector<ip_addr> vec_ip_adr_sort{
		{1, 1, 1, 2},
		{1, 1, 1, 1}
	};
	
	vec_ip_adr=sortIP_Address(vec_ip_adr);
	
	ASSERT_TRUE(vec_ip_adr == vec_ip_adr_sort);
}

TEST(test_version, test_split)
{
	std::string str = {"1.1.1.0\t2\t3"};
	std::vector<std::string> str_split = split(str, "\t");
	ASSERT_TRUE(str_split == std::vector<std::string>{"1.1.1.0", "2", "3"});
}
TEST(test_version, test_get_ip_adr)
{
	std::string str = {"1.1.1.0\t2\t3"};
	ip_addr ip_adr = get_ip_adr(str);
	ASSERT_TRUE((ip_adr.oct1 == 1) && (ip_adr.oct2 == 1) && (ip_adr.oct3 == 1) && (ip_adr.oct4 == 0));

}
TEST(test_vesion, test_ip_filter_add)
{ 
	vector<ip_addr> vec_ip = {{1, 1, 1,0}, {2,1,1,1}, {1, 1, 1, 2}};
	
	vector<ip_addr> vec_ip_rez = ip_filter_and(vec_ip, 1);
	ASSERT_TRUE(vec_ip_rez == std::vector<ip_addr)>{{1,1,1,0}, {1,1,1,2}});
}
TEST(test_vesion, test_ip_filter_add2)
{ 
	vector<ip_addr> vec_ip = {{1, 1, 1,0}, {2,1,1,1}, {1, 1, 1, 2}};
	
	vector<ip_addr> vec_ip_rez = ip_filter_and(vec_ip, 46, 70);
	ASSERT_TRUE(vec_ip_rez == std::vector<ip_addr)>{{1,1,1,0}, {1,1,1,2}});
}
TEST(test_vesion, test_ip_filter_add3)
{ 
	vector<ip_addr> vec_ip = {{1, 1, 1,0}, {2,1,1,1}, {1, 1, 1, 2}};
	
	vector<ip_addr> vec_ip_rez = ip_filter_or(vec_ip, 1);
	ASSERT_TRUE(vec_ip_rez == std::vector<ip_addr)>{{1,1,1,0}, {1,1,1,2}});
}

//EXPECT_EQ(marker.get_name(), name);
//ASSERT_EQ(signal_spy.count(), 5);
*/
	
	
	
	
