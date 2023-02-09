# include "ft_vector.hpp"
# include "ft_stack.hpp"
# include "ft_map.hpp"
# include <map>
#include <list>

#define T1 int
#define T2 int
#define TESTED_NAMESPACE1 ft
#define TESTED_NAMESPACE2 std 

int		main(void)
{
	// TESTED_NAMESPACE1::map<T1, T2> mp;
	// mp[0] = 1;
	TESTED_NAMESPACE1::map<T1, T2> mp1;
	mp1[0] = 10;
	mp1[1] = 20;
	mp1[2] = 30;
	mp1[3] = 40;
	ft::map<T1, T2> const mp2;
	// mp2[0] = 10;
	// TESTED_NAMESPACE1::map<T1, T2>::iterator it1 = mp1.begin(); // <-- error expected
	TESTED_NAMESPACE1::map<T1, T2>::iterator it1 = mp2.begin();
	TESTED_NAMESPACE1::map<T1, T2>::const_iterator it2 = mp1.begin();
	// std::cout << "it1 before: " << it1->second << std::endl;
	// std::cout << "it2 before: " << it1->second << std::endl;
	// // it1->second = 10;
	// it1->second = 100;
	// std::cout << "it1 after : " << it1->second << std::endl;
	// std::cout << "it2 before: " << it1->second << std::endl;
	// TESTED_NAMESPACE2::map<T1, T2> const mp2;
	// TESTED_NAMESPACE2::map<T1, T2>::iterator it2 = mp2.begin(); // <-- error expected

	(void)it1;
	(void)it2;
	return (0);
}
