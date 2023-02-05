# include "ft_vector.hpp"
# include "ft_stack.hpp"
# include "ft_map.hpp"
# include <map>
#include <list>

#define T1 int
#define T2 int
typedef ft::pair<const T1, T2> T3;

int		main(void)
{
	ft::map<T1, T2> mp;
	ft::map<T1, T2>::iterator it = mp.begin();
	ft::map<T1, T2>::const_iterator cit = mp.begin();

	ft::map<T1, T2>::reverse_iterator rit(it);

	ft::map<T1, T2>::const_reverse_iterator crit(rit);
	ft::map<T1, T2>::const_reverse_iterator crit_(it);
	ft::map<T1, T2>::const_reverse_iterator crit_2(cit);

	std::cout << "OK" << std::endl;
	return (0);
}