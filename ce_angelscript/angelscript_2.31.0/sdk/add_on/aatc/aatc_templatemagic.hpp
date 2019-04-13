/*
The zlib/libpng License
http://opensource.org/licenses/zlib-license.php


Angelscript addon Template Containers
Copyright (c) 2014 Sami Vuorela

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1.	The origin of this software must not be misrepresented;
You must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2.	Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3.	This notice may not be removed or altered from any source distribution.


Sami Vuorela
samivuorela@gmail.com
*/


#ifndef _includedh_aatc_templatemagic
#define _includedh_aatc_templatemagic


#include <tuple>



BEGIN_AS_NAMESPACE
namespace aatc {
	namespace templatemagic {



		namespace detail {
			namespace staticiterate {
				template<
					int iteration_start,
					int iteration_end,
					int iteration_current,
					template<int> class functor_operate
				> class internal_functor {
				public:
					void operator()()const {
						functor_operate<iteration_end - iteration_current> f_operate; f_operate();
						internal_functor<iteration_start, iteration_end, iteration_current - 1, functor_operate> f; f();
					}
				};

				template<
					int iteration_start,
					int iteration_end,
					template<int> class functor_operate
				> class internal_functor<iteration_start, iteration_end, -1, functor_operate> {
				public:
					void operator()()const {}
				};
			}//namespace staticiterate
		}//namespace detail

		/*
			Iterates in runtime over a range defined in compile time.

			Iterates over the int numbers iteration_start ... iteration_end and calls 'functor_operate' with 1 template parameter, the current iteration
			Iterating 2...4 will call the functor 3 times at functor_operate<2>(), functor_operate<3>(), functor_operate<4>()
			Iterating 0...0 will call the functor once at functor_operate<0>()
		*/
		template<
			int iteration_start,
			int iteration_end,
			template<int> class functor_operate
		> class staticiterate {
		public:
			void operator()()const{
				detail::staticiterate::internal_functor<iteration_start, iteration_end, iteration_end - iteration_start, functor_operate> f; f();
			}
		};



		namespace detail {
			namespace staticiterate_1arg {
				template<
					int iteration_start,
					int iteration_end,
					int iteration_current,
					template<int > class functor_operate,
					typename T_arg1
				> class internal_functor {
				public:
					void operator()(T_arg1 arg1)const {
						functor_operate<iteration_end - iteration_current> f_operate; f_operate(arg1);
						internal_functor<iteration_start, iteration_end, iteration_current - 1, functor_operate, T_arg1> f; f(arg1);
					}
				};

				template<
					int iteration_start,
					int iteration_end,
					template<int > class functor_operate,
					typename T_arg1
				> class internal_functor<iteration_start, iteration_end, -1, functor_operate, T_arg1> {
				public:
					void operator()(T_arg1 arg1)const {}
				};
			}//namespace staticiterate_1arg
		}//namespace detail

		/*
			Same as the basic iterator but this thing forwards an argument to the functor, use a tuple for multiple arguments
		*/
		template<
			int iteration_start,
			int iteration_end,
			template<int iteration_current> class functor_operate,
			typename T_arg1
		> class staticiterate_1arg{
		public:
			void operator()(T_arg1 arg1)const{
				detail::staticiterate_1arg::internal_functor<iteration_start, iteration_end, iteration_end - iteration_start, functor_operate, T_arg1> f; f(arg1);
			}
		};



		namespace detail {
			namespace staticiterate_2arg {
				template<
					int iteration_start,
					int iteration_end,
					int iteration_current,
					template<int > class functor_operate,
					typename T_arg1,
					typename T_arg2
				> struct internal_functor {
					void operator()(T_arg1 arg1, T_arg2 arg2)const {
						functor_operate<iteration_end - iteration_current> f_operate; f_operate(arg1, arg2);
						internal_functor<iteration_start, iteration_end, iteration_current - 1, functor_operate, T_arg1, T_arg2> f; f(arg1, arg2);
					}
				};

				template<
					int iteration_start,
					int iteration_end,
					template<int iteration_current> class functor_operate,
					typename T_arg1,
					typename T_arg2
				> struct internal_functor<iteration_start, iteration_end, -1, functor_operate, T_arg1, T_arg2> {
					void operator()(T_arg1 arg1, T_arg2 arg2)const {}
				};
			}//namespace staticiterate_2arg
		}//namespace detail

		/*
			Same as the basic iterator but this thing forwards an argument to the functor, use a tuple for multiple arguments
		*/
		template<
			int iteration_start,
			int iteration_end,
			template<int iteration_current> class functor_operate,
			typename T_arg1,
			typename T_arg2
		> struct staticiterate_2arg{
			void operator()(T_arg1 arg1, T_arg2 arg2)const{
				detail::staticiterate_2arg::internal_functor<iteration_start, iteration_end, iteration_end - iteration_start, functor_operate, T_arg1, T_arg2> f; f(arg1, arg2);
			}
		};



	};//namespace templatemagic
};//namespace aatc
END_AS_NAMESPACE
#endif
